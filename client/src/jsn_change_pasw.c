#include "client.h"

static char *get_value(cJSON *object, char *key, char **er_msg);

char *jsn_change_pasw(void) {
    cJSON *object = NULL;
    char *str = NULL;
    char *str1 = mx_strnew(2000);
    char *doing = strdup ("1");
    char *type = NULL;   //вывод
    char *error = NULL;

    object = cJSON_CreateObject(); //создается объект object
    cJSON_AddStringToObject(object, "type", "change_password_req"); //создается ключ "type" и значение "log_in" в объекте object
    cJSON_AddStringToObject(object, "user_id", cleint_data.login_jsn->user_id);  //создается ключ "user_login" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "old_password", cleint_data.login_jsn->passw);   //создается ключ "user_password" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "new_password", cleint_data.profile->new_pass);
    str = cJSON_Print(object);  //конвертирую json в строку
    if (!str)
        write(2,"PRINT\n",6);
    object = NULL;
    
    send(cleint_data.soketfd, str, 2000,0);
    recv(cleint_data.soketfd, str1, 2000, 0);

    printf("%s\n",str1);
    printf("strlenstr%lu\n",strlen(str1));

    object = cJSON_Parse(str1);

    if (!object)
        printf("NONE OBJECT");
    type = strdup(get_value(object, "type",&error));
    if (strcmp(type, "error") == 0) {
        doing = strdup(get_value(object, "message",&error));
        return doing;
    }
    if (strcmp(type,"change_password_reply") == 0) {
        doing = strdup(get_value(object, "password_changed",&error));
        return doing;
    }
    return doing;
}

static char *get_value(cJSON *object, char *key, char **er_msg) {
    cJSON *Item = NULL;
    char *value = NULL;
    char message[100];

    if (!*er_msg) {     //если не было раньше ошибки
        Item = cJSON_GetObjectItemCaseSensitive(object, key);

        if (!Item) {
            sprintf(message, " Can't get the value from key '%s' from json-string ", key);
            *er_msg = strdup(message);   
            return NULL;
        }

        else {
            value = strdup(Item->valuestring);    
            return value;
        }
    }
    return NULL;   //если уже появилась ранее ошибка - возвращаю NULL
}
