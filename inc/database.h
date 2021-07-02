#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"
#include <../cjson/inc/cJSON.h>
#include "stdbool.h"

#define N 200 //макс. длина sql-запроса
#define MAX_MESS_AMNT 50    //максимальное кол-во сообщений для отправки из БД

//--------------------------------------ERRORS---------------------------------------------------
#define ER_JSN_TO_STRUCT  "1"    //неудачная конвертация json-строки в структуру
#define ER_JSN_PARSE      "2"   //неудачный парсинг json-строки
#define ER_JSN_TYPE       "3"   //неправильный ключ 'type' в json-строке

#define ER_DB_OPEN        "4"   //неудача открыть базу данных
#define ER_DB_EXEC        "5"   //неудачное выполнение запроса в БД
#define ER_DB_INSERT      "6"   //неудача вставки данных в БД
#define ER_DB_TABLE       "7"   //таблица не существует в БД
#define ER_DB_NO_USERS    "8"   //не существует пользователь в БД
#define ER_DB_CREDENTIALS "9"   //неправильный user_id или user_password в БД

/*структура, которая содержит инф-ю об ошибке*/
typedef struct errors {
    char *error_message;
    char *error_number;
}              errors;

/*инициализация структуры ошибок*/
void init_error_struct(errors **error);

/*удаляю структуру errors*/
void delete_error(errors **error);

/*формирует нужную json-строку для отсылания ошибки*/
void error_json(char **reply, errors **error);

/*неправильный ключ 'type' в json-строке, фришит 'func_message'*/
void incorrect_key_type(errors **error, char *func_message);

/*неудачный парсинг json-строки, фришит 'func_message'*/
void failed_to_parse_json(errors **error, char *func_message);

/*неудача достать значения ключа в json-строке, фришит 'func-message-s'*/
void failed_to_get_key_value(errors **error, char **func_message1, char *func_message2);

/*неудача открыть бд*/
void failed_to_open_db(const char *err_msg, errors **error);

/*неудачный запрос в БД*/
void failed_to_exec(const char *message, errors **error);

/*таблица не существует в БД*/
void no_table(errors **error, const char *was_invoked_in, char **table_to_find);

/*один из пользователей или все не существуют в БД*/
void no_users(errors **error, const char *was_invoked_in, char *user1_id, char *user2_id);

/*не существует user_id или user_password in DB*/
void invalid_credentials(errors **error, const char *was_invoked_in, char *user_id, char *user_password);


//---------------------------------------REGISTRATION--------------------------------------------
//-----------------------------------------------------------------------------------------------

typedef struct db_user_registration_req {   //получаю с json: запрос - 'регистрация пользователя'
    char *user_first_name;
    char *user_last_name;
    char *user_login;
    char *user_password;
    char *user_email;
    char *user_phone_number;
    char *registration_time;
}              db_user_registration_req;

/*конвертирует json-строку в структуру или записывает ошибку*/
db_user_registration_req *jsn_to_registration_req(char *json_reg_request, errors **errors_p);

typedef struct db_user_registration_reply {     //получаю с БД: ответ на запрос 'регистрация пользователя'
    char *user_is_in_db;    
    char *user_login;
    char *user_phone_number;
    char *user_email;
    char *user_id; 
}              db_user_registration_reply;

/*сздает таблицу с названием 'friends_[user_id]' из 2-х столбцов, в которой будут храниться id пользователей,
//с которыми были переписки у [user_id].*/
void create_table_chats_with_friends(sqlite3 *db, errors **error, db_user_registration_reply *reply);

/*добавляет/не добавляет user в БД и возвращает ответ из БД, готовый для конвертации в json-строку*/
db_user_registration_reply *checking_matches_in_table_users(db_user_registration_req **usrreg_req, errors **error);

/*ответ от базы данных на запрос - 'регистрация пользователя' и перевод ответа в json-строку*/
char *registration_reply_to_jsn(db_user_registration_reply **reply_from_db);


//---------------------------------------LOG_IN--------------------------------------------
//-----------------------------------------------------------------------------------------

typedef struct db_user_log_in_req {     //получаю с json: запрос - 'вход пользователя'
    char *user_login;
    char *user_phone_number;
    char *user_password;
    char *log_in_time;
}              db_user_log_in_req;

/*достает из json-строки данные (запрос на вход пользователя) и записывает эти данные в структуру*/
db_user_log_in_req *jsn_to_log_in_req(char *json_log_in_request, errors **error_p);


