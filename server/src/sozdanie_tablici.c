//
// Created by Andrii Danylenko on 11/4/20.
//
#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void sozdanie_tablici(sqlite3 **db, char *tablica, errors **error) {
    if (!tablica || !db || !*db || (*error)->error_message)
        return;
    char sql_statemet[N];

    sprintf(sql_statemet, "CREATE TABLE %s (sms_id INTEGER, sender_id TEXT, receiver_id TEXT, sms TEXT, date TEXT);", tablica);
    sqlite3_better_exec(db, sql_statemet, 0, 0, error, "sozdanie_tablici");
}
