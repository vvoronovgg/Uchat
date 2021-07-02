/*//
// Created by Andrii Danylenko on 11/4/20.
//
#include "database.h"
#include "libmx.h"

void zapolnenie_tablici(char *tablica, db_private_message_req *private_message, sqlite3 **db, errors **error) {
    if (!tablica || !private_message || !db || !*db || (*error)->error_message)
        return;
    char sql_statemet[N];
    sprintf(sql_statemet, "INSERT INTO %s (sms_id, sender_id, receiver_id, sms, date) VALUES ((SELECT IFNULL(MAX(sms_id), 0) + 1 FROM %s), '%s', '%s', '%s', '%s');",
            tablica, tablica, private_message->sender_id, private_message->receiver_id, private_message->message, private_message->date);
    sqlite3_better_exec(db, sql_statemet, 0, 0, error, "zapolnenie_tablici");
    mx_strdel(&tablica);
}*/
//
// Created by Andrii Danylenko on 11/4/20.
//
#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void zapolnenie_tablici(char *tablica, db_private_message_req *private_message, sqlite3 **db, errors **error) {
    if (!tablica || !private_message || !db || !*db || (*error)->error_message)
        return;
    char sql_statemet[N];
    char *replaced_str = NULL;
    replaced_str = mx_replace_substr(private_message->message, "'", "''");

    sprintf(sql_statemet, "INSERT INTO %s(sms_id, sender_id, receiver_id, sms, date) VALUES((SELECT IFNULL(MAX(sms_id), 0) + 1 FROM %s), '%s', '%s', '%s', '%s');", 
    tablica, tablica, private_message->sender_id, private_message->receiver_id, replaced_str, private_message->date);
    sqlite3_better_exec(db, sql_statemet, 0, 0, error, "zapolnenie_tablici");
    mx_strdel(&tablica);
    mx_strdel(&replaced_str);
}
