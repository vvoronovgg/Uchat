#include "client.h"

void print_last_message(GtkWidget *list) {
    printf("%s\n", "heel10");
    for (int i = 0; cleint_data.chat->messages_senders[i] ; i++) {
        printf("%s\n", "heel11");
        mx_print_strarr(cleint_data.chat->messages_senders, "\n");
        if (strcmp(cleint_data.chat->messages_senders[i], cleint_data.chat->your_id) == 0) {
            printf("%s\n", "heel12");
            printer_message(list, cleint_data.chat->last_50_massege[i], cleint_data.chat->your_username);
            printf("%s\n", "heel13");
            printf("i in first:%d\n",i);
        }
        if (strcmp(cleint_data.chat->messages_senders[i], cleint_data.chat->friend_id) == 0) {
            printf("%s\n", "heel14");
            printer_reply_message(list, cleint_data.chat->last_50_massege[i], cleint_data.chat->friend_username);
            printf("%s\n", "heel15");
            printf("i in sec:%d\n",i);
        }
    }
}
