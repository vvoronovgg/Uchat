#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
    if (head && *head) {
        t_list *CurrentNode = *head;
        t_list *PreviousNode = *head;

        while (CurrentNode->next != NULL) {
            CurrentNode = CurrentNode->next;
            if (PreviousNode->next->next != NULL)
                PreviousNode = PreviousNode->next;
        }
        CurrentNode->data = NULL;
        free(CurrentNode);
        CurrentNode = NULL;
        PreviousNode->next = NULL;
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
//     mx_pop_back(&res);
//     printf("After deleting front node:\n");
//     PrintListData(res);
// }