typedef struct db_user_log_in_reply {   //получаю с БД: ответ на запрос 'вход пользователя'
    int row;    //для колбэка
    char *user_logged_in;
    char *user_first_name;
    char *user_last_name;
    char *user_login;   
    char *user_phone_number;
    char *user_email;    
    char *user_id;
    char *friends_id[MAX_MESS_AMNT];
    char *friends_f_name[MAX_MESS_AMNT];
    char *friends_l_name[MAX_MESS_AMNT];
    char *friends_login[MAX_MESS_AMNT];
    char *friends_ph_number[MAX_MESS_AMNT];
    char *friends_email[MAX_MESS_AMNT];  
    errors *error;   //для колбэка
    sqlite3 *db;     //для колбэка
}              db_user_log_in_reply;


/*достает инфу из таблицы 'friends_[user_id]' и 'users', и записывает в структуру*/
void get_info_from_friends_table(db_user_log_in_reply **log_in, errors **error, sqlite3 **db);

/*возвращает ответ log_in_reply на запрос log_in_req*/
db_user_log_in_reply *log_in_req_to_reply(db_user_log_in_req **log_in_req, errors **error);

/*ответ от базы данных на запрос - 'вход пользователя' и перевод ответа в json-строку*/
char *log_in_reply_to_jsn(db_user_log_in_reply **reply_from_db);

//--------------------------------------FIND_USER-----------------------------------------------
//----------------------------------------------------------------------------------------------

typedef struct db_find_user_req {   //получаю с json: запрос - 'поиск пользователя'
    char *login_to_find;
}              db_find_user_req;

/*достает из json-строки данные (запрос на поиск пользователя) и записывает эти данные в структуру*/
db_find_user_req *jsn_to_find_user_req(char *json_find_user_request, errors **error_p);

typedef struct db_find_user_reply {     //получаю с БД: ответ на запрос 'поиск пользователя'
    char *login_found;
    char *f_user_id;
    char *f_user_first_name;
    char *f_user_last_name;
    char *f_user_ph_number;
    char *f_user_email;
}              db_find_user_reply;

/*возвращает ответ find_user_reply на запрос find_user_req*/
db_find_user_reply *find_user_req_to_reply(db_find_user_req **find_user_req, errors **error);

/*ответ от базы данных на запрос - 'поиск пользователя' и перевод ответа в json-строку*/
char *find_user_reply_to_jsn(db_find_user_reply **reply_from_db);


//--------------------------------------PRIVATE_MESSAGE-----------------------------------------------
//----------------------------------------------------------------------------------------------------


typedef struct db_private_message_req {     //получаю с json: запрос - 'личное сообщение'
    char *sender_id;
    char *receiver_id;
    char *message;
    char *date;
}              db_private_message_req;

/*достает из json-строки данные (запрос на личное сообщение) и записывает эти данные в структуру*/
db_private_message_req *jsn_to_pr_message_req(char *json_pr_message_request, errors **error_p);

typedef struct db_private_message_reply {     //получаю с БД: ответ на запрос 'личное сообщение', 
                                            //должно быть отправлено другому пользователю!
    int row;              //текущая строка в таблице (для колбэка)
    char *sender_id;
    char *sender_f_name;
    char *sender_l_name;
    char *sender_email;
    char *sender_ph_number;
    char *sender_login;
    char *receiver_id;
    char *new_message;  
    char *date;                         
}              db_private_message_reply;

/*возвращает ответ private_message_reply на запрос private_message_req*/
db_private_message_reply *private_message_req_to_reply(db_private_message_req **private_message, 
                                                       errors **error);
/*проверка на наличие id ползьователей в таблице users который участвуют в переписке*/
void check_user(db_private_message_req *private_message_req, errors **error, sqlite3 **db);

        /*
    записывает личное сообщение от одного пользователя к другому в БД.
    Принимает:
    //private_message - структура, которая хранит инфу об этом сообщении; не очищается после использования
    //db - адрес на указатель к БД (БД открывается в другой функции)
    //error - структура ошибок, куда записываются данные о случившейся ошибки, если что-то пошло не так в функции.
    */
    void add_private_message_to_db(db_private_message_req *private_message, sqlite3 **db, errors **error);

    /*заполняет таблицу friends_[user_id] если это надо*/
    void fill_table_friends(db_private_message_req *pReq, sqlite3 **pSqlite3, errors **pErrors);

    /*возвращает информацию о пользователе (при отправке сообщения)*/
    void get_user_details(db_private_message_reply **pr_mess_reply, db_private_message_req *pr_mess_req,
                            errors **error, sqlite3 **db);
    /*создает таблицу в случае её отсутствия*/
    void sozdanie_tablici(sqlite3 **db, char *tablica, errors **error);

    /*заполняет таблицу чата двух пользователей*/
    void zapolnenie_tablici(char *tablica, db_private_message_req *private_message, sqlite3 **db, errors **error);

    void fill_table_friends(db_private_message_req *pReq, sqlite3 **pSqlite3, errors **pErrors);

    void insert_into_table_friends(char *id_for_tablename, char *id_for_value, sqlite3 **pSqlite3, errors **pErrors);

