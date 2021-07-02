#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*возвращает ответ из БД на запрос 'получить чат с выбранным пользователем'*/
void get_chat_with_reply(char *json, char **reply) {
    errors *error = NULL;

    init_error_struct(&error);
    db_get_chat_with_sel_user_req *chat_with_req = jsn_to_chat_with_req(json, &error);
    db_get_chat_with_sel_user_reply *chat_with_reply = get_chat_with_req_to_reply(&chat_with_req, &error);
    *reply = chat_with_reply_to_jsn(&chat_with_reply);

    if (*reply == 0)
        error_json(reply, &error);
    delete_error(&error);
}
