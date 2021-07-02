#include "client.h"

//static char *get_value(cJSON *object, char *key);

GMutex mutex3;

void jsn_send_message(void) {  //добавьте этот прототип в общий header!!!
    cJSON *object = NULL;
    char *str = NULL;
    // char *str1 = mx_strnew(2000);
    // char *type = NULL;

    object = cJSON_CreateObject(); //создается объект object
    cJSON_AddStringToObject(object, "type", "private_message_req"); //создается ключ "type" и значение "log_in" в объекте object
    cJSON_AddStringToObject(object, "sender_id", cleint_data.chat->your_id);  //создается ключ "user_login" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "receiver_id", cleint_data.chat->friend_id);   //создается ключ "user_password" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "message", cleint_data.chat->message);
    cJSON_AddStringToObject(object, "date", cleint_data.chat->time);
    printf("%s\n",cleint_data.chat->time);
    str = cJSON_Print(object);  //конвертирую json в строку
    if (!str)
        write(2,"PRINT\n",6);
    cJSON_Delete(object);   //удаляю объект user, содержащий свои ключи - значения
    
    printf("str: %s\n", str);
    g_mutex_lock(&mutex3);
    send(cleint_data.soketfd, str, 2000,0);
    g_mutex_unlock(&mutex3);

    printf("%s\n",str);
    printf("strlenstr%lu\n",strlen(str));
    free(str);
}
