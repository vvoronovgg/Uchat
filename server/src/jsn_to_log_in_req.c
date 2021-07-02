#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void init_log_in_req(db_user_log_in_req **log_in);
static void delete_req_struct(db_user_log_in_req **log_in);

/*достает из json-строки данные (запрос на вход пользователя) и записывает эти данные в структуру*/
db_user_log_in_req *jsn_to_log_in_req(char *json_log_in_request, errors **error_p) { 
    db_user_log_in_req* log_in = NULL;
    cJSON *object = NULL;
    char *e_message = NULL;     //ЧАСТЬ сообщения об ошибке

    init_log_in_req(&log_in);
    object = cJSON_Parse(json_log_in_request);
    
    if (!object) {
        failed_to_parse_json(error_p, mx_strdup(" in function 'jsn_to_log_in_req' "));
        delete_req_struct(&log_in);
        return NULL;
    }     

    if (object) {
        log_in->user_login = get_value(object, "user_login", &e_message);   //записываю в структуру значение ключа user_login в объекте object
        //log_in->user_phone_number = get_value(object, "user_phone_number", &e_message);     не удалять пока что! //записываю в структуру значение ключа user_phone_number в объекте object
        log_in->user_password = get_value(object, "user_password", &e_message);     //записываю в структуру значение ключа user_password в объекте object
        log_in->log_in_time = get_value(object, "log_in_time", &e_message);      //записываю в структуру значение ключа log_in_time в объекте object
    }

    cJSON_Delete(object);   //удаляю json

    if (!e_message)      //если не обнаружена ошибка при переводе json-строки в структуру:
        return log_in;
    else {      //была найдена ошибка
        delete_req_struct(&log_in);
        failed_to_get_key_value(error_p, &e_message, mx_strdup(" in function 'jsn_to_log_in_req' "));
        return NULL;
    }

    return log_in;
}

static void init_log_in_req(db_user_log_in_req **log_in) {
    *log_in = (db_user_log_in_req*)malloc(sizeof(db_user_log_in_req));   //выделяю память под структуру
    (*log_in)->log_in_time = NULL;
    (*log_in)->user_login = NULL;
    (*log_in)->user_password = NULL;
    (*log_in)->user_phone_number = NULL;
}

static void delete_req_struct(db_user_log_in_req **log_in) {
    mx_strdel(&(*log_in)->log_in_time);
    mx_strdel(&(*log_in)->user_login);
    mx_strdel(&(*log_in)->user_password);
    mx_strdel(&(*log_in)->user_phone_number);
    free(*log_in);
    *log_in = NULL;
}
