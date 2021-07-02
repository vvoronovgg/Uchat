#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void m_allocation_initializing(db_find_user_reply **find_user_reply); //выделяет и заполняет структуру нач. значениями
static void free_find_user_req(db_find_user_req **find_user_req);   //удаляет find_user_req (запрос)
static void delete_reply_from_db(db_find_user_reply **reply_from_db);

/*возвращает ответ find_user_reply на запрос find_user_req*/
db_find_user_reply *find_user_req_to_reply(db_find_user_req **find_user_req, errors **error) {
    if (!*find_user_req)
        return NULL;

    db_find_user_reply *find_user_reply = NULL;
    sqlite3 *db = NULL;

    m_allocation_initializing(&find_user_reply);
    open_db(&db);

    if (db == NULL) {       //в случае не успеха открытия БД
        failed_to_open_db(" in function 'find_user_req_to_reply' ", error);
        free_find_user_req(find_user_req);
        return NULL;
    }

    get_found_user_info(&find_user_reply, *find_user_req, &db, error);     //функция поиска в БД
    
    sqlite3_close(db);
    free_find_user_req(find_user_req);

    if ((*error)->error_message) 
        delete_reply_from_db(&find_user_reply);

    return find_user_reply;
}

/*выделяет память и инициализирует структуру начальными значениями*/
static void m_allocation_initializing(db_find_user_reply **find_user_reply) {
    *find_user_reply = (db_find_user_reply*)malloc(sizeof(db_find_user_reply));
    (*find_user_reply)->f_user_first_name = NULL;
    (*find_user_reply)->f_user_id = NULL;
    (*find_user_reply)->f_user_last_name = NULL;
    (*find_user_reply)->login_found = NULL;
    (*find_user_reply)->f_user_email = NULL;
    (*find_user_reply)->f_user_ph_number = NULL;
}

/*очищает память (удаляет запрос log_in)*/
static void free_find_user_req(db_find_user_req **find_user_req) {
    mx_strdel(&(*find_user_req)->login_to_find);
    free(*find_user_req);
    *find_user_req = NULL;
}

/*очищает структуру, в случае ошибки*/
static void delete_reply_from_db(db_find_user_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->f_user_first_name);
    mx_strdel(&(*reply_from_db)->f_user_last_name);
    mx_strdel(&(*reply_from_db)->f_user_id);
    mx_strdel(&(*reply_from_db)->login_found);
    mx_strdel(&(*reply_from_db)->f_user_email);
    mx_strdel(&(*reply_from_db)->f_user_ph_number);
    free(*reply_from_db);
    *reply_from_db = NULL;
}
