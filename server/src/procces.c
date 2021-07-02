#include "database.h"
#include "sqlite3.h"
#include "server.h"

// pthread_mutex_t muztex;
pthread_mutex_t muztex;

/*определяет тип json-строки из БД*/
static char *define_db_jsonstr_type(cJSON *object) {
    char *err_msg = NULL;
    char *type = get_value(object, "type", &err_msg); 
    
    if (err_msg) {
        print_error(err_msg);
        mx_strdel(&err_msg);
    }

    return type;   //динам строка
}

void *procces (void *data) {
    int *socket = (int*)data;
    int curr_client_socket = *socket;     //сокет только что подключенного клиента к серверу
    char *buffer = NULL;                    //json-строка от клиента
    char *strdb = NULL;                     //json-строка из БД
    cJSON *object = NULL;                 //объект из БД
    char *err_msg = NULL;                   //ошибка для get_value
    char *type = NULL;                      //тип json-строки из БД
    char *curr_client_id = NULL;            /*id текущего клиента (только что подключенного к серверу) в БД 
                                            (при регистрации или логине), чистится в update_uid */
    char *receiverid = NULL;                //id получателя
    int on;
    while (1) {
        buffer = mx_strnew(2000);    
        pthread_mutex_lock(&muztex);
        on = recv(curr_client_socket, buffer, MAX_BUFF, 0);
        printf("currclient:%d\n",curr_client_socket);
        printf("on:%d\n",on);
        if (on == -1) {
            printf("oggg%d\n",on);
            delete_client_from_db(curr_client_socket);
            perror("close socket");
            fflush (stdout);
            break;
        }
        if (on == 0) {
            perror("Error recv");
            delete_client_from_db(curr_client_socket);
            exit(1);
        }
        pthread_mutex_unlock(&muztex);
        printf("client:%s\n",buffer);
        strdb = get_reply_from_db(&buffer);
        printf("bd:%s\n", strdb);
        printf("%lu\n",strlen(strdb));
        object = cJSON_Parse(strdb);
        type = define_db_jsonstr_type(object);

        /*если логин или регистрация из БД: */
        if (mx_strcmp(type, "log_in_reply") == 0 || mx_strcmp(type, "registration_reply") == 0) {
            curr_client_id = get_value(object, "user_id", &err_msg);
            update_uid(&curr_client_id, curr_client_socket);

            /*Нужна проверка на существование сокета.  
            Удалять сокет и id клиента из БД, если нет сокета и
            Ничего не отправлять.*/

            send(curr_client_socket, strdb, strlen(strdb),0);
        }

        /*если личное сообщение из БД: */
        if (mx_strcmp(type, "private_message_reply") == 0) {
            receiverid = get_value(object, "receiver_id", &err_msg);

            /*Нужна проверка на существование сокета.  
            Удалять сокет и id клиента из БД, если нет сокета и
            Ничего не отправлять.*/

             send(select_client_socket(&receiverid), strdb, strlen(strdb),0);
        }

        /*если смена пароля/ошибка/поиск пользователя/получение переписки с пользователем из БД: */
        if (mx_strcmp(type, "change_password_reply") == 0 || mx_strcmp(type, "error") == 0 || 
            mx_strcmp(type , "find_user_reply") == 0 || mx_strcmp(type, "chat_with_reply") == 0) {
            
            /*Нужна проверка на существование сокета.  
            Удалять сокет и id клиента из БД, если нет сокета и
            Ничего не отправлять.*/

            send(curr_client_socket, strdb, strlen(strdb),0);
        }
        cJSON_Delete(object);
        mx_strdel(&type);
        mx_strdel(&err_msg);
        mx_strdel(&strdb);
    }
    return 0;
}

