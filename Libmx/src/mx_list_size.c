#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
    int NodesAmnt = 0;
    t_list *CurrentNode = list;

    while (CurrentNode) {
        CurrentNode = CurrentNode->next;
        NodesAmnt++;
    }
    return NodesAmnt;
}

// int main() {
//     char t1[] = "Hello!";
//     char t2[] = "Goodbye";
//     char t3[] = "Hello again!";
//     char t4[] = "Goodbye again!";
//     char Last[] = "Pleased to meet you!";
//     t_list *res = mx_create_node(t1);
//     mx_push_back(&res, "Hi");
//     mx_push_front(&res, t2);
//     mx_push_front(&res, t3);
//     mx_push_front(&res, t4);
//     mx_push_back(&res, Last);
//     printf("SizeB: %d\n", mx_list_size(res));
//     PrintListData(res);
//     mx_pop_back(&res);
//     mx_pop_front(&res);
//     printf("SizeA: %d\n", mx_list_size(res));
//     printf("After deleting front node:\n");
//     PrintListData(res);
// }
