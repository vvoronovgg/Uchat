#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void delete_reply_from_db(db_change_user_passw_reply **reply_from_db);

/*ответ от базы данных на запрос - 'смена пароля' и перевод ответа в json-строку*/
char *change_passwd_reply_to_jsn(db_change_user_passw_reply **reply_from_db) {
    if (!*reply_from_db)
        return NULL;
    
    cJSON *object = NULL;
    char *str = NULL;

    object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "type", "change_password_reply");  
    cJSON_AddStringToObject(object, "password_changed", (*reply_from_db)->password_changed);
    
    str = cJSON_Print(object);  
    cJSON_Delete(object);   
    delete_reply_from_db(reply_from_db); 

    return str; 
}

/*очищает структуру*/
static void delete_reply_from_db(db_change_user_passw_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->password_changed);
    free(*reply_from_db);
    *reply_from_db = NULL;
}
