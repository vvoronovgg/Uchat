#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*инициализация структуры ошибок*/
void init_error_struct(errors **error) {
    *error = (errors*)malloc(sizeof(errors));
    (*error)->error_message = NULL;
    (*error)->error_number = NULL;
}
