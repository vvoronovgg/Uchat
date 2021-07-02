#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "gtk/gtk.h"

#include <openssl/sha.h>
#include <openssl/ssl.h>

#include <time.h> 
#include <../../cjson/inc/cJSON.h>
#include <../../Libmx/inc/libmx.h>

#define PORT 8080 
#define SA struct sockaddr 

typedef struct s_send_jsn {
    char *sender_id;
    char *sender_f_name;
    char *sender_l_name;
    char *sender_login;
    char *sender_email;
    char *sender_ph_number;
    char *receiver_id;
    char *new_message;
    char *date;
}               t_send_jsn;

GMutex muxtex;

typedef struct s_client_tmp {
    int argc;
    char **argv;
    int socket;
} t_client_tmp;

typedef struct s_profile {
    char *search_user_id;
    char *search_username;
    char *search_user_fn;
    char *search_user_ln;
    char *search_user_em;
    char *search_user_num;
    char *search_user_fl;
    char *new_pass;
    char *new_conf_pass;
    int count_arr;
}               t_profile;

typedef struct s_gui {
    GtkStack *stack;
    GtkStack *stack_chat;
    GtkStack *settings_fix;
    GtkWidget *login_child;
    GtkWidget *sing_up_child;
    GtkWidget *chat_child;
    GtkWidget *chat_child0;
    GtkWidget *user_and_friends_child;
    GtkWidget *err_login;
    GtkWidget *err_singup;
    GtkWidget *entr_message;
    GtkWidget *entr_search;
    GtkWidget *label_nickname;
    GtkWidget *label_id;
    GtkWidget *label_email;
    GtkWidget *label_number;
    GtkWidget *label_not_found;
    GtkWidget *label_chat1;
    GtkWidget *label_chat2;
    GtkWidget *sender;
    GtkWidget *list_message;
    GtkWidget *list_chat;
    GtkWidget *chang_pass;
    GtkWidget *settings;
    GtkWidget *fix_set;
    GtkScrolledWindow *swindow_chat;
    GtkCssProvider *css_provider;
}               t_gui;

typedef struct s_login_jsn {
    char *username;
    char *firstname;
    char *lastname;
    char *email;
    char *phonenum;
    char *passw;
    char *time_login;
    char *user_id;
    char **userschat;
    char **friends_f_name;
    char **friends_l_name;
    char **friends_id;
    char **friends_ph_number;
    char **friends_email;
}               t_login_jsn;

typedef struct s_signup {
    char *username_sign;
    char *firstname_sign;
    char *lastname_sign;
    char *email_sign;
    char *phonenum_sign;
    char *passw_sign;
    char *confpass_sign;
    char *time_sigin;
    char *user_id;
}               t_signup;

typedef struct s_login {
    char *username;
    char *password;
    char *time_log;
}               t_login;

typedef struct s_chat {
    char *message;
    char *your_username;
    char *your_id;
    char *friend_username;
    char *friend_id;
    char *time;
    char **last_50_massege;
    char **dates;
    char **messages_senders;
    int arr_count;
}               t_chat;

typedef struct s_struct {
    int soketfd;
    t_send_jsn *new_message;
    t_profile *profile;
    t_chat *chat;
    t_gui *gui;
    t_login_jsn *login_jsn;
    t_signup *signup;
    t_login *login;
}              t_struct;

t_struct cleint_data;

int main(int argc, char **argv);
int mx_interface(int argc, char **argv, int sockfd);
const char *time_doing(void);
char *jsn_log_in(void);
char *jsn_sign_in(void);
char *mx_strnew(const int size);
char *hash(char *data, char *key);
char *jsn_profile(char *search);
char *mx_strjoin(const char *s1, const char *s2);
char **parse_arr(char *str, char *key);
void printer(GtkWidget *list, const char *login);
char *strjoin_f_and_l(char *f, char *l);
int arr_size(char **arr);
void add_to_arr_new_contact (void);
void mx_print_strarr(char **arr, const char *delim);
void mx_clear_container(GtkWidget *con);
void printer_message(GtkWidget *list, const char *message, const char *name);
void printer_reply_message(GtkWidget *list, const char *message, const char *name);
void print_last_message(GtkWidget *list);
char *jsn_get_chat_with_user(void);
void print_new_message(void);
void jsn_get_message(void);
char *jsn_change_pasw(void);
void jsn_send_message(void);
//void jsn_get_message(void *client);

#endif
