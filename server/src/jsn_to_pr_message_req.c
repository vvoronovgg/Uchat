#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void init_log_in_req(db_private_message_req **private_message);
static void delete_req_struct(db_private_message_req **private_message);

/*достает из json-строки данные (запрос на личное сообщение) и записывает эти данные в структуру*/
db_private_message_req *jsn_to_pr_message_req(char *json_pr_message_request, errors **error_p) { 
    db_private_message_req* private_message = NULL;
    cJSON *object = NULL;
    char *e_message = NULL;     //ЧАСТЬ сообщения об ошибке

    init_log_in_req(&private_message);
    object = cJSON_Parse(json_pr_message_request);
    
    if (!object) {
        failed_to_parse_json(error_p, mx_strdup(" in function 'jsn_to_pr_message_req' "));
        delete_req_struct(&private_message);
        return NULL;
    }     

    if (object) {
        private_message->date = get_value(object, "date", &e_message);   
        private_message->message = get_value(object, "message", &e_message);
        private_message->receiver_id = get_value(object, "receiver_id", &e_message);
        private_message->sender_id = get_value(object, "sender_id", &e_message);
    }

    cJSON_Delete(object);   //удаляю json

    if (!e_message)      //если не обнаружена ошибка при переводе json-строки в структуру:
        return private_message;
    else {      //была найдена ошибка
        delete_req_struct(&private_message);
        failed_to_get_key_value(error_p, &e_message, mx_strdup(" in function 'jsn_to_pr_message_req' "));
        return NULL;
    }

    return private_message;
}

static void init_log_in_req(db_private_message_req **private_message) {
    *private_message = (db_private_message_req*)malloc(sizeof(db_private_message_req));   //выделяю память под структуру
    (*private_message)->date = NULL;
    (*private_message)->message = NULL;
    (*private_message)->receiver_id = NULL;
    (*private_message)->sender_id = NULL;
}

static void delete_req_struct(db_private_message_req **private_message) {
    mx_strdel(&(*private_message)->date);
    mx_strdel(&(*private_message)->message);
    mx_strdel(&(*private_message)->receiver_id);
    mx_strdel(&(*private_message)->sender_id);
    free(*private_message);
    *private_message = NULL;
}
