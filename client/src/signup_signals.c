#include "client.h"

void on_Sign_up_btn4_clicked(GtkButton *btn) {
    char prosto = 0;
    if (btn)
        prosto = 1;
    char *tmp = strdup("NULL_ok");
    char *jsn = NULL;
    cleint_data.signup->time_sigin = strdup(time_doing());
    if (cleint_data.signup->username_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE ENTER YOUR USERNAME" );
        printf("%s\n", "null_field_username");
        tmp =  strdup("NULL_field");
    }
    if (cleint_data.signup->firstname_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE ENTER YOUR FIRST NAME" );
        printf("%s\n", "null_field_firstname");
        tmp =  strdup("NULL_field");
    }
    if (cleint_data.signup->lastname_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE ENTER YOUR LAST NAME" );
        printf("%s\n", "null_field_lastname");
        tmp =  strdup("NULL_field");
    }
    if (cleint_data.signup->email_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE ENTER YOUR EMAIL" );
        printf("%s\n", "null_field_email");
        tmp =  strdup("NULL_field");
    }   
    if (cleint_data.signup->phonenum_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE ENTER YOUR PHONE NUMBER" );
        printf("%s\n", "null_field_phonenum");
        tmp =  strdup("NULL_field");
    } 
    if (cleint_data.signup->passw_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE ENTER YOUR PASSWORD" );
        printf("%s\n", "null_field_passw");
        tmp =  strdup("NULL_field");
    } 
    if (cleint_data.signup->confpass_sign == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "PLEASE CONFIRM YOUR PASSWORD" );
        printf("%s\n", "null_field_confpassw");
        tmp =  strdup("NULL_field");
    }
    if (strcmp(tmp, "NULL_ok") == 0) {
        if (strcmp(cleint_data.signup->passw_sign, cleint_data.signup->confpass_sign) == 0) {
            jsn = strdup(jsn_sign_in());
            if (strcmp(jsn, "1") == 0) {
                gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "YOU ARE SIGN IN");
                printf("%s\n", "you are sign in");
            }
            if (strcmp(jsn, "1") != 0 && strcmp(jsn, "0") != 0) {
                gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), jsn);
                printf("%s\n", jsn);
            }
            if (strcmp(jsn, "0") == 0) {
            cleint_data.chat->your_username = strdup(cleint_data.signup->username_sign); 
            cleint_data.chat->your_id = strdup(cleint_data.signup->user_id);
            gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat1), cleint_data.signup->username_sign);
            gtk_stack_set_visible_child(cleint_data.gui->stack, cleint_data.gui->chat_child);
            }
        }
        else 
            gtk_label_set_text(GTK_LABEL(cleint_data.gui->err_singup), "CHECK THE PASSWORD ENTRY");
    }
}

void on_Login_btn4_clicked(GtkButton *btn1) {
    char prosto = 0;
    if (btn1)
        prosto = 1;
    gtk_stack_set_visible_child(cleint_data.gui->stack, cleint_data.gui->login_child);
}

void on_Username_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->username_sign = (char *)malloc(sizeof(char) * 50);  
    sprintf(cleint_data.signup->username_sign, "%s", gtk_entry_get_text(entr));
    cleint_data.login->username = strdup(cleint_data.signup->username_sign);
}

void on_first_name_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->firstname_sign = (char *)malloc(sizeof(char) * 50);  
    sprintf(cleint_data.signup->firstname_sign, "%s", gtk_entry_get_text(entr));
}

void on_Last_name_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->lastname_sign = (char *)malloc(sizeof(char) * 20);  
    sprintf(cleint_data.signup->lastname_sign, "%s", gtk_entry_get_text(entr));
}

void on_Email_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->email_sign = (char *)malloc(sizeof(char) * 100);  
    sprintf(cleint_data.signup->email_sign, "%s", gtk_entry_get_text(entr));
}

void on_Phone_number_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->phonenum_sign = (char *)malloc(sizeof(char) * 20);  
    sprintf(cleint_data.signup->phonenum_sign, "%s", gtk_entry_get_text(entr));
}

void on_Password_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->passw_sign = (char *)malloc(sizeof(char) * 20);  
    sprintf(cleint_data.signup->passw_sign, "%s", gtk_entry_get_text(entr));
    cleint_data.signup->passw_sign = hash(cleint_data.signup->passw_sign, "123456789ABCDEF");
}

void on_Confirm_password_entry1_changed(GtkEntry *entr) {
    cleint_data.signup->confpass_sign = (char *)malloc(sizeof(char) * 20);  
    sprintf(cleint_data.signup->confpass_sign, "%s", gtk_entry_get_text(entr));
    cleint_data.signup->confpass_sign = hash(cleint_data.signup->confpass_sign, "123456789ABCDEF");
}
