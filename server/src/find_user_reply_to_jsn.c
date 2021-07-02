#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void found_user(cJSON *object, db_find_user_reply *reply_from_db);
static void not_found_user(cJSON *object);
static void delete_reply_from_db(db_find_user_reply **reply_from_db);

/*ответ от базы данных на запрос - 'поиск пользователя' и перевод ответа в json-строку*/
char *find_user_reply_to_jsn(db_find_user_reply **reply_from_db) {
    if (!*reply_from_db)
        return NULL;
    
    cJSON *object = NULL;
    char *str = NULL;

    object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "type", "find_user_reply");  
    
    if (mx_strcmp((*reply_from_db)->login_found, "1") == 0)  
        found_user(object, *reply_from_db);    
    else  not_found_user(object);     
    
    str = cJSON_Print(object);  
    cJSON_Delete(object);   
    delete_reply_from_db(reply_from_db); 

    return str; 
}

/*пользователь не найден*/
static void not_found_user(cJSON *object) {
    cJSON_AddStringToObject(object, "login_found", "0");  
}

/*пользователь найден*/
static void found_user(cJSON *object, db_find_user_reply *reply_from_db) {
    cJSON_AddStringToObject(object, "login_found", reply_from_db->login_found);  
    cJSON_AddStringToObject(object, "f_user_first_name", reply_from_db->f_user_first_name);       
    cJSON_AddStringToObject(object, "f_user_id", reply_from_db->f_user_id);     
    cJSON_AddStringToObject(object, "f_user_last_name", reply_from_db->f_user_last_name);     
    cJSON_AddStringToObject(object, "f_user_ph_number", reply_from_db->f_user_ph_number);
    cJSON_AddStringToObject(object, "f_user_email", reply_from_db->f_user_email);       
}

/*очищает структуру*/
static void delete_reply_from_db(db_find_user_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->f_user_first_name);
    mx_strdel(&(*reply_from_db)->f_user_last_name);
    mx_strdel(&(*reply_from_db)->login_found);
    mx_strdel(&(*reply_from_db)->f_user_id);
    mx_strdel(&(*reply_from_db)->f_user_email);
    mx_strdel(&(*reply_from_db)->f_user_ph_number);
    free(*reply_from_db);
    *reply_from_db = NULL;
}
