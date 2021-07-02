#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*неправильный ключ 'type' в json-строке, фришит 'func_message'*/
void incorrect_key_type(errors **error, char *func_message) {
    if (error && *error && func_message) {
        (*error)->error_message = mx_strjoin(func_message, " incorrect key 'type' in json-string ");
        (*error)->error_number = mx_strdup(ER_JSN_TYPE);
        mx_strdel(&func_message);
    }
}
