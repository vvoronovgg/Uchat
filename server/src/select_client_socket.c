#include "server.h"
#include "database.h"

#define SCS "select_client_socket"

static int callback(void *here, int count, char **data, char **columns);

/*достает сокет клиента-получателя из БД по айди получателя*/
int select_client_socket(char **receiver_id) {
    sqlite3 *db = NULL;
    errors *error = NULL;
    int open_try;
    char sql[N];
    char *callback_receiver_socket = NULL;
    int receiver_socket = -1;

    init_error_struct(&error);
    open_try = sqlite3_open("sockets.db", &db);

    if (!db) {
        failed_to_open_db("in function 'select_client_socket': ", &error);
    }

    else {
        sql_make_simple_select_in("socket", "sockets", "uid", *receiver_id, sql, error);
        sqlite3_better_exec(&db, sql, callback, &callback_receiver_socket, &error, SCS);
        sqlite3_close(db);

        if (callback_receiver_socket) {
            receiver_socket = mx_atoi(callback_receiver_socket);
            mx_strdel(&callback_receiver_socket);
        }
    }

    mx_strdel(receiver_id);
    print_error(error->error_message);
    delete_error(&error);
    return receiver_socket;
}

static void save_data(char *what, char **where);

static int callback(void *here, int count, char **data, char **columns) {
    int prosto_tak;
    if (count && data && columns) prosto_tak = 1;

    save_data(data[0], here);
    return 0;
}

static void save_data(char *what, char **where) {
    *where = mx_strdup(what);
}
