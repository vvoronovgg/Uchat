#include "../inc/libmx.h"

void PrintListData(t_list *list) {
    t_list *CurrentNode = list;

    while(CurrentNode != NULL) {
        write(1, CurrentNode->data, mx_strlen((char *)CurrentNode->data));
        mx_printchar('\n');
        CurrentNode = CurrentNode->next;
    }
}
