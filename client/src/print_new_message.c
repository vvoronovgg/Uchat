#include "client.h"

void print_new_message(void) {
    //     if (strcmp(cleint_data.new_message->sender_login, gtk_widget_get_name(node->data)) == 0) {
    //         write(2,"teh2\n",5);
    //         printer(cleint_data.gui->list_chat, cleint_data.new_message->sender_login);
    //     }
    // }
    if (strcmp(cleint_data.new_message->sender_login, gtk_label_get_text(GTK_LABEL(cleint_data.gui->label_chat1))) == 0) {
        write(2,"teh3\n",5);
        printer_reply_message(cleint_data.gui->list_message, cleint_data.new_message->new_message, cleint_data.new_message->sender_login);
    }
}
