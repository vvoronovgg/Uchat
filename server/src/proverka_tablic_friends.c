#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

//возвращает название таблицы в cлучае успешной проверки или NULL в случае руины
void proverka_tablic_friends(char *id_for_check, sqlite3 **db, errors **error) {
    if (!id_for_check || !db || !*db || (*error)->error_message)
        return;
    char sql_req[N];
    //char *err_msg = NULL;

    sprintf(sql_req, "SELECT number FROM friends_%s LIMIT 1;", id_for_check);
    //int rc = sqlite3_exec(*db, sql_req, 0, 0, &err_msg);
    //printf("\n error_in_source_exec = %s\n", err_msg);
    sqlite3_better_exec(db, sql_req, 0, 0, error, "proverka_tablic_friends");

}
