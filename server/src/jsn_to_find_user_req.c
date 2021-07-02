#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void init_find_user_req(db_find_user_req **find_user);
static void delete_req_struct(db_find_user_req **find_user);

/*достает из json-строки данные (запрос на поиск пользователя) и записывает эти данные в структуру*/
db_find_user_req *jsn_to_find_user_req(char *json_find_user_request, errors **error_p) { 
    db_find_user_req* find_user = NULL;
    cJSON *object = NULL;
    char *e_message = NULL;

    init_find_user_req(&find_user);
    object = cJSON_Parse(json_find_user_request);
    
    if (!object) {
        failed_to_parse_json(error_p, mx_strdup(" in function 'jsn_to_find_user_req': "));
        delete_req_struct(&find_user);
        return NULL;
    }     

    if (object) {
        find_user->login_to_find = get_value(object, "login_to_find", &e_message);   //записываю в структуру значение ключа login_to_find в объекте object
    }

    cJSON_Delete(object);
    if (!e_message)      //если не обнаружена ошибка при переводе json-строки в структуру:
        return find_user;
    else {      //была найдена ошибка
        delete_req_struct(&find_user);
        failed_to_get_key_value(error_p, &e_message, mx_strdup(" in function 'jsn_to_find_user_req "));
        return NULL;
    }

    return find_user;
}

static void init_find_user_req(db_find_user_req **find_user) {
    *find_user = (db_find_user_req*)malloc(sizeof(db_find_user_req));   
   (*find_user)->login_to_find = NULL;
}

static void delete_req_struct(db_find_user_req **find_user) {
  mx_strdel(&(*find_user)->login_to_find);
  free(*find_user);
  *find_user = NULL;
}
