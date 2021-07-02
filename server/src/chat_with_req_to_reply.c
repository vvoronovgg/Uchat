#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void m_allocation_initializing(db_get_chat_with_sel_user_reply **get_chat_with); //выделяет и заполняет структуру нач. значениями
static void free_get_chat_with_req(db_get_chat_with_sel_user_req **get_chat_with_req);   //удаляет get_chat_with_req (запрос)
static void delete_reply_from_db(db_get_chat_with_sel_user_reply **reply_from_db);

/*возвращает ответ get_chat_with на запрос get_chat_with*/
db_get_chat_with_sel_user_reply *get_chat_with_req_to_reply(db_get_chat_with_sel_user_req **get_chat_with_req, errors **error) {
    if (!*get_chat_with_req)
        return NULL;

    db_get_chat_with_sel_user_reply *get_chat_with = NULL;
    sqlite3 *db = NULL;

    m_allocation_initializing(&get_chat_with);
    open_db(&db);

    if (db == NULL) {       //в случае не успеха открытия БД
        failed_to_open_db(" in function 'get_chat_with_req_to_reply' ", error);
        free_get_chat_with_req(get_chat_with_req);
        return NULL;
    }
    get_last_chat(&get_chat_with, *get_chat_with_req, &db, error);
    sqlite3_close(db);
    free_get_chat_with_req(get_chat_with_req);

    if ((*error)->error_message) 
        delete_reply_from_db(&get_chat_with);

    return get_chat_with;
}

/*выделяет память и инициализирует структуру начальными значениями*/
static void m_allocation_initializing(db_get_chat_with_sel_user_reply **get_chat_with) {
    *get_chat_with = (db_get_chat_with_sel_user_reply*)malloc(sizeof(db_get_chat_with_sel_user_reply));
    (*get_chat_with)->dest_user_id = NULL;
    (*get_chat_with)->source_user_id = NULL;
    (*get_chat_with)->row = 0;

    for (int i = 0; i < MAX_MESS_AMNT; i++) {
        (*get_chat_with)->dates[i] = NULL;
        (*get_chat_with)->last_50_messages[i] = NULL;
        (*get_chat_with)->messages_senders[i] = NULL;
    }
}

/*очищает память (удаляет запрос log_in)*/
static void free_get_chat_with_req(db_get_chat_with_sel_user_req **get_chat_with_req) {
    mx_strdel(&(*get_chat_with_req)->dest_user_id);
    mx_strdel(&(*get_chat_with_req)->source_user_id);
    free(*get_chat_with_req);
    *get_chat_with_req = NULL;
}

/*очищает структуру, в случае ошибки*/
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
