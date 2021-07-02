#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void user_is_not_in(cJSON *object);
static void user_is_in(cJSON *object, db_user_registration_reply *reply_from_db);
static void delete_reply_from_db(db_user_registration_reply **reply_from_db);

/*ответ от базы данных на запрос - 'регистрация пользователя' и перевод ответа в json-строку*/
char *registration_reply_to_jsn(db_user_registration_reply **reply_from_db) {
    if (!reply_from_db || !*reply_from_db) {
        return NULL;
    }
    
    cJSON *object = NULL;
    char *str = NULL;

    object = cJSON_CreateObject();    //создается объект 
    cJSON_AddStringToObject(object, "type", "registration_reply");  //создается ключ "type" и значение "registration_req" в объекте object

    if ((*reply_from_db)->user_is_in_db == NULL) //если пользователь с соответствующими данными не найден в БД
        user_is_not_in(object);    
    else user_is_in(object, *reply_from_db); //если пользователь с соответствующими данными найден в БД
    
    str = cJSON_Print(object);  //конвертирую в json-строку
    
    cJSON_Delete(object);   //удаляю объект
    delete_reply_from_db(reply_from_db);

    return str; 
}

static void user_is_not_in(cJSON *object) {
    cJSON_AddStringToObject(object, "user_is_in_db", "0");  //создается ключ "user_is_in_db" и значение "0" в объекте object
}

static void user_is_in(cJSON *object, db_user_registration_reply *reply_from_db) {
    cJSON_AddStringToObject(object, "user_is_in_db", reply_from_db->user_is_in_db);     //создается ключ "user_is_in_db" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_login", reply_from_db->user_login);       //создается ключ "user_login" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_phone_number", reply_from_db->user_phone_number);     //создается ключ "user_phone_number" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_email", reply_from_db->user_email);       //создается ключ "user_email" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_id", reply_from_db->user_id);       //создается ключ "user_id" и значение  в структуре в объекте object
}

static void delete_reply_from_db(db_user_registration_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->user_is_in_db);
    mx_strdel(&(*reply_from_db)->user_login);
    mx_strdel(&(*reply_from_db)->user_phone_number);
    mx_strdel(&(*reply_from_db)->user_email);
    mx_strdel(&(*reply_from_db)->user_id);
    free(*reply_from_db);
    *reply_from_db = NULL;
}
