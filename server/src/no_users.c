#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*один из пользователей или все не существуют в БД*/
void no_users(errors **error, const char *was_invoked_in, char *user1_id, char *user2_id) {
    if (error && *error && was_invoked_in && 
        user1_id && *user1_id && user2_id && *user2_id) {
        char full_message[100];

        sprintf(full_message, "no user '%s' or user '%s' in database, in function '%s'", user1_id, user2_id, was_invoked_in);
        (*error)->error_message = mx_strdup(full_message);
        (*error)->error_number = mx_strdup(ER_DB_NO_USERS);
    }
}
