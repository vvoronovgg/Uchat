#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

#define DCFD "delete_client_from_db"

static void make_sql_delete(char sql[N], int socket);

/*удаляет клиента из БД по сокету*/
void delete_client_from_db(int socket_to_delete) {
    write(2,"Start\n",strlen("Start\n"));
    sqlite3 *db = NULL;
    errors *error = NULL;
    int open_try;
    char sql[N];

    init_error_struct(&error);
    write(2,"a\n",strlen("a\n"));
    open_try = sqlite3_open("sockets.db", &db);
    write(2,"b\n",strlen("b\n"));
    if (!db) {
        write(2,"c\n",strlen("c\n"));
        failed_to_open_db("in function 'delete_client_from_db': ", &error);
    }

    else {
        write(2,"e\n",strlen("e\n"));
        make_sql_delete(sql, socket_to_delete);
        write(2,sql,strlen(sql));
        sqlite3_better_exec(&db, sql, NULL, NULL, &error, DCFD);
        write(2,"n\n",strlen("n\n"));
        sqlite3_close(db);
    }
    write(2,"z\n",strlen("z\n"));
    print_error(error->error_message);
    delete_error(&error);
    write(2,"Finish delete client\n",strlen("Finish delete client\n"));
}

static void make_sql_delete(char sql[N], int socket) {
    char *_socket = mx_itoa(socket);

    sprintf(sql, "delete from sockets where socket = '%s';", _socket);
    mx_strdel(&_socket);
}
