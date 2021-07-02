#include "client.h"

#define W 2000
static char *get_value(cJSON *object, char *key, char **er_msg);

char *jsn_log_in(void) {  //добавьте этот прототип в общий header!!!
    cJSON *object = NULL;
    char *str = NULL;
    char *str1 = mx_strnew(W);
    char *login_doing = strdup ("1");
    char *type = NULL;   //вывод
    char *error = NULL;

    object = cJSON_CreateObject(); //создается объект object
    cJSON_AddStringToObject(object, "type", "log_in_req"); //создается ключ "type" и значение "log_in" в объекте object
    cJSON_AddStringToObject(object, "user_login", cleint_data.login->username);  //создается ключ "user_login" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "user_password", cleint_data.login->password);   //создается ключ "user_password" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "log_in_time", cleint_data.login->time_log);   //создается ключ "log_in_time" и значение "none" в объекте object
    str = cJSON_Print(object);  //конвертирую json в строку
    if (!str)
        write(2,"PRINT\n",6);
    //cJSON_Delete(object);   //удаляю объект user, содержащий свои ключи - значения
    object = NULL;
    
    g_mutex_lock(&muxtex);
    send(cleint_data.soketfd, str, 2000,0);
    recv(cleint_data.soketfd, str1, 2000, 0);
    g_mutex_unlock(&muxtex);

    printf("%s\n",str1);
    printf("strlenstrlog%lu\n",strlen(str1));
    object = cJSON_Parse(str1);
    if (!object)
        printf("NONE OBJECT");
    type = strdup(get_value(object, "type",&error));
    if (strcmp(type, "error") == 0) {
        login_doing = strdup(get_value(object, "message",&error));
        write(2,"REE\n",4);
        //free(str1);
        return login_doing;
    }
    if (strcmp(type,"log_in_reply") == 0) {
        login_doing = strdup(get_value(object, "user_logged_in",&error));   //записываю в структуру значение ключа user_login в объекте object
        if (strcmp(login_doing, "1") == 0) {// тут ще має бути одна перевірка
            cleint_data.login_jsn->firstname = strdup(get_value(object, "user_first_name",&error));     //записываю в структуру значение ключа user_password в объекте object
            cleint_data.login_jsn->lastname = strdup(get_value(object, "user_last_name",&error));
            cleint_data.login_jsn->username = strdup(get_value(object, "user_login",&error));
            cleint_data.login_jsn->phonenum = strdup(get_value(object, "user_phone_number",&error));
            cleint_data.login_jsn->user_id = strdup(get_value(object, "user_id",&error));
            cleint_data.login_jsn->userschat = parse_arr(str1, "friends_login");
            cleint_data.login_jsn->friends_f_name = parse_arr(str1, "friends_f_name");
            cleint_data.login_jsn->friends_l_name = parse_arr(str1, "friends_l_name");
            cleint_data.login_jsn->friends_id = parse_arr(str1, "friends_id");
            cleint_data.login_jsn->friends_ph_number = parse_arr(str1, "friends_ph_number");
            cleint_data.login_jsn->friends_email = parse_arr(str1, "friends_email");
            //cJSON_Delete(object);
            object = NULL;   //удаляю json
            write(2,"ERR\n",4);
            //free(str1);
            return login_doing;
        }  
        else if (strcmp(login_doing, "0") == 0) {// тут ще має бути одна перевірка
            //cJSON_Delete(object); 
            object = NULL;  //удаляю json
            //free(str1);
            return login_doing;
        }
    }
    //free(str1);
    //cJSON_Delete (object);
    return login_doing;
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
            printf("%s\n", message);
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
