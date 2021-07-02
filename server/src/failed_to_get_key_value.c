#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*неудача достать значения ключа в json-строке, фришит 'func-message-s'*/
void failed_to_get_key_value(errors **error, char **func_message1, char *func_message2) {
    if (error && *error && func_message1 && *func_message1 && func_message2) {
        (*error)->error_message = mx_strjoin(*func_message1, func_message2);
        (*error)->error_number = mx_strdup(ER_JSN_TO_STRUCT);
        mx_strdel(func_message1);
        mx_strdel(&func_message2);
    }
}
