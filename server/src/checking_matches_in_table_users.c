//
// Created by Andrii Danylenko on 10/9/20.
//
#include "server.h"
#include "database.h"
#include "sqlite3.h"
#include "libmx.h"

static void init_rep_struct(db_user_registration_reply **usrreq_rep);
static int callback(void *unused, int count, char **data, char **columns);
static int check_for_three_column(db_user_registration_req *usrreg_req, sqlite3 *db, int *arr_result, char *sql_req_fill_four, char **err, errors **error);
static void fill_structure_rep(db_user_registration_req *usrreg_req, db_user_registration_reply **usrreq_rep, int *arr_result);
static int add_user_in_db(db_user_registration_req *usrreg_req, sqlite3 *db, char *sql);
static void print_result(char **result, char *str);
static void delete_req_struct(db_user_registration_req **usrreg_req);
static void fill_structure_rep_user_id(db_user_registration_req *usrreg_req, db_user_registration_reply **usrreq_rep, sqlite3 *db, char *sql_req_fill_four);


db_user_registration_reply *checking_matches_in_table_users(db_user_registration_req **usrreg_req, errors **error) {
    if (!*usrreg_req)
        return NULL;

    sqlite3 *db;
    char *err = NULL;

    db_user_registration_reply *usrreq_rep = NULL;
    init_rep_struct(&usrreq_rep);

    int *arr_result = mx_intnew(3);
    char sql_req_fill_four[255];


    int rc = sqlite3_open("uchat.db", &db);

    if (rc != SQLITE_OK) {
        err = mx_strdup("Cannot open database - error in func checking_matches_in_table_users");
        (*error)->error_message = mx_strdup("Cannot open database - error in func checking_matches_in_table_users");
        (*error)->error_number = mx_strdup(ER_DB_OPEN);
        delete_req_struct(usrreg_req);
        mx_strdel(&err);
        sqlite3_close(db);
        return NULL;
    } else {



    check_for_three_column(*usrreg_req, db, arr_result, sql_req_fill_four, &err, error);
    if (err) {
        delete_req_struct(usrreg_req);
        mx_intdel(&arr_result);

        mx_strdel(&err);
        sqlite3_close(db);
        return NULL;
    } else {


        fill_structure_rep(*usrreg_req, &usrreq_rep, arr_result);

        mx_intdel(&arr_result);


        if (mx_strcmp(usrreq_rep->user_is_in_db, "0") == 0) {
            if (add_user_in_db(*usrreg_req, db, sql_req_fill_four) == 0) {

                fill_structure_rep_user_id(*usrreg_req, &usrreq_rep, db, sql_req_fill_four);
                create_table_chats_with_friends(db, error, usrreq_rep);
                delete_req_struct(usrreg_req);

                sqlite3_close(db);
                mx_strdel(&err);
                return usrreq_rep;
            }
            else {
                err = mx_strdup("Cannot execute exec - error in static func check fot three column");


                (*error)->error_message = mx_strdup("Can't add user to db");
                (*error)->error_number = mx_strdup(ER_DB_INSERT);
                delete_req_struct(usrreg_req);

                sqlite3_close(db);
                mx_strdel(&err);
                return NULL;
            }

        }   else {


            delete_req_struct(usrreg_req);

            sqlite3_close(db);
            mx_strdel(&err);
            return usrreq_rep;
        }
    }
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////
static int callback(void *unused, int count, char **data, char **columns) {
    char b;

    if (count && data && columns)
        b = 'b';

    print_result(unused, data[0]);
    return 0;
}

static void print_result(char **result, char *str) {

    *result = mx_strdup(str);
}


static int check_for_three_column(db_user_registration_req *usrreg_req, sqlite3 *db, int *arr_result, char *sql_req_fill_four, char **err, errors **error)
{
    char mes_err[255];
    int rc = 0;

    char **req_arr = mx_strarrnew(3);
    req_arr[0] = mx_strdup("user_login");
    req_arr[1] = mx_strdup("user_email");
    req_arr[2] = mx_strdup("user_phone_number");
    char **req_usr = mx_strarrnew(3);
    req_usr[0] = mx_strdup(usrreg_req->user_login);
    req_usr[1] = mx_strdup(usrreg_req->user_email);
    req_usr[2] = mx_strdup(usrreg_req->user_phone_number);

    char *result = NULL;


    for (int i = 0; i < 3; i++) {

        sprintf(sql_req_fill_four, "SELECT count(*) FROM users where %s like '%s';", req_arr[i], req_usr[i]);

        rc = sqlite3_exec(db, sql_req_fill_four, callback, &result, 0);

        arr_result[i] = mx_atoi(result);    //заполнение массива результата

        free(result);


    }
    if (rc != SQLITE_OK) {
        *err = mx_strdup("Cannot execute exec - error in static func check fot three column");
        sprintf(mes_err, "Cannot execute exec - error in static func check fot three column: '%s'", sql_req_fill_four);

        (*error)->error_message = mx_strdup(mes_err);
        (*error)->error_number = mx_strdup(ER_DB_EXEC);


    }
    mx_del_strarr(&req_arr);
    mx_del_strarr(&req_usr);


    return *arr_result;
}

static void fill_structure_rep(db_user_registration_req *usrreg_req, db_user_registration_reply **usrreq_rep, int *arr_result) {




    if (arr_result[0] == 1 || arr_result[1] == 1 || arr_result[2] == 1) {
        (*usrreq_rep)->user_is_in_db = mx_strdup("1");
    } else {
        (*usrreq_rep)->user_is_in_db = mx_strdup("0");
    }


    if (arr_result[0] == 1) {
        (*usrreq_rep)->user_login = mx_strdup((usrreg_req)->user_login);
    } else {
        (*usrreq_rep)->user_login = mx_strdup("0");
    }
    if (arr_result[1] == 1) {
        (*usrreq_rep)->user_email = mx_strdup((usrreg_req)->user_email);
    } else {
        (*usrreq_rep)->user_email = mx_strdup("0");
    }
    if (arr_result[2] == 1) {
        (*usrreq_rep)->user_phone_number = mx_strdup((usrreg_req)->user_phone_number);
    } else {
        (*usrreq_rep)->user_phone_number = mx_strdup("0");
    }
}


static int add_user_in_db(db_user_registration_req *usrreg_req, sqlite3 *db, char *sql) {
    int rc = 0;
    char *err_msg = 0;
    char *password = NULL;
    password = mx_replace_substr(usrreg_req->user_password,"'","''");
    sprintf(sql, "insert into USERS(user_first_name, user_last_name, user_login, user_password, user_email, user_phone_number, registration_time)" \
            "values('%s', '%s', '%s', '%s', '%s', '%s', '%s')", usrreg_req->user_first_name, usrreg_req->user_last_name,
            usrreg_req->user_login, password, usrreg_req->user_email, usrreg_req->user_phone_number, usrreg_req->registration_time);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    mx_strdel(&password);
    if (rc != SQLITE_OK ) {

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }
    return 0;
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

static void fill_structure_rep_user_id(db_user_registration_req *usrreg_req, db_user_registration_reply **usrreq_rep, sqlite3 *db, char *sql_req_fill_four) {
    int rc = 0;

    sprintf(sql_req_fill_four, "SELECT user_id FROM users WHERE user_login LIKE '%s';", usrreg_req->user_login);
    rc = sqlite3_exec(db, sql_req_fill_four, callback, &(*usrreq_rep)->user_id, 0);
}

static void init_rep_struct(db_user_registration_reply **usrreq_rep) {
    *usrreq_rep = (db_user_registration_reply *)malloc(sizeof(db_user_registration_reply));
    (*usrreq_rep)->user_is_in_db = NULL;
    (*usrreq_rep)->user_login = NULL;
    (*usrreq_rep)->user_phone_number = NULL;
    (*usrreq_rep)->user_email = NULL;
    (*usrreq_rep)->user_id = NULL;
}

///////////////////////////////////////////////////////////////////

