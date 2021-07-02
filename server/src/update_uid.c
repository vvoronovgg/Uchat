#include "database.h"
#include "server.h"

#define UU "update_uid"

static void make_sql_update(char sql[N], int curr_client_socket, char *curr_client_id);

/*обновляет айди клиента, связанного с его сокетом в БД*/
void update_uid(char **curr_client_id, int curr_client_socket) {
    
    sqlite3 *db = NULL;
    errors *error = NULL;
    int open_try;
    char sql[N];

    init_error_struct(&error);
    open_try = sqlite3_open("sockets.db", &db);

    if (!db) {
        failed_to_open_db("in function 'update_uid': ", &error);
    }

    else {
        make_sql_update(sql, curr_client_socket, *curr_client_id);
        sqlite3_better_exec(&db, sql, NULL, NULL, &error, UU);
        sqlite3_close(db);
    }

    print_error(error->error_message);
    delete_error(&error);
    mx_strdel(curr_client_id);
}

static void make_sql_update(char sql[N], int curr_client_socket, char *curr_client_id) {
    char *socket = mx_itoa(curr_client_socket);

    sprintf(sql, "update sockets SET uid = '%s' where socket = '%s';", curr_client_id, socket);
    mx_strdel(&socket);
}
