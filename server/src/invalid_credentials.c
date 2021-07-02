#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*не существует user_id или user_password in DB*/
void invalid_credentials(errors **error, const char *was_invoked_in, char *user_id, char *user_password) {
    if (error && *error && was_invoked_in && 
        user_id && user_password) {
        char full_message[150];

        sprintf(full_message, "invalid user_id  '%s' or user_password '%s' in db in function '%s'", user_id, user_password, was_invoked_in);
        (*error)->error_message = mx_strdup(full_message);
        (*error)->error_number = mx_strdup(ER_DB_CREDENTIALS);
    }
}