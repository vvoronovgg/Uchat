#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void insert_into_table_friends(char *id_for_tablename, char *id_for_value, sqlite3 **pSqlite3, errors **pErrors) {
    if (!id_for_tablename || !id_for_value || !pSqlite3 || !*pSqlite3 || (*pErrors)->error_message)
        return;
    char sql_statemet[N];
    sprintf(sql_statemet, "INSERT INTO friends_%s (number, friend_id) VALUES ((SELECT IFNULL(MAX(number), 0) + 1 FROM friends_%s), '%s');", id_for_tablename, id_for_tablename, id_for_value);
    sqlite3_better_exec(pSqlite3, sql_statemet, 0, 0, pErrors, "insert_into_table_friends");
}
