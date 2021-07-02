#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

#define GFUI "'get_found_user_info'"

static int callback(void *here, int count, char **data, char **columns);

/*находит пользователя по логину и заполняет структуру db_find_user_reply*/
void get_found_user_info(db_find_user_reply **find_user_reply, db_find_user_req *find_user_req, 
                                        sqlite3 **db, errors **error) {
    if (!find_user_req || !*find_user_reply 
    || !find_user_reply || !db || !*db)
        return;
    
    char sql[N];
    char *is_in_db = NULL;
    
    sql_make_simple_select_in("user_login", "users", "user_login", find_user_req->login_to_find, sql, *error);
    sqlite3_better_exec(db, sql, callback, &is_in_db, error, GFUI);
    
    if (!is_in_db) {
        (*find_user_reply)->login_found = mx_strdup("0");
    } 

    else {
        sql_make_simple_select_in("user_first_name", "users", "user_login", find_user_req->login_to_find, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*find_user_reply)->f_user_first_name, error, GFUI);
        
        sql_make_simple_select_in("user_last_name", "users", "user_login", find_user_req->login_to_find, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*find_user_reply)->f_user_last_name, error, GFUI);
       
        sql_make_simple_select_in("user_id", "users", "user_login", find_user_req->login_to_find, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*find_user_reply)->f_user_id, error, GFUI);

        sql_make_simple_select_in("user_email", "users", "user_login", find_user_req->login_to_find, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*find_user_reply)->f_user_email, error, GFUI);

        sql_make_simple_select_in("user_phone_number", "users", "user_login", find_user_req->login_to_find, sql, *error);
        sqlite3_better_exec(db, sql, callback, &(*find_user_reply)->f_user_ph_number, error, GFUI);

        (*find_user_reply)->login_found = mx_strdup("1");
        mx_strdel(&is_in_db);
    }
}

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
