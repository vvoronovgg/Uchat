#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void m_allocation_initializing(db_change_user_passw_reply **change_passwd_reply); //выделяет и заполняет структуру нач. значениями
static void free_change_passwd_req(db_change_user_passw_req **change_passwd_req);   //удаляет change_passwd_req (запрос)
static void delete_reply_from_db(db_change_user_passw_reply **reply_from_db);

/*возвращает ответ change_passwd_reply на запрос change_passwd_req*/
db_change_user_passw_reply *change_passwd_req_to_reply(db_change_user_passw_req **change_passwd_req, errors **error) {
    if (!*change_passwd_req || (*error)->error_message)
        return NULL;

    db_change_user_passw_reply *change_passwd_reply = NULL;
    sqlite3 *db = NULL;

    m_allocation_initializing(&change_passwd_reply);
    open_db(&db);

    if (db == NULL) {       //в случае не успеха открытия БД
        failed_to_open_db(" in function 'change_passwd_req_to_reply' ", error);
        free_change_passwd_req(change_passwd_req);
        return NULL;
    }

    try_to_update_passwd(&change_passwd_reply, *change_passwd_req, &db, error);
    
    sqlite3_close(db);
    free_change_passwd_req(change_passwd_req);

    if ((*error)->error_message) 
        delete_reply_from_db(&change_passwd_reply);

    return change_passwd_reply;
}

/*выделяет память и инициализирует структуру начальными значениями*/
static void m_allocation_initializing(db_change_user_passw_reply **change_passwd_reply) {
    *change_passwd_reply = (db_change_user_passw_reply*)malloc(sizeof(db_change_user_passw_reply));
    (*change_passwd_reply)->password_changed = NULL;
}

/*очищает память (удаляет запрос смена пароля)*/
static void free_change_passwd_req(db_change_user_passw_req **change_passwd_req) {
    mx_strdel(&(*change_passwd_req)->new_password);
    mx_strdel(&(*change_passwd_req)->old_password);
    mx_strdel(&(*change_passwd_req)->user_id);
    free(*change_passwd_req);
    *change_passwd_req = NULL;
}

/*очищает структуру, в случае ошибки*/
static void delete_reply_from_db(db_change_user_passw_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->password_changed);
    free(*reply_from_db);
    *reply_from_db = NULL;
}
