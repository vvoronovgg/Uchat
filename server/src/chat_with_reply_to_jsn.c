#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"
static void fill_arrays(db_get_chat_with_sel_user_reply *reply_from_db, cJSON *object);
static void delete_reply_from_db(db_get_chat_with_sel_user_reply **reply_from_db);

/*конвертирует структуру в json-строку*/
char *chat_with_reply_to_jsn(db_get_chat_with_sel_user_reply **reply_from_db) {
    if (!reply_from_db || !*reply_from_db)
        return NULL;

    cJSON *object = NULL;
    char *str = NULL;

    object = cJSON_CreateObject();    //создается объект 
    cJSON_AddStringToObject(object, "type", "chat_with_reply");  
    cJSON_AddStringToObject(object, "source_user_id", (*reply_from_db)->source_user_id);  
    cJSON_AddStringToObject(object, "dest_user_id", (*reply_from_db)->dest_user_id);

    fill_arrays(*reply_from_db, object);
    str = cJSON_Print(object);  //конвертирую в json-строку
    
    cJSON_Delete(object);  //удаляю объект
    delete_reply_from_db(reply_from_db);

    return str; 
}

/*добавляет массивы в json из структуры*/
static void fill_arrays(db_get_chat_with_sel_user_reply *reply_from_db, cJSON *object) {
    cJSON *last_50_messages = NULL;
    cJSON *dates = NULL;
    cJSON *messages_senders = NULL;
    cJSON *s1 = NULL;
    cJSON *s2 = NULL;
    cJSON *s3 = NULL;

    last_50_messages = cJSON_AddArrayToObject(object, "last_50_messages");
    dates = cJSON_AddArrayToObject(object, "dates");
    messages_senders = cJSON_AddArrayToObject(object, "messages_senders");

    for (int i = 0; i < MAX_MESS_AMNT && reply_from_db->dates[i] != NULL; i++) {
        s1 = cJSON_CreateString(reply_from_db->dates[i]);
        s2 = cJSON_CreateString(reply_from_db->last_50_messages[i]);
        s3 = cJSON_CreateString(reply_from_db->messages_senders[i]);
        cJSON_AddItemToArray(dates, s1);
        cJSON_AddItemToArray(last_50_messages, s2);
        cJSON_AddItemToArray(messages_senders, s3);
    }
}

/*очищает структуру*/
static void delete_reply_from_db(db_get_chat_with_sel_user_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->dest_user_id);
    mx_strdel(&(*reply_from_db)->source_user_id);

    for (int i = 0; i < MAX_MESS_AMNT; i++) {
        mx_strdel(&(*reply_from_db)->dates[i]);
        mx_strdel(&(*reply_from_db)->last_50_messages[i]);
        mx_strdel(&(*reply_from_db)->messages_senders[i]);
    }

    free(*reply_from_db);
    *reply_from_db = NULL;
}