/*ответ от базы данных на запрос - 'личное сообщение' и перевод ответа в json-строку*/
char *private_mess_reply_to_jsn(db_private_message_reply **reply_from_db);
/*проверяет наличие id друга в таблице friends_[user_id}*/
bool proverka_existence_id(char *id_for_tablename, char *id_for_check_value, sqlite3 **db);
/*выполнение запроса заполнения таблицы*/
void insert_into_table_friends(char *id_for_tablename, char *id_for_value, sqlite3 **pSqlite3, errors **pErrors);


//--------------------------------------GET_CHAT_WITH_SEL_USER-----------------------------------------------
//----------------------------------------------------------------------------------------------------

typedef struct db_get_chat_with_sel_user_req {     //получаю с json: запрос - 'получить чат с выбранным пользователем'
    char *dest_user_id;         //id выбранного пользователя (пользователя, с кем хотят увидеть чат)
    char *source_user_id;           //id пользователя, который хочет увидеть чат с selected_user_id
}              db_get_chat_with_sel_user_req;


/*достает из json-строки данные (запрос "получить чат с выбранным пользователем" ) и записывает эти данные в структуру*/
db_get_chat_with_sel_user_req *jsn_to_chat_with_req(char *json_chat_with_request, errors **error_p);

typedef struct db_get_chat_with_sel_user_reply {     //получаю с БД: ответ на запрос 'получить чат с выбранным пользователем'
    int row;              //текущая строка в таблице (для колбэка)
    char *dest_user_id;
    char *source_user_id;
    char *last_50_messages[MAX_MESS_AMNT];  //нужно уточнение
    char *dates[MAX_MESS_AMNT];             //нужно уточнение
    char *messages_senders[MAX_MESS_AMNT];  //нужно уточнение
    //char *unread_message_index;             //нужно уточнение
}              db_get_chat_with_sel_user_reply;

/*возвращает последний чат между source_user и dest_user*/
void get_last_chat(db_get_chat_with_sel_user_reply **get_chat_reply, db_get_chat_with_sel_user_req *get_chat_req, 
                   sqlite3 **db, errors **error);

    /*возвращает ответ get_chat_with на запрос get_chat_with*/
    db_get_chat_with_sel_user_reply *get_chat_with_req_to_reply(db_get_chat_with_sel_user_req **get_chat_with_req, errors **error);

char *chat_with_reply_to_jsn(db_get_chat_with_sel_user_reply **reply_from_db);


//--------------------------------------CHANGING_THE_PASSWORD-----------------------------------------------
//-----------------------------------------------------------------------------------------------------------

typedef struct db_change_user_passw_req {
    char *user_id;
    char *old_password;
    char *new_password;
}              db_change_user_passw_req;

typedef struct db_change_user_passw_reply {
    char *password_changed;
}              db_change_user_passw_reply;

/*конвертирует json-строку в структуру или записывает ошибку*/
db_change_user_passw_req *jsn_to_change_passw_req(char *json_change_passw, errors **errors_p);

/*возвращает ответ change_passwd_reply на запрос change_passwd_req*/
db_change_user_passw_reply *change_passwd_req_to_reply(db_change_user_passw_req **change_passwd_req, errors **error);

    /*пытается сменить пароль по айди и старому паролю и заполняет структуру db_change_user_passw_reply*/
    void try_to_update_passwd(db_change_user_passw_reply **change_passwd_reply, db_change_user_passw_req *change_passwd_req, 
                                            sqlite3 **db, errors **error);

/*ответ от базы данных на запрос - 'смена пароля' и перевод ответа в json-строку*/
char *change_passwd_reply_to_jsn(db_change_user_passw_reply **reply_from_db);
//--------------------------------------TYPE----------------------------------------------------------
//----------------------------------------------------------------------------------------------------

/*
основная функция:
принимает json-строку (запрос от клиента), определяет поле type в json, 
фришит char *json
возвращает ответ из БД, конвертирует его в необходимую json-строку для отправки клиенту
*/
char *get_reply_from_db(char **json);

    /*возвращает ответ из БД на запрос 'вход пользователя'*/
    void get_log_in_reply(char *json, char **reply);

    /*возвращает ответ из БД на запрос 'регистрация пользователя'*/
    void get_registration_reply(char *json, char **reply);

    /*возвращает ответ из БД на запрос 'поиск пользователя'*/
    void get_find_user_reply(char *json, char **reply);

    /*возвращает ответ из БД на запрос 'личное сообщение'*/
    void get_pr_message_reply(char *json, char **reply);

    /*возвращает ответ из БД на запрос 'получить чат с выбранным пользователем'*/
    void get_chat_with_reply(char *json, char **reply);

    /*возвращает ответ из БД на запрос 'смена пароля'*/
    void get_change_passw_reply(char *json, char **reply);


