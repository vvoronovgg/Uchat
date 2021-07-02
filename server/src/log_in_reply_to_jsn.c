#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void logged_in_user(cJSON *object, db_user_log_in_reply *reply_from_db);
static void not_logged_in_user(cJSON *object);
static void delete_reply_from_db(db_user_log_in_reply **reply_from_db);

/*ответ от базы данных на запрос - 'вход пользователя' и перевод ответа в json-строку*/
char *log_in_reply_to_jsn(db_user_log_in_reply **reply_from_db) {
    if (!*reply_from_db)
        return NULL;

    cJSON *object = NULL;
    char *str = NULL;

    object = cJSON_CreateObject();    //создается объект 
    cJSON_AddStringToObject(object, "type", "log_in_reply");  //создается ключ "type" и значение "registration_req" в объекте object
   
    if (mx_strcmp((*reply_from_db)->user_logged_in, "1") == 0)  //если пользователь ввел правильные данные при входе
        logged_in_user(object, *reply_from_db);    
    else  not_logged_in_user(object);     //если пользователь ввел не правильные данные при входе 
    
    str = cJSON_Print(object);  //конвертирую в json-строку
    cJSON_Delete(object);   //удаляю объект
    delete_reply_from_db(reply_from_db);    //удаляю db_user_log_in_reply структуру

    return str; 
}

/*user ввел неправильные данные для входа*/
static void not_logged_in_user(cJSON *object) {
    cJSON_AddStringToObject(object, "user_logged_in", "0");  //создается ключ "user_is_in_db" и значение "0" в объекте object
}

/*добавляет массивы в json из структуры*/
static void fill_arrays(db_user_log_in_reply *reply_from_db, cJSON *object);

/*user ввел правильные данные для входа*/
static void logged_in_user(cJSON *object, db_user_log_in_reply *reply_from_db) {
    cJSON_AddStringToObject(object, "user_logged_in", reply_from_db->user_logged_in);  //создается ключ "user_logged_in" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_first_name", reply_from_db->user_first_name);       //создается ключ "user_first_name" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_last_name", reply_from_db->user_last_name);     //создается ключ "user_last_name" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_login", reply_from_db->user_login);       //создается ключ "user_login" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_phone_number", reply_from_db->user_phone_number);       //создается ключ "user_phone_number" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_email", reply_from_db->user_email);       //создается ключ "user_email" и значение  в структуре в объекте object
    cJSON_AddStringToObject(object, "user_id", reply_from_db->user_id);     //создается ключ "user_id" и значение  в структуре в объекте object
    fill_arrays(reply_from_db, object);
}

static void fill_arrays(db_user_log_in_reply *reply_from_db, cJSON *object) {
    cJSON *friends_f_name = NULL;
    cJSON *friends_l_name = NULL;
    cJSON *friends_login = NULL;
    cJSON *friends_id = NULL;
    cJSON *friends_ph_number = NULL;
    cJSON *friends_email = NULL;
    
    cJSON *s1 = NULL;
    cJSON *s2 = NULL;
    cJSON *s3 = NULL;
    cJSON *s4 = NULL;
    cJSON *s5 = NULL;
    cJSON *s6 = NULL;

    //добавляю массивы в объект object:
    friends_f_name = cJSON_AddArrayToObject(object, "friends_f_name");  
    friends_l_name = cJSON_AddArrayToObject(object, "friends_l_name");
    friends_login = cJSON_AddArrayToObject(object, "friends_login");
    friends_id = cJSON_AddArrayToObject(object, "friends_id");
    friends_ph_number = cJSON_AddArrayToObject(object, "friends_ph_number");
    friends_email = cJSON_AddArrayToObject(object, "friends_email");

    //для каждого массива и элемента этого массива записываю соответствующие данные
    for (int i = 0; i < MAX_MESS_AMNT && reply_from_db->friends_f_name[i] != NULL; i++) {
        s1 = cJSON_CreateString(reply_from_db->friends_f_name[i]);
        s2 = cJSON_CreateString(reply_from_db->friends_l_name[i]);
        s3 = cJSON_CreateString(reply_from_db->friends_login[i]);
        s4 = cJSON_CreateString(reply_from_db->friends_id[i]);
        s5 = cJSON_CreateString(reply_from_db->friends_ph_number[i]);
        s6 = cJSON_CreateString(reply_from_db->friends_email[i]);
        
        cJSON_AddItemToArray(friends_f_name, s1);
        cJSON_AddItemToArray(friends_l_name, s2);
        cJSON_AddItemToArray(friends_login, s3);
        cJSON_AddItemToArray(friends_id, s4);
        cJSON_AddItemToArray(friends_ph_number, s5);
        cJSON_AddItemToArray(friends_email, s6);
    }
}

/*очищает структуру*/
static void delete_reply_from_db(db_user_log_in_reply **reply_from_db) {
    mx_strdel(&(*reply_from_db)->user_first_name);
    mx_strdel(&(*reply_from_db)->user_last_name);
    mx_strdel(&(*reply_from_db)->user_login);
    mx_strdel(&(*reply_from_db)->user_logged_in);
    mx_strdel(&(*reply_from_db)->user_id);
    mx_strdel(&(*reply_from_db)->user_phone_number);
    mx_strdel(&(*reply_from_db)->user_email);
    for (int i = 0; i < MAX_MESS_AMNT; i++) {
        mx_strdel(&(*reply_from_db)->friends_ph_number[i]);
        mx_strdel(&(*reply_from_db)->friends_email[i]);
        mx_strdel(&(*reply_from_db)->friends_f_name[i]);
        mx_strdel(&(*reply_from_db)->friends_id[i]);
        mx_strdel(&(*reply_from_db)->friends_l_name[i]);
        mx_strdel(&(*reply_from_db)->friends_login[i]);
    }
    free(*reply_from_db);
    *reply_from_db = NULL;
}
