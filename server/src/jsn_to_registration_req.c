#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void delete_req_struct(db_user_registration_req **usrreg_req);

/*конвертирует json-строку в структуру или записывает ошибку*/
db_user_registration_req *jsn_to_registration_req(char *json_reg_request, errors **errors_p) { 
    db_user_registration_req *registration = (db_user_registration_req*)malloc(sizeof(db_user_registration_req));   //выделяю память под структуру
    cJSON *object = NULL;
    char *e_message = NULL;     //ЧАСТЬ сообщения об ошибке

    object = cJSON_Parse(json_reg_request);
    
    if (!object) {  //если распарсило
        failed_to_parse_json(errors_p, mx_strdup(" in function jsn_to_registration_req "));
        delete_req_struct(&registration);

        return NULL;
    }     

    if (object) {   //если не распарсило
        registration->user_first_name = get_value(object, "user_first_name", &e_message);   
        registration->user_last_name = get_value(object, "user_last_name", &e_message);     
        registration->user_login = get_value(object, "user_login", &e_message);    
        registration->user_password = get_value(object, "user_password", &e_message);      
        registration->user_email = get_value(object, "user_email", &e_message);     
        registration->user_phone_number = get_value(object, "user_phone_number", &e_message);   
        registration->registration_time = get_value(object, "registration_time", &e_message);  
    }

    cJSON_Delete(object); 

    if (!e_message)      //если не обнаружена ошибка при переводе json-строки в структуру:
        return registration;
    else {      //была найдена ошибка
        failed_to_get_key_value(errors_p, &e_message, mx_strdup(" in function 'jsn_to_registration_req' "));
        delete_req_struct(&registration);
        return NULL;
    }
}

static void delete_req_struct(db_user_registration_req **usrreg_req) {
    mx_strdel(&(*usrreg_req)->registration_time);
    mx_strdel(&(*usrreg_req)->user_phone_number);
    mx_strdel(&(*usrreg_req)->user_email);
    mx_strdel(&(*usrreg_req)->user_password);
    mx_strdel(&(*usrreg_req)->user_login);
    mx_strdel(&(*usrreg_req)->user_last_name);
    mx_strdel(&(*usrreg_req)->user_first_name);
    free(*usrreg_req);
    *usrreg_req = NULL;
}
