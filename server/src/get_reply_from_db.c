#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void define_json_type(char *json, char **type, errors **error);

/*
основная функция:
принимает json-строку (запрос от клиента), определяет поле type в json, 
фришит char *json
возвращает ответ из БД, конвертирует его в необходимую json-строку для отправки клиенту
*/
char *get_reply_from_db(char **json) {
    char *reply = NULL;
    char *type = NULL;
    errors *error = NULL;

    init_error_struct(&error);
    //inversion(json);    //расшифровываю
    define_json_type(*json, &type, &error); //определяет тип json-строки

    if (!type) {    //не удалось достать ключ type
        error_json(&reply, &error);
    }

    else if (mx_strcmp("registration_req", type) == 0)
        get_registration_reply(*json, &reply);  //тип - регистрация
    
    else if (mx_strcmp("log_in_req", type) == 0) 
        get_log_in_reply(*json, &reply);    //тип - логин
    
    else if (mx_strcmp("find_user_req", type) == 0)
        get_find_user_reply(*json, &reply);

    else if (mx_strcmp("private_message_req", type) == 0)
        get_pr_message_reply(*json, &reply);

    else if (mx_strcmp("chat_with_req", type) == 0)
        get_chat_with_reply(*json, &reply);
    
    else if (mx_strcmp("change_password_req", type) == 0)
        get_change_passw_reply(*json, &reply);
        
    else {
        incorrect_key_type(&error, mx_strdup(" in function 'get_reply_from_db' "));
        error_json(&reply, &error); 
    }   
    
    delete_error(&error);
    mx_strdel(&type);
    mx_strdel(json);
    //inversion(&reply);  //шифрую
    
    return reply;
}

static void define_json_type(char *json, char **type, errors **error) {
    cJSON *object = NULL;
    char *err_msg = NULL;   //часть ошибки;

    object = cJSON_Parse(json);
    
    if (!object) {      //если не распарсило
        failed_to_parse_json(error, mx_strdup(" in function 'define_json_type' "));
        return;
    }

    if (object) {       //если распарсило
        *type = get_value(object, "type", &err_msg);
        if (!*type) {
            failed_to_get_key_value(error, &err_msg, mx_strdup(" in function 'define_json_type' "));    
        }
    }
    cJSON_Delete(object);
}
