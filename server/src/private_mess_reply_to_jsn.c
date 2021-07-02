#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void delete_reply_from_db(db_private_message_reply **reply_from_db);

/*ответ от базы данных на запрос - 'личное сообщение' и перевод ответа в json-строку*/
char *private_mess_reply_to_jsn(db_private_message_reply **reply_from_db) {
    if (!reply_from_db || !*reply_from_db)
        return NULL;

    cJSON *object = NULL;
    char *str = NULL;

    object = cJSON_CreateObject();    //создается объект 
    cJSON_AddStringToObject(object, "type", "private_message_reply");  
    cJSON_AddStringToObject(object, "sender_id", (*reply_from_db)->sender_id);  
    cJSON_AddStringToObject(object, "sender_f_name", (*reply_from_db)->sender_f_name);
    cJSON_AddStringToObject(object, "sender_l_name", (*reply_from_db)->sender_l_name);
    cJSON_AddStringToObject(object, "sender_login", (*reply_from_db)->sender_login);
    cJSON_AddStringToObject(object, "sender_email", (*reply_from_db)->sender_email);
    cJSON_AddStringToObject(object, "sender_ph_number", (*reply_from_db)->sender_ph_number);
    cJSON_AddStringToObject(object, "receiver_id", (*reply_from_db)->receiver_id);
    cJSON_AddStringToObject(object, "new_message", (*reply_from_db)->new_message);
    cJSON_AddStringToObject(object, "date", (*reply_from_db)->date);

    str = cJSON_Print(object);  //конвертирую в json-строку
    
    cJSON_Delete(object);   //удаляю объект
    delete_reply_from_db(reply_from_db);

    return str; 
}

/*очищает структуру*/
static void delete_reply_from_db(db_private_message_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->receiver_id);
    mx_strdel(&(*reply_from_db)->sender_id);
    mx_strdel(&(*reply_from_db)->sender_f_name);
    mx_strdel(&(*reply_from_db)->sender_l_name);
    mx_strdel(&(*reply_from_db)->sender_login);
    mx_strdel(&(*reply_from_db)->sender_email);
    mx_strdel(&(*reply_from_db)->sender_ph_number);
    mx_strdel(&(*reply_from_db)->date);
    mx_strdel(&(*reply_from_db)->new_message);

    free(*reply_from_db);
    *reply_from_db = NULL;
}
