#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*возвращает ответ из БД на запрос 'личное сообщение'*/
void get_pr_message_reply(char *json, char **reply) {
    errors *error = NULL;

    init_error_struct(&error);
    db_private_message_req *private_message_req = jsn_to_pr_message_req(json, &error);
    db_private_message_reply *private_message_reply = private_message_req_to_reply(&private_message_req, &error);
    *reply = private_mess_reply_to_jsn(&private_message_reply);

    if (*reply == 0)
        error_json(reply, &error);
    delete_error(&error);
}
