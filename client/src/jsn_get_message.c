#include "client.h"

static char *get_value(cJSON *object, char *key, char **er_msg);

GMutex mutex;
GMutex mutex1;

void jsn_get_message(void) {
    // t_struct *cleint_data = (t_struct *)client;
    cJSON *object = NULL;
    char *str1 = NULL;
    char *type = NULL;
    char *error = NULL;
    char *messege_doing = strdup ("1");
    while(1)
    {
        puts("qqq");
        str1 = mx_strnew(2000);
        g_mutex_lock(&mutex);
        recv(cleint_data.soketfd, str1, 2000, 0);
        g_mutex_unlock(&mutex);
        if (strlen(str1) == 0){
            puts("Jopa");
            break;
        }
        printf("getmessege:%s\n",str1);
        printf("strlenstrgetmessege%lu\n",strlen(str1));
        object = cJSON_Parse(str1);
        // //free(str1);
        type = strdup(get_value(object, "type",&error)); 
        if (strcmp(type, "error") == 0) {
            messege_doing = strdup(get_value(object, "message",&error));
            printf("%s\n", messege_doing);
        } 
        if (strcmp(type, "private_message_reply") == 0) {
                write(2,"teh1\n",5);
                cleint_data.new_message->sender_id = strdup(get_value(object, "sender_id",&error));     //записываю в структуру значение ключа user_password в объекте object
                cleint_data.new_message->sender_f_name = strdup(get_value(object, "sender_f_name",&error));
                cleint_data.new_message->sender_l_name = strdup(get_value(object, "sender_l_name",&error));
                cleint_data.new_message->sender_login = strdup(get_value(object, "sender_login",&error));
                cleint_data.new_message->sender_email = strdup(get_value(object, "sender_email",&error));
                cleint_data.new_message->sender_ph_number = strdup(get_value(object, "sender_ph_number",&error));
                cleint_data.new_message->receiver_id = strdup(get_value(object, "receiver_id",&error));
                cleint_data.new_message->new_message = strdup(get_value(object, "new_message",&error));
                cleint_data.new_message->date = strdup(get_value(object, "date",&error));
                g_mutex_lock(&mutex1);
                print_new_message();
                g_mutex_unlock(&mutex1);
        }
        // else {
        //     object = NULL;
        //     break;
        // }
        object = NULL;

    }
    // recv(cleint_data.soketfd, str1, 2000, 0);
    // printf("getmessege:%s\n",str1);
    // printf("strlenstrgetmessege%lu\n",strlen(str1));

    // object = cJSON_Parse(str1);
    // free(str1);
    // type = strdup(get_value(object, "type",&error)); 
    // if (strcmp(type, "error") == 0) {
    //     messege_doing = strdup(get_value(object, "message",&error));
    //     printf("%s\n", messege_doing);
    // } 
    // if (strcmp(type, "private_message_reply") == 0) {
    //         write(2,"teh1\n",5);
    //         cleint_data.new_message->sender_id = strdup(get_value(object, "sender_id",&error));     //записываю в структуру значение ключа user_password в объекте object
    //         cleint_data.new_message->sender_f_name = strdup(get_value(object, "sender_f_name",&error));
    //         cleint_data.new_message->sender_l_name = strdup(get_value(object, "sender_l_name",&error));
    //         cleint_data.new_message->sender_login = strdup(get_value(object, "sender_login",&error));
    //         cleint_data.new_message->sender_email = strdup(get_value(object, "sender_email",&error));
    //         cleint_data.new_message->sender_ph_number = strdup(get_value(object, "sender_ph_number",&error));
    //         cleint_data.new_message->receiver_id = strdup(get_value(object, "receiver_id",&error));
    //         cleint_data.new_message->new_message = strdup(get_value(object, "new_message",&error));
    //         cleint_data.new_message->date = strdup(get_value(object, "date",&error));
    //         print_new_message();
    // }
    //cJSON_Delete(object);
    // object = NULL;
}

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
