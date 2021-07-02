#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void delete_req_struct(db_change_user_passw_req **usrreg_req);

/*конвертирует json-строку в структуру или записывает ошибку*/
db_change_user_passw_req *jsn_to_change_passw_req(char *json_change_passw, errors **errors_p) { 
    db_change_user_passw_req *change_passwd = (db_change_user_passw_req*)malloc(sizeof(db_change_user_passw_req));   //выделяю память под структуру
    cJSON *object = NULL;
    char *e_message = NULL;     //ЧАСТЬ сообщения об ошибке

    object = cJSON_Parse(json_change_passw);
    
    if (!object) {  //если распарсило
        failed_to_parse_json(errors_p, mx_strdup(" in function jsn_to_change_passw_req "));
        delete_req_struct(&change_passwd);

        return NULL;
    }     

    if (object) {   //если не распарсило
        change_passwd->user_id = get_value(object, "user_id", &e_message);   
        change_passwd->old_password = get_value(object, "old_password", &e_message);     
        change_passwd->new_password = get_value(object, "new_password", &e_message);    
    }

    cJSON_Delete(object); 

    if (!e_message)      //если не обнаружена ошибка при переводе json-строки в структуру:
        return change_passwd;
    else {      //была найдена ошибка
        failed_to_get_key_value(errors_p, &e_message, mx_strdup(" in function 'jsn_to_change_passw_req' "));
        delete_req_struct(&change_passwd);
        return NULL;
    }
}

static void delete_req_struct(db_change_user_passw_req **usrreg_req) {
    mx_strdel(&(*usrreg_req)->new_password);
    mx_strdel(&(*usrreg_req)->old_password);
    mx_strdel(&(*usrreg_req)->user_id);
    free(*usrreg_req);
    *usrreg_req = NULL;
}
