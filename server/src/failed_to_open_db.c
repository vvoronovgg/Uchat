#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*неудача открыть бд*/
void failed_to_open_db(const char *err_msg, errors **error) {
    if (err_msg && error && *error) {
        (*error)->error_message = mx_strjoin(err_msg, " failed to open database " );
        (*error)->error_number = mx_strdup(ER_DB_OPEN);
    }
}
