#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

/*формирует нужную json-строку для отсылания ошибки*/
void error_json(char **reply, errors **error) {
    cJSON *object = NULL;

    object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "type", "error");
    cJSON_AddStringToObject(object, "number", (*error)->error_number);
    cJSON_AddStringToObject(object, "message", (*error)->error_message);

    *reply = cJSON_Print(object);
    cJSON_Delete(object);
}
