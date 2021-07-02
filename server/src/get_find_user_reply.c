#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*возвращает ответ из БД на запрос 'поиск пользователя'*/
void get_find_user_reply(char *json, char **reply) {
    errors *error = NULL;

    init_error_struct(&error);
    db_find_user_req *find_user_request = jsn_to_find_user_req(json, &error);
    db_find_user_reply *find_user_reply = find_user_req_to_reply(&find_user_request, &error);
    *reply = find_user_reply_to_jsn(&find_user_reply);

    if (*reply == 0)
        error_json(reply, &error);
    delete_error(&error);
}
