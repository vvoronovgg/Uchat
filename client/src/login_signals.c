#include "client.h"

void on_field_username1_changed(GtkEntry *username) {
    cleint_data.login->username = (char *)malloc(sizeof(char) * 21);
    sprintf(cleint_data.login->username, "%s", gtk_entry_get_text(username));
}

void on_field_password1_changed(GtkEntry *userpasw) { 
    cleint_data.login->password = (char *)malloc(sizeof(char) * 21); 
    sprintf(cleint_data.login->password, "%s", gtk_entry_get_text(userpasw));
    cleint_data.login->password = hash(cleint_data.login->password, "123456789ABCDEF");
    printf("%s\n", cleint_data.login->password);
}

//clicked on btn log in, open window chat
void on_Login_btn3_clicked(GtkButton *btn, GtkWidget *list) {
    char prosto = 0;
    if (btn)
        prosto = 1;
    

    char *tmp = "g";
    char *jsn = "H";
    int i = 0;

    cleint_data.login->time_log = strdup(time_doing());
    if (cleint_data.login->username == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_login), "PLEASE ENTER YOUR USERNAME" );
        printf("%s\n", "null_field_username");
        tmp =  strdup("NULL_field");
    }
    if (cleint_data.login->password == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_login), "PLEASE ENTER YOUR PASSWORD" );
        printf("%s\n", "null_field_pasww");
        tmp =  strdup("NULL_field");
    }
    if (strcmp(tmp, "NULL_field") != 0) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_login), "");
        jsn = strdup(jsn_log_in());
        printf("jsn:%s\n", jsn);
    }
    if (strcmp(jsn, "0") == 0) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_login), "YOU SHOULD SING UP");
        printf("%s\n","you should sing up");
    }
    if (strcmp(jsn, "0") != 0 && strcmp(jsn, "1") != 0) {
        printf("%s\n", jsn);
    }
    if (strcmp(jsn, "1") == 0) {
        printf("A\n");
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat1), cleint_data.login->username);
        printf("B\n");
        gtk_stack_set_visible_child(cleint_data.gui->stack, cleint_data.gui->chat_child);
        printf("C\n");
        cleint_data.chat->your_username = strdup(cleint_data.login_jsn->username);
        cleint_data.chat->your_id = strdup(cleint_data.login_jsn->user_id);
        // cleint_data.login_jsn->userschat[0] = strdup("hello");
        // cleint_data.login_jsn->userschat[1] = strdup("my");
        // cleint_data.login_jsn->userschat[2] = strdup("dear");
        // cleint_data.login_jsn->userschat[3] = strdup("friend");
        // cleint_data.login_jsn->userschat[4] = NULL;
        // cleint_data.login_jsn->friends_f_name[0] = strdup("Kate");
        // cleint_data.login_jsn->friends_l_name[0] = strdup("Pischanska");
        // cleint_data.login_jsn->friends_email[0] = strdup("sovushkakp@gmail.com");
        // cleint_data.login_jsn->friends_ph_number[0] = strdup("0684188079");
        printf("he1\n");
        i = arr_size(cleint_data.login_jsn->userschat);
        printf("he2\n");
        cleint_data.login_jsn->userschat[i] = NULL;
        printf("he3: %i \n", i);
        if ( i != 0) {
            printf("he4\n");
            for (int i = 0; cleint_data.login_jsn->userschat[i] != NULL; i++) {
                if (cleint_data.login_jsn->userschat[i] != NULL) {
                    //printf("%s\n",cleint_data.login_jsn->userschat[i]);
                    printer(list, (const char *)cleint_data.login_jsn->userschat[i]);
                }
            }
        }
    printf("%s\n","you are log in");
    }
    //free(tmp);
}

// called when exit button is clicked

// called when window is closed
// void on_window_main_destroy() {
//   gtk_main_quit();
// }

// void on_window_chat_destroy() {
//   gtk_main_quit();
// }

void on_Sign_up_btn3_clicked(GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_stack_set_visible_child(cleint_data.gui->stack, cleint_data.gui->sing_up_child);
}
