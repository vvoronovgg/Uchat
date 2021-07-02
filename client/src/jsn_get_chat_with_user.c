#include "client.h"

#define W 2000
static char *get_value(cJSON *object, char *key, char **er_msg);

GMutex mutex1;

char *jsn_get_chat_with_user(void) {  //добавьте этот прототип в общий header!!!
    cJSON *object = NULL;
    char *str = NULL;
    char *str1 = mx_strnew(W);
    char *doing = strdup ("1");
    char *type = NULL;   //вывод
    char *error = NULL;

    object = cJSON_CreateObject(); //создается объект object
    cJSON_AddStringToObject(object, "type", "chat_with_req"); //создается ключ "type" и значение "log_in" в объекте object
    cJSON_AddStringToObject(object, "dest_user_id", cleint_data.chat->friend_id);  //создается ключ "user_login" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "source_user_id", cleint_data.chat->your_id);   //создается ключ "user_password" и значение "none" в объекте object
    str = cJSON_Print(object);  //конвертирую json в строку
    if (!str)
        write(2,"PRINT\n",6);
    // cJSON_Delete(object);   //удаляю объект user, содержащий свои ключи - значения
    
    object = NULL;
    g_mutex_lock(&mutex1);
    send(cleint_data.soketfd, str, 2000,0);
    recv(cleint_data.soketfd, str1, 2000, 0);
    g_mutex_unlock(&mutex1);

    printf("%s\n",str1);
    printf("strlenstr%lu\n",strlen(str1));

    object = cJSON_Parse(str1);
    if (!object)
        printf("NONE OBJECT");
    type = strdup(get_value(object, "type", &error));
    printf("%s\n", type);
    if (strcmp(type, "error") == 0) {
        write(2,"OG\n",3);
        doing = strdup(get_value(object, "message",&error));
        // free(str1);
        return doing;
    }
    printf("%i\n", strcmp(type,"chat_with_reply"));
    if (strcmp(type,"chat_with_reply") == 0) {
        write(2,"hello7" ,6);
        write(2, "\n", 1);
        doing = strdup("1");
        write(2,"hello1" ,6);
        write(2, "\n", 1);
        cleint_data.chat->last_50_massege = parse_arr(str1, "last_50_messages");
        cleint_data.chat->messages_senders = parse_arr(str1, "messages_senders");
        cleint_data.chat->dates = parse_arr(str1, "dates");
        write(2,"hello3" ,6);
        write(2, "\n", 1);
        // cJSON_Delete(object);   //удаляю json 
        object = NULL;
        printf("%s\n", doing);
        return doing;
    }
    else {
        doing = strdup("0");
        cJSON_Delete (object);
        write(2,"hello4" ,6);
        write(2, "\n", 1);
        return doing;
    }
    write(2,"hello" ,5);
    write(2, "\n", 1);
}

/*достает значение из заданного ключа с объекта*/
static char *get_value(cJSON *object, char *key, char **er_msg) {
    cJSON *Item = NULL;
    char *value = NULL;
    char message[100];

    if (!*er_msg) {     //если не было раньше ошибки
        Item = cJSON_GetObjectItemCaseSensitive(object, key);   //достаю значение ключа key в объекте object

        if (!Item) {        //если не нашло ключ key: (будет записана часть ошибки)
            sprintf(message, " Can't get the value from key '%s' from json-string ", key);
            *er_msg = strdup(message);   //записываю ЧАСТЬ ошибки (чтобы потом указать в какой функции была найдена ошибка)
            return NULL;
        }

        else {      //если нашло ключ key: (все в порядке)
            value = strdup(Item->valuestring);    
            //cJSON_DeleteItemFromObjectCaseSensitive(object, key);   //удаляю ключ key и значение из object
            return value;
        }
    }
    return NULL;   //если уже появилась ранее ошибка - возвращаю NULL
}
