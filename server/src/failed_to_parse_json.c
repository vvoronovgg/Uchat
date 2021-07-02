#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*неудачный парсинг json-строки, фришит 'func_message'*/
void failed_to_parse_json(errors **error, char *func_message) {
    if (error && *error && func_message) {
        (*error)->error_message = mx_strjoin(func_message, " failed to parse json-string ");
        (*error)->error_number = mx_strdup(ER_JSN_PARSE);
        mx_strdel(&func_message);
    }
}
