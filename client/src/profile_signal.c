#include "client.h"

void on_search_username_entry(GtkEntry *entr, GtkWidget *list) {
    char *jsn = "h";
    char *search = NULL;
    bool tmp = 0;

    search = (char *)gtk_entry_get_text(GTK_ENTRY(entr));
    
    //printf("%s\n", search);
    jsn = strdup(jsn_profile(search));
    if (search == NULL || strcmp(search, "") == 0) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_not_found), "PLEASE ENTER USERNAME YOUR FRIEND:)");
        printf("%s\n", "PLEASE ENTER USERNAME YOUR FRIEND");
    }
    if (strcmp(jsn, "0") != 0 && strcmp(jsn, "1") != 0) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_not_found), jsn);
        printf("%s\n", jsn);
    }
    if (strcmp(jsn, "0") == 0) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_not_found), "USER NOT FAUND");
        printf("%s\n", "USER NOT FAUND");
    }
    if (strcmp(jsn, "1") == 0) {
        cleint_data.profile->search_username = strdup(search);
        for (int i = 0; cleint_data.login_jsn->userschat[i]; i++) {
            if (strcmp(cleint_data.login_jsn->userschat[i], cleint_data.profile->search_username) == 0) {
                gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_not_found), "You have this contact:)");
                tmp = 1;
            }
        }
        if (tmp == 0) {
            add_to_arr_new_contact();
            mx_print_strarr(cleint_data.login_jsn->userschat, "\n");
            printer(list, (const char *)search);
            gtk_entry_set_text(GTK_ENTRY(cleint_data.gui->entr_search), "");
        }
    }
    printf("%s\n", search);
}

void on_up_clicked(GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_stack_set_visible_child(cleint_data.gui->stack_chat, cleint_data.gui->chat_child0);
}

void on_list_row_clicked(GtkWidget *list) {
    int id = gtk_list_box_row_get_index (gtk_list_box_get_selected_row (GTK_LIST_BOX(list)));
    printf("%i\n", id);
    gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_nickname), cleint_data.login_jsn->userschat[id]);//cleint_data.profile->search_username
    gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_id), strjoin_f_and_l(cleint_data.login_jsn->friends_f_name[id], cleint_data.login_jsn->friends_l_name[id]));
    gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_email), cleint_data.login_jsn->friends_email[id]);
    gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_number), cleint_data.login_jsn->friends_ph_number[id]);
    cleint_data.chat->friend_id = cleint_data.login_jsn->friends_id[id];
    cleint_data.chat->friend_username = cleint_data.login_jsn->userschat[id];
}

void on_send_message_btn(GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    

    char *jsn = NULL;
    jsn = strdup(jsn_get_chat_with_user());
    cleint_data.chat->arr_count = 50;
    printf("arrcount:%d\n",cleint_data.chat->arr_count);
    const char *str = gtk_label_get_text(GTK_LABEL(cleint_data.gui->label_nickname));
    if (strcmp(jsn, "1") == 0) {
        if (strcmp(str, gtk_label_get_text(GTK_LABEL(cleint_data.gui->label_chat1))) == 0) {
            gtk_stack_set_visible_child(cleint_data.gui->stack_chat, cleint_data.gui->chat_child0);
        }
        else
        {
            mx_clear_container(cleint_data.gui->list_message);
            gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat1), str);
            if (cleint_data.chat->arr_count > 0) {
                print_last_message(cleint_data.gui->list_message);
            }
            gtk_stack_set_visible_child(cleint_data.gui->stack_chat, cleint_data.gui->chat_child0); 
        }
    }
    else if (strcmp(jsn, "0") == 0) {
        printf("%s\n", "ups, pls try again:)");
    }
}
//settings 

void on_settings_clicked (GtkButton *b, GtkWidget *w) { 
    char prosto = 0;
    if (b)
        prosto = 1;
    

    gtk_widget_show (w);
    gtk_widget_show_all(w);
}

void on_password_chan_btn_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    

    gtk_stack_set_visible_child(cleint_data.gui->settings_fix, cleint_data.gui->chang_pass);
}

void on_theme_btn_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_stack_set_visible_child(cleint_data.gui->settings_fix, cleint_data.gui->settings);
}

void on_1c_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_css_provider_load_from_path(cleint_data.gui->css_provider, "theme1.css", NULL);
}

void on_2c_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_css_provider_load_from_path(cleint_data.gui->css_provider, "theme2.css", NULL);
}

void on_3c_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_css_provider_load_from_path(cleint_data.gui->css_provider, "theme3.css", NULL);
}

void on_4c_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    
    gtk_css_provider_load_from_path(cleint_data.gui->css_provider, "theme4.css", NULL);
}

void on_exit_btn_clicked (GtkButton *b, GtkWidget *w) { 
    char prosto = 0;
    if (b)
        prosto = 1;
    gtk_widget_hide(w);
}

void on_exit_btn1_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    gtk_stack_set_visible_child(cleint_data.gui->settings_fix ,cleint_data.gui->fix_set);
}

void on_exit_btn2_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    gtk_stack_set_visible_child(cleint_data.gui->settings_fix ,cleint_data.gui->fix_set);
}

void on_logout_clicked (GtkButton *b) {
    char prosto = 0;
    if (b)
        prosto = 1;
    gtk_stack_set_visible_child(cleint_data.gui->stack, cleint_data.gui->login_child);
    mx_clear_container(cleint_data.gui->list_message);
    mx_clear_container(cleint_data.gui->list_chat);
}

void on_new_password_changed(GtkEntry *entr) {
    cleint_data.profile->new_pass = (char *)malloc(sizeof(char) * 100);  
    sprintf(cleint_data.profile->new_pass, "%s", gtk_entry_get_text(entr));
    cleint_data.profile->new_pass = hash(cleint_data.signup->passw_sign, "123456789ABCDEF");
}

void on_new_confirm_password_changed(GtkEntry *entr) {
    cleint_data.profile->new_conf_pass = (char *)malloc(sizeof(char) * 100);  
    sprintf(cleint_data.profile->new_conf_pass, "%s", gtk_entry_get_text(entr));
    cleint_data.profile->new_conf_pass = hash(cleint_data.signup->passw_sign, "123456789ABCDEF");
}

void on_change_btn_clicked (GtkButton *b, GtkLabel *label) {
    char prosto = 0;
    if (b)
        prosto = 1;
    char *jsn = NULL;

    if (strcmp(cleint_data.profile->new_pass, cleint_data.profile->new_conf_pass) == 0) {
        jsn = strdup(jsn_change_pasw());
        if (strcmp(jsn, "0") == 0) {
            gtk_label_set_text(label, "try again");
        }
        if (strcmp(jsn, "1") == 0) {
            gtk_label_set_text(label, "your password has been changed");
        }
        if (strcmp(jsn, "1") != 0 && strcmp(jsn, "0") != 0) {
            gtk_label_set_text(label, jsn);
        }
    }
}