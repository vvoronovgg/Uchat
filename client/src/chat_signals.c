#include "client.h"

static gint scroll() {
    GtkAdjustment *ad = gtk_scrolled_window_get_vadjustment(cleint_data.gui->swindow_chat);
    double l_pos = gtk_adjustment_get_upper(ad) + gtk_adjustment_get_page_increment(ad);

    gtk_adjustment_set_value(ad, l_pos);
    return false;
}

static void display_message(GtkWidget *list, char *login, char *message) {
    printer_message(list, (const char *)message, (const char *)login);
    gtk_entry_set_text(GTK_ENTRY(cleint_data.gui->entr_message), "");
    g_timeout_add(10, scroll, NULL);
}

static char *cat_message(char *message) {
    char *res = NULL;
    int count_space = strlen(message) / 70;
    int count = 0;

    if (count_space == 0)
        return message;
    if (strlen(message) < 70)
        return message;
    res = mx_strnew(strlen(message) + count_space);
    for (int i = 0; message[i]; i++) {
        if (i % 70 == 0 && i != 0 && message[i] != ' ') {
            res[count] = ' ';
            count++;
        }
        res[count] = message[i];
        count++;
    }
    return res;
}

void on_send_btn5_clicked(GtkButton *btn) {
    char prosto = 0;
    if (btn)
        prosto = 1;

    cleint_data.chat->time = strdup(time_doing());
    cleint_data.chat->message = (char *)gtk_entry_get_text(GTK_ENTRY(cleint_data.gui->entr_message));
    if (cleint_data.chat->message == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat2), "massege is too short");
        printf("%s\n", "errror");
    }
    else if (strlen(cleint_data.chat->message) < 1) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat2), "massege is too short");
        printf("%s\n", "massege is too short");
    }
    else if (strlen(cleint_data.chat->message) > 300) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat2), "massege is too big");
        printf("%s\n", "massege is too big");
    }
    else {
        jsn_send_message();
        cleint_data.chat->message = cat_message(cleint_data.chat->message);
	    if (cleint_data.chat->message && strcmp(cleint_data.chat->message, "")) {
		    display_message(cleint_data.gui->list_message, cleint_data.login->username, cleint_data.chat->message);
	    }
    } 
}

void on_enter_message_changed(GtkEntry *entr) { 
    cleint_data.chat->message = (char *)gtk_entry_get_text(GTK_ENTRY(entr));
    cleint_data.chat->time = strdup(time_doing());
    if (cleint_data.chat->message == NULL) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat2), "massege is too short");
        printf("%s\n", "errror");
    }
    else if (strlen(cleint_data.chat->message) < 1) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat2), "massege is too short");
        printf("%s\n", "massege is too short");
    }
    else if (strlen(cleint_data.chat->message) > 300) {
        gtk_label_set_text(GTK_LABEL(cleint_data.gui->label_chat2), "massege is too big");
        printf("%s\n", "massege is too big");
    }
    else {
        jsn_send_message();
        cleint_data.chat->message = cat_message(cleint_data.chat->message);
	    if (cleint_data.chat->message && strcmp(cleint_data.chat->message, "")) {
		    display_message(cleint_data.gui->list_message, cleint_data.login->username, cleint_data.chat->message);
	    }
    } 
}

void on_friends_profile_btn_clicked(GtkButton *btn) { 
    char prosto = 0;
    if (btn)
        prosto = 1;
    
    gtk_stack_set_visible_child(cleint_data.gui->stack_chat, cleint_data.gui->user_and_friends_child);
}
