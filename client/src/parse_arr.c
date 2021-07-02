#include "client.h"

char **parse_arr(char *str, char *key) {
    cJSON *array = NULL;
    cJSON *object = cJSON_Parse(str);
    cJSON *item = NULL;
    array = cJSON_GetObjectItem(object, key);         //достаю массив 'strarray' из объекта
    int size = cJSON_GetArraySize(array); 
    printf("size :%d\n", size);
    char **arr = (char **)malloc(sizeof(char *) * (size + 1));
    for (int j = 0; j <= (size + 1); j++) {
        arr[j] = NULL;
    }
    for (int i = 0; i < size; i++) {
        item = cJSON_GetArrayItem(array, i);    //достаю элемент массива
        arr[i] = strdup(item->valuestring);                                                   //strdup в помощь, чтобы скопировать значение
    }
    // cJSON_Delete(object);   //удаляю json объект и все его комплектующие
    //object = NULL;
    return arr;
    //mx_del_strarr(&arr);
}
