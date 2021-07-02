#include "client.h"

#define W 2000

static char *get_value(cJSON *object, char *key, char **er_msg);

GMutex mutex4;

char *jsn_sign_in(void) {
    cJSON *object = NULL; 
    char *str = NULL;
    char *str1 = mx_strnew(W);
    
    char *signup_doing = strdup ("1");   //вывод
    char *type = NULL;
    char *error = NULL;
    
    object = cJSON_CreateObject();    //создается объект user
    cJSON_AddStringToObject(object, "type", "registration_req");  //создается ключ "type" и значение "registration" в объекте object
    cJSON_AddStringToObject(object, "user_first_name", cleint_data.signup->firstname_sign);    //создается ключ "user_first_name" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "user_last_name", cleint_data.signup->lastname_sign);//создается ключ "user_last_name" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "user_login", cleint_data.signup->username_sign);      //создается ключ "user_login" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "user_password", cleint_data.signup->passw_sign);          //создается ключ "user_password" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "user_email", cleint_data.signup->email_sign);    //создается ключ "user_email" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "user_phone_number", cleint_data.signup->phonenum_sign);//создается ключ "user_phone_number" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "registration_time", cleint_data.signup->time_sigin); //создается ключ "registration_time" и значение "none" в объекте object
    cJSON_AddStringToObject(object, "additional_field", "none"); //создается ключ "additional_field" и значение "none" в объекте object
    
    str = cJSON_Print(object);    //конвертирую json в строку
    //cJSON_Delete(object); 
    object = NULL;    //удаляю объект user, содержащий свои ключи - значения
    
    g_mutex_lock(&mutex4);
    send(cleint_data.soketfd, str, 2000,0);
    //free(str);
    recv(cleint_data.soketfd, str1, 2000, 0);
    g_mutex_unlock(&mutex4);

    printf("%s\n",str1);
    printf("strlenstr%lu\n",strlen(str1));

    object = cJSON_Parse(str1);
    //free(str1);
    if (!object)
        printf("NONE OBJECT");

    type = strdup(get_value(object, "type",&error));
    if (strcmp(type, "error") == 0) {
        signup_doing = strdup(get_value(object, "message",&error));
        return signup_doing;
    }
    if (strcmp(type, "registration_reply") == 0) {
        signup_doing = strdup(get_value(object, "user_is_in_db",&error));   //записываю в структуру значение ключа user_login в объекте object
        cleint_data.login_jsn->username = strdup(get_value(object, "user_login",&error));
        cleint_data.login_jsn->phonenum = strdup(get_value(object, "user_phone_number",&error));
        cleint_data.login_jsn->email = strdup(get_value(object, "user_email",&error));
        if (strcmp(signup_doing, "0") == 0) {
            //cJSON_Delete(object);   //удаляю json 
            object = NULL;
            return signup_doing;
        }  
        else if (strcmp(signup_doing, "1") == 0) {
            if (strcmp(cleint_data.login_jsn->username, "0") != 0) {
                error = strdup("your username is exist");
                free(cleint_data.login_jsn->username);
                return error;
            }  
            if (strcmp(cleint_data.login_jsn->phonenum, "0") != 0) {
                error = strdup("your phonenum is exist");
                free(cleint_data.login_jsn->phonenum);
                return error;
            }  
            if (strcmp(cleint_data.login_jsn->email, "0") != 0) {
                error = strdup("your email is exist");
                free(cleint_data.login_jsn->email);
                return error;
            } 
            //cJSON_Delete(object);   //удаляю json
            object = NULL;
            return signup_doing;
        }
    }
    //cJSON_Delete(object);
    object = NULL;
    return signup_doing;
}

// static char *get_value(cJSON *object, char *key) {
//     cJSON *Item = NULL;
//     char *value = NULL;

//     Item = cJSON_GetObjectItemCaseSensitive(object, key);   //достаю значение ключа key в объекте object
//     value = strdup(Item->valuestring);    

//     cJSON_DeleteItemFromObjectCaseSensitive(object, key);   //удаляю ключ key и значение из object
//     return value;
// }

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
