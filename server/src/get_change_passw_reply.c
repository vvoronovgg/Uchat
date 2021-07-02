#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*возвращает ответ из БД на запрос 'смена пароля'*/
void get_change_passw_reply(char *json, char **reply) {
    errors *error = NULL;

    init_error_struct(&error);
    db_change_user_passw_req *change_passwd_req = jsn_to_change_passw_req(json, &error);
    db_change_user_passw_reply *change_passwd_reply = change_passwd_req_to_reply(&change_passwd_req, &error);
    *reply = change_passwd_reply_to_jsn(&change_passwd_reply);

    if (*reply == 0)
        error_json(reply, &error);
    delete_error(&error);
}
