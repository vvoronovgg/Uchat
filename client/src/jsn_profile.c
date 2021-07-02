#include "client.h"

static char *get_value(cJSON *object, char *key, char **er_msg);

GMutex mutex2;

char *jsn_profile(char *search) {  //добавьте этот прототип в общий header!!!
    cJSON *object = NULL;
    char *str = NULL;
    char *login_doing = strdup ("1");
    char *type = NULL;   //вывод
    char *str1 = mx_strnew(2000);
    char *error = NULL;

    object = cJSON_CreateObject(); //создается объект object
    cJSON_AddStringToObject(object, "type", "find_user_req"); //создается ключ "type" и значение "log_in" в объекте object
    cJSON_AddStringToObject(object, "login_to_find", search);  //создается ключ "user_login" и значение "none" в объекте object
    str = cJSON_Print(object);  //конвертирую json в строку
    //cJSON_Delete(object); 
    object = NULL;  //удаляю объект user, содержащий свои ключи - значения
    // write(cleint_data.soketfd, str, strlen(str));
    // free(str);
    // read(cleint_data.soketfd, str, strlen(str));
    g_mutex_lock(&mutex2);
    send(cleint_data.soketfd, str, 2000,0);
    free(str);
    recv(cleint_data.soketfd, str1, 2000, 0);
    g_mutex_unlock(&mutex2);
    printf("findprofile%s\n",str1);
    printf("strlen profile%lu\n",strlen(str1));
    object = cJSON_Parse(str1);
    if (!object)
        printf("NONE OBJECT");
    write(2,"101\n",4);
    type = strdup(get_value(object, "type",&error));
    if (strcmp(type, "error") == 0) {
        login_doing = strdup(get_value(object, "message",&error));
        write(2,"102\n",4);
        free(str1);
        return login_doing;
    }
    if (strcmp(type,"find_user_reply") == 0) {
        write(2,"103\n",4);
        login_doing = strdup(get_value(object, "login_found",&error));   //записываю в структуру значение ключа user_login в объекте object
        write(2,"104\n",4);
        if (strcmp(login_doing, "1") == 0) {// тут ще має бути одна перевірка
            write(2,"105\n",4);
            cleint_data.profile->search_user_id = strdup(get_value(object, "f_user_id",&error));     //записываю в структуру значение ключа user_password в объекте object
            cleint_data.profile->search_user_fn = strdup(get_value(object, "f_user_first_name",&error));
            str1 = mx_strjoin(cleint_data.profile->search_user_fn, " ");
            write(2,"107\n",4);
            cleint_data.profile->search_user_ln = strdup(get_value(object, "f_user_last_name",&error));
            cleint_data.profile->search_user_fl = mx_strjoin(str1, cleint_data.profile->search_user_ln);
            cleint_data.profile->search_user_em = strdup(get_value(object, "f_user_email",&error));
            cleint_data.profile->search_user_num = strdup(get_value(object, "f_user_ph_number",&error));
            write(2,"108\n",4);
            //cJSON_Delete(object); 
            object = NULL;  //удаляю json 
            free(str1);
            return login_doing;
        }  
        else if (strcmp(login_doing, "0") == 0) {// тут ще має бути одна перевірка
            //cJSON_Delete(object); 
            object = NULL;  //удаляю json
            free(str1);
            return login_doing;
        }
        write(2,"106\n",4);
    }
    free(str1);
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
