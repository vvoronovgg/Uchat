#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static int callback(void *here, int count, char **data, char **columns);
//возвращает название таблицы в лучае успешной проверки или NULL в случае руины
char *proverka_tablic(char *sender_id, char *reciever_id, sqlite3 **db) {
    if (!sender_id || !reciever_id || !db || !*db)
        return NULL;
    char sql_req[N];
    char *err_msg = NULL;
    char result[N];
    char *finally_result = NULL;
    char *direct = NULL;

    sprintf(sql_req, "SELECT sms_id FROM chat_%s_%s LIMIT 1;", sender_id, reciever_id);
    int rc = sqlite3_exec(*db, sql_req, callback, &direct, &err_msg);

    mx_strdel(&err_msg);
        
    if (direct) {
        sprintf(result, "chat_%s_%s", sender_id, reciever_id);
        finally_result = mx_strdup(result);
        mx_strdel(&direct);
        return finally_result;
    }
    
    else if (!direct) {
        sprintf(sql_req, "SELECT sms_id FROM chat_%s_%s LIMIT 1;", reciever_id, sender_id);
        rc = sqlite3_exec(*db, sql_req, callback, &direct, &err_msg);
        if (err_msg)
            mx_strdel(&err_msg);

        if (direct) {
            sprintf(result, "chat_%s_%s", reciever_id, sender_id);
            finally_result = mx_strdup(result);
            mx_strdel(&direct);
            return finally_result;
        }

        else {
            return NULL;
        }
    }
    
    return NULL;
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
