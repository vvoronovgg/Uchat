#include "../inc/libmx.h"

// static bool Compare(void *first, void *second) {
//     if (mx_strcmp((const char *)first, (const char *)second) > 0)
//         return true;
//     else return false;
// }

static void RerollNodes(t_list **lst, t_list *Current, t_list **Previous, bool *head) {
    t_list *AfterCur = Current->next;
    t_list *AfterPrev = *Previous;
    
    if (*head && Current->next != NULL) {
       *lst = Current->next;
       *Previous = *lst;
       Current->next = Current->next->next;
       AfterCur->next = Current;
       *head = false; 
    }
    else if (!*head && Current->next != NULL) {
        AfterPrev->next = Current->next;
        *Previous = Current->next;
        Current->next = Current->next->next;
        AfterCur->next = Current;
    }
}

t_list *mx_sort_list(t_list *lst, bool(*cmp)(void*, void*)) {
    if (lst && cmp) {
        t_list *Current = lst;
        t_list *Previous = NULL;
        int ListSize = mx_list_size(lst);
        bool head;

        for (int i = 1; i < ListSize; i++) {
            head = true;
            Current = lst;
            for (int j = 0; j < ListSize - i; j++) {
                if ((*cmp)(Current->data, Current->next->data))
                    RerollNodes(&lst, Current, &Previous, &head);
                else {
                    Previous = Current;
                    Current = Current->next;
                    head = false;
                }
            }
        }
    }
    return lst;   
}

// int main() {
//     // char text[] = "1";
//     // char NewText[] = "2";
//     // char Text1[] = "7";
//     // char Text2[] = "8";
//     // char Text3[] = "3";
//     int a1 = 917;
//     int a2 = 895;
//     int a3 = 518;
//     int a4 = 408;
//     int a5 = 94;
//     int a6 = -417;
//     int a7 = -862;
//     int a8 = -864;

//     bool (*cmp)(void *, void *);
//     cmp = Compare;
//     t_list *res = NULL;
//     mx_push_back(&res, &a1);
//     mx_push_back(&res, &a2);
//     mx_push_back(&res, &a3);
//     mx_push_back(&res, &a4);
//     mx_push_back(&res, &a5);
//     mx_push_back(&res, &a6);
//     mx_push_back(&res, &a7);
//     mx_push_back(&res, &a8);
    
    
//     printf("\tBefore sorting:\n");
//     PrintListData(res);
//     res = mx_sort_list(res, cmp);
//     printf("\tAfter sorting:\n");
//     PrintListData(res);
//     return 0;
// }
