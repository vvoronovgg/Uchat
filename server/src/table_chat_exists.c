#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*проверяет: существует ли таблица chat_[uid1]_[uid2] или chat_[uid2]_[uid1].
  возвращает:
        NULL - если не существует ни одна таблица или если структура errors заполнена
        chat_[uid2]_[uid1] или chat_[uid1]_[uid2] - если одна из них существует. (динамическая память)
        DON'T USE THIS FUNCTION
*/
char *table_chat_exists(char *uid1, char *uid2, sqlite3 **db, errors **error) {
    if (!uid2 || !uid1 || !db || !*db || (*error)->error_message)
        return NULL;

    char buffer[N];
    char *table_name = NULL;  
    sprintf(buffer, "chat_%s_%s", uid1, uid2);   
        
    table_name = table_exists(buffer, db, error);
    
    if (!table_name && !(*error)->error_message) {
        sprintf(buffer, "chat_%s_%s", uid2, uid1);
        table_name = table_exists(buffer, db, error);
    }

    return table_name;
}
