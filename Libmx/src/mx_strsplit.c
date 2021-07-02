#include "../inc/libmx.h"

static char *CopySubStr(char *dst, const char *src, int SubStrIndex, char delim) {
    int j = 0;

    while (src[SubStrIndex] != delim && src[SubStrIndex] != '\0') {
        dst[j] = src[SubStrIndex];
        j++;
        SubStrIndex++;
    }
    return dst;
}

static int DefWordLen (const char *Str, int start, char delim) {
    int Next = 0;
    int WordLen = 0;

    while (Str[start + Next] != delim && Str[start + Next] != '\0') {
        WordLen++;
        Next++;
    }
    return WordLen;
}

char **mx_strsplit(const char *s, char c) {
    if (!s || *s == '\0')
        return NULL;
    int WordsAmount = mx_count_words(s, c);
    int i = 0;
    int WordIndex = 0;
    char **SepdWords = NULL;
    int WordLen = 0;

    SepdWords = (char **)malloc(sizeof(char *) * (WordsAmount + 1));   
    if (!SepdWords)
        return NULL;
    while (s[i] != '\0' && WordIndex < WordsAmount) {
        if (s[i] != c) {
            WordLen = DefWordLen(s, i, c);
            SepdWords[WordIndex] = mx_strnew(WordLen);
            if (!SepdWords[WordIndex])
                return NULL;
            SepdWords[WordIndex] = CopySubStr(SepdWords[WordIndex], s, i, c);
            WordIndex++;
        }
        if (WordLen == 0)
            i++;
        else {
            i = i + WordLen;
            WordLen = 0;
        }
    }
    SepdWords[WordsAmount] = NULL;
    return SepdWords;
}

// int main () {
//     mx_print_strarr(mx_strsplit("*Good bye,**Mr.*Anderson.****",'*'), " ");
//     mx_print_strarr(mx_strsplit("*\tGood\tbye,*Mr.*Anderson.**\t1*",'*'), " ");
//     //printf("END: %s\n", *s);
//     return 0;
// }
