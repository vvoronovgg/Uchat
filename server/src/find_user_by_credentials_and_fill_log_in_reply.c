#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"


#define FUBCFLIR "'find_user_by_credentials_and_fill_log_in_reply'"

static void set_credential_value(char **credential_value, char *credential, db_user_log_in_req **log_in_req);
static void sql_user_is_in_db(db_user_log_in_req *log_in_req, char sql[N], errors *error);
static int callback(void *here, int count, char **data, char **columns);

/*находит пользователя по логину/номеру телефона и паролю в БД && записывает ответ в log_in_reply*/
void find_user_by_credentials_and_fill_log_in_reply(db_user_log_in_reply **log_in_reply, 
                                                    db_user_log_in_req *log_in_req, sqlite3 **db, errors **error) {
    if (!log_in_req || !*log_in_reply 
    || !log_in_reply || !db || !*db)
        return;
    
    char sql[N];
    char *credential = NULL;
    char *credential_value = NULL;
    

    credential = by_phone_number_or_login(log_in_req->user_phone_number, db, error, FUBCFLIR);
    set_credential_value(&credential_value, credential, &log_in_req);
    sql_user_is_in_db(log_in_req, sql, *error);
    sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_logged_in, error, FUBCFLIR);

    if ((*log_in_reply)->user_logged_in && mx_strcmp((*log_in_reply)->user_logged_in, "1") == 0 ) {
        sql_make_simple_select_in("user_first_name", "users", credential, credential_value, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_first_name, error, FUBCFLIR);
        
        sql_make_simple_select_in("user_last_name", "users", credential, credential_value, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_last_name, error, FUBCFLIR);
       
        sql_make_simple_select_in("user_id", "users", credential, credential_value, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_id, error, FUBCFLIR);
       
        sql_make_simple_select_in("user_phone_number", "users", credential, credential_value, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_phone_number, error, FUBCFLIR);
        
        sql_make_simple_select_in("user_login", "users", credential, credential_value, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_login, error, FUBCFLIR);

        sql_make_simple_select_in("user_email", "users", credential, credential_value, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*log_in_reply)->user_email, error, FUBCFLIR);

        get_info_from_friends_table(log_in_reply, error, db);
    }
}

static void set_credential_value(char **credential_value, char *credential, db_user_log_in_req **log_in_req) {
    if (!log_in_req || !*log_in_req || !credential || !credential_value)
        return;
    
    if (mx_strcmp(credential, "user_phone_number") == 0) {
        *credential_value = (*log_in_req)->user_phone_number;
    }

    else if (mx_strcmp(credential, "user_login") == 0) {
        *credential_value = (*log_in_req)->user_login;
    }
}

static void sql_user_is_in_db(db_user_log_in_req *log_in_req, char sql[N], errors *error) {
    if (!log_in_req || !sql || error->error_message)
        return;

    char *newstr = NULL;
    newstr = mx_replace_substr(log_in_req->user_password, "'", "''");
    sprintf(sql, "select count(*) from users where user_login = '%s' and user_password = '%s';", 
            log_in_req->user_login, newstr);
    mx_strdel(&newstr);
}

//----------------------------------------------CALLBACKS---------------------------------------------
//----------------------------------------------------------------------------------------------------

static void save_data( char *what, char **where);

static int callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data(data[0], here);
    return 0;
}

static void save_data( char *what, char **where) {
    *where = mx_strdup(what);
}
