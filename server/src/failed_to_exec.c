#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

void failed_to_exec(const char *message, errors **error) {
    if (message && error && *error) {
        (*error)->error_message = mx_strdup(message);
        (*error)->error_number = mx_strdup(ER_DB_EXEC);
    }
}
