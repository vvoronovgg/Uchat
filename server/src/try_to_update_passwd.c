#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

#define TTUP "'try_to_update_passwd'"

static void make_sql_select_id_passwd(char sql[N], char *user_id, char *password, errors *error);
static void make_sql_update_passwd(char sql[N], db_change_user_passw_req *change_passwd_req, errors *error);
static int callback(void *here, int count, char **data, char **columns);


/*пытается сменить пароль по айди и старому паролю и заполняет структуру db_change_user_passw_reply*/
void try_to_update_passwd(db_change_user_passw_reply **change_passwd_reply, db_change_user_passw_req *change_passwd_req, 
                                        sqlite3 **db, errors **error) {
    if (!change_passwd_req || !*change_passwd_reply 
    || !change_passwd_reply || !db || !*db || (*error)->error_message)
        return;
    
    char sql[N];
    char **credentials = NULL;
   
    credentials = mx_strarrnew(2);

    make_sql_select_id_passwd(sql, change_passwd_req->user_id, change_passwd_req->old_password, *error);
    sqlite3_better_exec(db, sql, callback, &credentials, error, TTUP);
    
    if (!credentials[0] || !credentials[1]) {
        invalid_credentials(error, TTUP, change_passwd_req->user_id, change_passwd_req->old_password);
    }

    if (credentials[0] && credentials[1] && !(*error)->error_message && 
        mx_strcmp(credentials[0], change_passwd_req->new_password) == 0)  {    //если старый пароль == новому паролю
        (*change_passwd_reply)->password_changed = mx_strdup("0");  //такой пароль уже существует
        mx_del_strarr(&credentials);
        return;
    }
   
    if (credentials[0] && credentials[1] && !(*error)->error_message) {  //если существует user с таким паролем, айди, не было ошибки - меняю пароль
        make_sql_update_passwd(sql, change_passwd_req, *error);
        sqlite3_better_exec(db, sql, NULL, NULL, error, TTUP);
        
        if (!(*error)->error_message) {
            (*change_passwd_reply)->password_changed = mx_strdup("1");  //пароль успешно изменен
        }
    }
    
    mx_del_strarr(&credentials);
}

static void make_sql_select_id_passwd(char sql[N], char *user_id, char *password, errors *error) {
    if (!sql || !user_id || !password || error->error_message)
        return;
    
    char *_password = NULL;

    _password = mx_replace_substr(password, "'", "''");
    sprintf(sql, "select user_password, user_id from users where user_id = '%s' and user_password = '%s';",
            user_id, _password);
    printf("sql: %s\n", sql);
    mx_strdel(&_password);
} 


static void make_sql_update_passwd(char sql[N], db_change_user_passw_req *change_passwd_req, errors *error) {
    if (!sql || !change_passwd_req || error->error_message)
        return;
    char *newpasswd = NULL;
    char *oldpasswd = NULL;

    newpasswd = mx_replace_substr(change_passwd_req->new_password, "'", "''");
    oldpasswd = mx_replace_substr(change_passwd_req->old_password, "'", "''");
    sprintf(sql, "update users set user_password = '%s' where user_id = '%s' and user_password = '%s'",
            newpasswd, change_passwd_req->user_id, oldpasswd);
    mx_strdel(&newpasswd);
    mx_strdel(&oldpasswd);
}

static void save_data(char **what, char ***where);

static int callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data(data, here);
    return 0;
}

static void save_data(char **what, char ***where) {
    (*where)[0] = mx_strdup(what[0]);
    (*where)[1] = mx_strdup(what[1]);
}
