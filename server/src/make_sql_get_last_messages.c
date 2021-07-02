#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*создание sql-запроса для БД, чтобы достать 50 последних сообщений*/
void make_sql_get_last_messages(char sql[N], char *table_name) {
    if (!sql || !table_name)
        return;
    char *max_len = mx_itoa(MAX_MESS_AMNT);

    sprintf(sql, "select sender_id, sms, date from (SELECT * FROM %s ORDER BY sms_id DESC LIMIT %s) ORDER BY sms_id;", table_name, max_len);
    mx_strdel(&max_len);
}
