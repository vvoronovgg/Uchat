#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*возвращает ответ из БД на запрос 'регистрация пользователя'*/
void get_registration_reply(char *json, char **reply) {
    errors *error = NULL;

    init_error_struct(&error);
    db_user_registration_req *reg_req = jsn_to_registration_req(json, &error);
    db_user_registration_reply *reg_reply = checking_matches_in_table_users(&reg_req, &error);
    *reply = registration_reply_to_jsn(&reg_reply);

    if (*reply == 0)
        error_json(reply, &error);
    delete_error(&error);
}
