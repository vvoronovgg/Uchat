#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
    if (list && !*list) {
        *list = mx_create_node(data);
        return;
    }
    else if (list && *list) {
        t_list *FrontNode = mx_create_node(data);
        t_list *NextNode = *list;

        if (!FrontNode)
            return; 
        FrontNode->next = NextNode;
        *list = FrontNode;
    }
}

// int main() {
//     char text[] = "Hello!";
//     char NewText[] = "Goodbye";
//     t_list *res = NULL;
//     mx_push_front(&res, text);
//     mx_push_front(&res, NewText);
//     PrintListData(res);
// }
