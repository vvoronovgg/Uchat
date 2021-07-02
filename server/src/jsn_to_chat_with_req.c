#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void init_get_chat_with_req(db_get_chat_with_sel_user_req **chat_with);
static void delete_req_struct(db_get_chat_with_sel_user_req **chat_with);

/*достает из json-строки данные (запрос "получить чат с выбранным пользователем" ) и записывает эти данные в структуру*/
db_get_chat_with_sel_user_req *jsn_to_chat_with_req(char *json_chat_with_request, errors **error_p) { 
    db_get_chat_with_sel_user_req* chat_with = NULL;
    cJSON *object = NULL;
    char *e_message = NULL;     //ЧАСТЬ сообщения об ошибке

    init_get_chat_with_req(&chat_with);
    object = cJSON_Parse(json_chat_with_request);
    
    if (!object) {
        failed_to_parse_json(error_p, mx_strdup(" in function 'jsn_to_chat_with_req' "));
        delete_req_struct(&chat_with);
        return NULL;
    }     

    if (object) {
        chat_with->dest_user_id = get_value(object, "dest_user_id", &e_message);   
        chat_with->source_user_id = get_value(object, "source_user_id", &e_message); 
    }

    cJSON_Delete(object);   //удаляю json

    if (!e_message)      //если не обнаружена ошибка при переводе json-строки в структуру:
        return chat_with;
    else {      //была найдена ошибка
        delete_req_struct(&chat_with);
        failed_to_get_key_value(error_p, &e_message, mx_strdup(" in function 'jsn_to_chat_with_req' "));
        return NULL;
    }

    return chat_with;
}

static void init_get_chat_with_req(db_get_chat_with_sel_user_req **chat_with) {
    *chat_with = (db_get_chat_with_sel_user_req*)malloc(sizeof(db_get_chat_with_sel_user_req));   //выделяю память под структуру
    (*chat_with)->dest_user_id = NULL;
    (*chat_with)->source_user_id = NULL;
}

static void delete_req_struct(db_get_chat_with_sel_user_req **chat_with) {
    mx_strdel(&(*chat_with)->dest_user_id);
    mx_strdel(&(*chat_with)->source_user_id);
    free(*chat_with);
    *chat_with = NULL;
}
