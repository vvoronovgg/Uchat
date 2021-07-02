#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (arr && s && size > 0 && count) {
        int Index_first = 0;
        int Index_last = size - 1;
        int Index_middle;

        while (Index_first <= Index_last) {
            (*count)++;
            Index_middle = Index_first + (Index_last - Index_first) / 2;
            if (mx_strcmp(s, arr[Index_middle]) > 0)
                Index_first = Index_middle + 1;
            else if (mx_strcmp(s, arr[Index_middle]) < 0)
                Index_last = Index_middle - 1;
            else 
                return Index_middle;
        }
        *count = 0;
    }
    return -1;
}

/* int main() {
    char *arr[] = {"222", "Abcd", "aBc", "ab", "az", "z"};
    int count = 0;
    printf("k = %d, count = %d", mx_binary_search(arr, 6, "aBc", &count), count);
    return 0;
}
 */
