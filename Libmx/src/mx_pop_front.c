#include "../inc/libmx.h"

void mx_pop_front(t_list **head) {
    if (head && *head) {
        t_list *NextNode = *head;
        t_list *NodeToDel = *head;
        
        NextNode = NextNode->next;
        NodeToDel->next = NULL;
        NodeToDel->data = NULL;
        free(NodeToDel);
        NodeToDel = NULL;
        *head = NextNode;
    }
}

// int main() {
//     char t1[] = "Hello!";
//     char t2[] = "Goodbye";
//     char t3[] = "Hello again!";
//     char t4[] = "Goodbye again!";
//     char Last[] = "Pleased to meet you!";
//     t_list *res = mx_create_node(t1);

//     mx_push_front(&res, t2);
//     mx_push_front(&res, t3);
//     mx_push_front(&res, t4);
//     mx_push_back(&res, Last);
//     PrintListData(res);
//     mx_pop_front(&res);
//     printf("After deleting front node:\n");
//     PrintListData(res);
// }
