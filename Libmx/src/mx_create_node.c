#include "../inc/libmx.h"

t_list *mx_create_node(void *data) {
    t_list *Head = NULL;
    t_list *tmp = (t_list *)malloc(sizeof(t_list));
    if (!tmp)
        return NULL;
    tmp->data = data;
    tmp->next = NULL;
    Head = tmp;
    return Head;
}

// int main() {
//     char *text = "Text";
//     t_list *res;
//     res = mx_create_node(text);
//     printf("%s", (char *)res->data);
//     free(res);
//     return 0;
// }
