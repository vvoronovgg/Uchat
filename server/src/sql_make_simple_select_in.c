#include "database.h"
#include "libmx.h"

/*записывает в стат. массив sql "полный, простой запрос" select*/
void sql_make_simple_select_in(char *column, char *table, char *key_column, 
                            char *key_value, char sql[N], errors *error) {
    if (!column || !table || !key_column || 
    !key_value || !sql || error->error_message)
        return;

    char *_key_value = NULL;

    _key_value = mx_replace_substr(key_value, "'", "''");
    sprintf(sql, "%s %s %s %s %s %s %s '%s';", "SELECT", column, "from", table, "where", 
            key_column, "=", _key_value);
    mx_strdel(&_key_value);
}
