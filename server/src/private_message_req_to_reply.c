#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void m_allocation_initializing(db_private_message_reply **pr_mess_reply);
static void free_pr_mess_req(db_private_message_req **private_message);
static void delete_reply_from_db(db_private_message_reply **reply_from_db);


/*возвращает ответ private_message_reply на запрос private_message_req*/
db_private_message_reply *private_message_req_to_reply(db_private_message_req **private_message_req, 
                                                       errors **error) {
    if (!private_message_req || !*private_message_req ||
        (*error)->error_message)
        return NULL;

    db_private_message_reply *pr_mess_reply = NULL;
    sqlite3 *db = NULL;

    m_allocation_initializing(&pr_mess_reply);
    open_db(&db);

    if (db == NULL) {       //в случае не успеха открытия БД
        failed_to_open_db(" in function 'private_message_req_to_reply' ", error);
        delete_reply_from_db(&pr_mess_reply);
    }
    
    check_user(*private_message_req, error, &db);
    add_private_message_to_db(*private_message_req, &db, error);
    proverka_tablic_friends((*private_message_req)->sender_id, &db, error);
    proverka_tablic_friends((*private_message_req)->receiver_id, &db, error);
    fill_table_friends(*private_message_req, &db, error);

    
    if ((*error)->error_message) 
        delete_reply_from_db(&pr_mess_reply);
    
    if (!(*error)->error_message && private_message_req && *private_message_req) {     //информация о сообщении
        pr_mess_reply->new_message = mx_strdup((*private_message_req)->message);
        pr_mess_reply->date = mx_strdup((*private_message_req)->date);
    }
    
    get_user_details(&pr_mess_reply, *private_message_req, error, &db);
    free_pr_mess_req(private_message_req);
    sqlite3_close(db);
    return pr_mess_reply;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              

/*выделяет память и инициализирует структуру начальными значениями*/
static void m_allocation_initializing(db_private_message_reply **pr_mess_reply) {
    *pr_mess_reply = (db_private_message_reply*)malloc(sizeof(db_private_message_reply));
    (*pr_mess_reply)->row = 0;
    (*pr_mess_reply)->receiver_id = NULL;
    (*pr_mess_reply)->sender_f_name = NULL;
    (*pr_mess_reply)->sender_id = NULL;
    (*pr_mess_reply)->sender_l_name = NULL;
    (*pr_mess_reply)->sender_login = NULL;
    (*pr_mess_reply)->sender_email = NULL;
    (*pr_mess_reply)->sender_ph_number = NULL;
    (*pr_mess_reply)->date = NULL;
    (*pr_mess_reply)->new_message = NULL;
}

/*очищает память (удаляет запрос private_message)*/
static void free_pr_mess_req(db_private_message_req **private_message) {
    mx_strdel(&(*private_message)->date);
    mx_strdel(&(*private_message)->message);
    mx_strdel(&(*private_message)->receiver_id);
    mx_strdel(&(*private_message)->sender_id);
    free(*private_message);
    *private_message = NULL;
}

/*очищает структуру, в случае ошибки*/
static void delete_reply_from_db(db_private_message_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->receiver_id);
    mx_strdel(&(*reply_from_db)->sender_f_name);
    mx_strdel(&(*reply_from_db)->sender_id);
    mx_strdel(&(*reply_from_db)->sender_l_name);
    mx_strdel(&(*reply_from_db)->sender_login);
    mx_strdel(&(*reply_from_db)->sender_email);
    mx_strdel(&(*reply_from_db)->sender_ph_number);
    mx_strdel(&(*reply_from_db)->date);
    mx_strdel(&(*reply_from_db)->new_message);
    free(*reply_from_db);
    *reply_from_db = NULL;
}
