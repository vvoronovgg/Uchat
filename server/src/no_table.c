#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*таблица не существует в БД*/
void no_table(errors **error, const char *was_invoked_in, char **table_to_find) {
    if (error && *error && was_invoked_in && table_to_find && *table_to_find) {
        char full_message[100];

        sprintf(full_message, "table '%s' %s '%s'", *table_to_find, "doesn't exist in function", was_invoked_in);
        (*error)->error_message = mx_strdup(full_message);
        (*error)->error_number = mx_strdup(ER_DB_TABLE);
        mx_strdel(table_to_find);
    }
}
