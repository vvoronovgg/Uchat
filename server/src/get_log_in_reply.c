#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*возвращает ответ из БД на запрос 'вход пользователя'*/
void get_log_in_reply(char *json, char **reply) {
    errors *error = NULL;

    init_error_struct(&error);
    db_user_log_in_req *log_in_request = jsn_to_log_in_req(json, &error);
    db_user_log_in_reply *log_in_reply = log_in_req_to_reply(&log_in_request, &error);
    *reply = log_in_reply_to_jsn(&log_in_reply);
    if (*reply == 0)
        error_json(reply, &error);
    delete_error(&error);
}
