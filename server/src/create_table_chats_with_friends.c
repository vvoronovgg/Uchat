//
// Created by Andrii Danylenko on 11/9/20.
//
#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void create_table_chats_with_friends(sqlite3 *db, errors **error, db_user_registration_reply *reply) {
    if (!reply || !db || (*error)->error_message)
        return;

    char sql_statemet_sozdania_tablici[N];

    sprintf(sql_statemet_sozdania_tablici, "CREATE TABLE friends_%s(number INTEGER, friend_id TEXT);", reply->user_id);
    sqlite3_better_exec(&db, sql_statemet_sozdania_tablici, 0, 0, error, "create_table_chats_with_friends");
}
