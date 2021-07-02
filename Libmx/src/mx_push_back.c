#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (list && !*list) {
        *list = mx_create_node(data);
        return;
    }
    else if (list && *list) {
        t_list *BackNode = mx_create_node(data);
        t_list *CurrentNode = *list;

        if (!BackNode)
            return;
        while (CurrentNode->next != NULL)
            CurrentNode = CurrentNode->next;
        CurrentNode->next = BackNode;
    } 
}

// int main() {
//     char t1[] = "Hello!";
//     char t2[] = "Goodbye";
//     char t3[] = "Hello again!";
//     char t4[] = "Goodbye again!";
//     char Last[] = "Pleased to meet you!";
//     t_list *res = NULL;
//     mx_push_back(&res, t1);//mx_create_node(t1);
//     mx_push_back(&res, t2);
//     mx_push_back(&res, t3);
//     mx_push_back(&res, t4);
//     mx_push_back(&res, Last);
//     PrintListData(res);
// }
