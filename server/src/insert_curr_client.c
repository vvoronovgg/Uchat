#include "server.h"
#include "database.h"

#define ICC "insert_curr_client"

static void make_sql_insert(char sql[N], int curr_socket);

/*вставляет текущего клиента (его сокет) в БД*/
void insert_curr_client(int curr_socket) {
    sqlite3 *db = NULL;
    errors *error = NULL;
    int open_try;
    char sql[N];

    init_error_struct(&error);
    open_try = sqlite3_open("sockets.db", &db);

    if (!db) {
        failed_to_open_db("in function 'insert_curr_client': ", &error);
    }

    else {
        make_sql_insert(sql, curr_socket);
        sqlite3_better_exec(&db, sql, NULL, NULL, &error, ICC);
        sqlite3_close(db);
    }

    print_error(error->error_message);
    delete_error(&error);
}

static void make_sql_insert(char sql[N], int curr_socket) {
    char *socket = mx_itoa(curr_socket);

    sprintf(sql, "insert into sockets (socket, uid) values ('%s', '-1');", socket);
    mx_strdel(&socket);
}
