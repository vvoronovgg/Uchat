#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*удаляю структуру errors*/
void delete_error(errors **error) {
    if (*error) {
        mx_strdel(&(*error)->error_message);
        mx_strdel(&(*error)->error_number);
        free(*error);
        *error = NULL;
    }
}