//--------------------------------------OTHER-----------------------------------------------
//------------------------------------------------------------------------------------------

/*такое же, что и sqlite3_open, только void  не обрабатывает ошибки*/
void open_db(sqlite3 **ppdb);

/*записывает в стат. массив sql "полный, простой запрос" select*/
void sql_make_simple_select_in(char *column, char *table, char *key_column, 
                            char *key_value, char sql[N], errors *error);

/*такое же, что и sqlite3_exec, только void, и обрабатывает ошибки*, 
    //void *save_result  -- куда будет записываться результат (адрес на любой тип)
    //sqlite3 **db -- адрес указателя на БД
    //char *sql -- запрос SQL
    //int (*callback)(void *, int, char **, char **) -- указатель на ф-ю обратного вызова
    //errors **error -- адрес на указатель на структуру errors, место, куда будет записываться ошибка в случае неудачи
    //const char *was_invoked_in -- название функции, где был вызван sqlite3_better_exec для **error
    */ 
/*такое же, что и sqlite3_exec, только void, и обрабатывает ошибки*/  
void sqlite3_better_exec(sqlite3 **db, char *sql, 
                        int (*callback)(void *, int, char **, char **), 
                        void *save_result, errors **error, 
                        const char *was_invoked_in);

/*находит пользователя по логину/номеру телефона и паролю в БД && записывает ответ в log_in_reply*/
void find_user_by_credentials_and_fill_log_in_reply(db_user_log_in_reply **log_in_reply, 
                                                    db_user_log_in_req *log_in_req, sqlite3 **db, errors **error);

/*определяет: искать по номеру телефона или логину в uchat.db
//возвращает: 
"user_phone_number" - по номеру телефона
"user_login" - по логину
*/
char *by_phone_number_or_login(char *ph_num, sqlite3 **db, errors **error, const char *was_invoked_in);

/*находит пользователя по логину и заполняет структуру db_find_user_reply*/
void get_found_user_info(db_find_user_reply **find_user_reply, db_find_user_req *find_user_req, 
                                        sqlite3 **db, errors **error);

/*инверсия строки* (простое шифрование)*/
void inversion(char **str);

/*достает значение ключа у json или создает ошибку*/
char *get_value(cJSON *object, char *key, char **er_msg);

/*проверяет: пустая ли таблица*/
bool is_empty_table(char *table_name, sqlite3 **db, errors **error);

/*проверяет: существует ли таблица 'chat_[sender_id]_[receiver_id]' или 'chat_[receiver_id]_[sender_id]', 
возвращает:
     название таблицы в случае положительного р-та 
     в ином случае NULL*/
char *proverka_tablic(char *sender_id, char *reciever_id, sqlite3 **db);

/*проверяет наличие таблицы friends_[user_id] в БД*/
void proverka_tablic_friends(char *id_for_check, sqlite3 **db, errors **error);

/*создание sql-запроса для БД, чтобы достать 50 последних сообщений*/
void make_sql_get_last_messages(char sql[N], char *table_name);

/*возвращает: 
    NULL - не существует таблица table_name
    table_name (динамическая память) - если существует
*/
char *table_exists(char *table_name, sqlite3 **db, errors **error);

/*проверяет: существует ли таблица chat_[uid1]_[uid2] или chat_[uid2]_[uid1].
  возвращает:
        NULL - если не существует ни одна таблица или если структура errors заполнена
        chat_[uid2]_[uid1] или chat_[uid1]_[uid2] - если одна из них существует. (динамическая память)
        DON'T USE THE FUNCTION!
*/
char *table_chat_exists(char *uid1, char *uid2, sqlite3 **db, errors **error);

bool proverka_existence_id(char *id_for_tablename, char *id_for_check_value, sqlite3 **db);


//--------------------------------------TESTS-----------------------------------------------
//------------------------------------------------------------------------------------------

/*создается предполагаемая json-строка (запрос) для регистрации*/
char *test_reg_json();

/*создается предполагаемая json-строка (запрос) для входа*/
char *test_log_in_json();

/*создается предполагаемая json-строка (запрос) для поиска пользователя*/
char *test_find_user_json();

/*создается предполагаемая json-строка (запрос) для личного сообщения*/
char *test_private_mess_json();

/*создается предполагаемая json-строка (запрос) для получить чат с*/
char *test_get_chat_json();

/*создается предполагаемая json-строка (запрос) для смены пароля пользователя*/
char *test_change_passwd_json();

#endif
