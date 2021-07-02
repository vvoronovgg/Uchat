#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

//void insert_into_table(char *id, char *id1, sqlite3 **pSqlite3, errors **pErrors);
void fill_table_friends(db_private_message_req *pReq, sqlite3 **pSqlite3, errors **pErrors) {
    if (!pReq || !pSqlite3 || !*pSqlite3 || (*pErrors)->error_message)
        return;

    if (proverka_existence_id(pReq->sender_id, pReq->receiver_id, pSqlite3) == false) {
        insert_into_table_friends(pReq->sender_id, pReq->receiver_id, pSqlite3, pErrors);
    }
    if(!(*pErrors)->error_message && proverka_existence_id(pReq->receiver_id, pReq->sender_id, pSqlite3) == false) {
        insert_into_table_friends(pReq->receiver_id, pReq->sender_id, pSqlite3, pErrors);
    }
}


