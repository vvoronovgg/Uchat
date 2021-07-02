#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*
записывает личное сообщение от одного пользователя к другому в БД.
возвращает название таблицы, в которой было записано сообщение
Принимает:
//private_message - структура, которая хранит инфу об этом сообщении; не очищается после использования
//db - адрес на указатель к БД (БД открывается в другой функции)
//error - структура ошибок, куда записываются данные о случившейся ошибки, если что-то пошло не так в функции.
*/
void add_private_message_to_db(db_private_message_req *private_message, sqlite3 **db, errors **error) {
    if (!private_message || !db || !*db || (*error)->error_message)
        return;

    char *err_msg = NULL;
    char *tablica = NULL;
    tablica = proverka_tablic(private_message->sender_id, private_message->receiver_id, db);
    char sql[N];

    if (!tablica) {
        sprintf(sql, "chat_%s_%s", private_message->sender_id, private_message->receiver_id);
        sozdanie_tablici(db, sql, error);
        zapolnenie_tablici(mx_strdup(sql), private_message, db, error);
    }
    
    else {
        zapolnenie_tablici(tablica, private_message, db, error);
        mx_strdel(&err_msg);
    }
}
