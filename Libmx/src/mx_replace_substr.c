#include "../inc/libmx.h"

static char *EmptyReplStr(const char *str, const char *sub, const char *replace, int SubstrAmnt) {
    int ReplacedStrLen = mx_strlen(str) + SubstrAmnt * (mx_strlen(replace) - mx_strlen(sub));
    char *EmptyStr = NULL;

    EmptyStr = mx_strnew(ReplacedStrLen);
    if (!EmptyStr)
        return NULL;
    return EmptyStr;
}

static int Get_substr_index(const char *str, const char *sub, int start) {
    int LengthOfSub = mx_strlen(sub);
    int LengthOfStr = mx_strlen(str);
    char *buff = NULL;

    buff = mx_strnew(LengthOfSub);
    if (!buff) return -1;
    int Next;

    while (start < LengthOfStr) {
        Next = 0;
        for (int j = 0; j < LengthOfSub; j++) {
            if (str[start + Next] == '\0')
                return -1;
            buff[j] = str[start + Next];
            Next++;
        }
        if (mx_strcmp(buff, sub) == 0) {
            free(buff);
            return start;
        }  
        start++; 
    }
    free(buff);
    return -1;
}

void PutSubstr(char *dst, const char *replace, int start, int *Next) {
    int ReplaceLen = mx_strlen(replace);
    
    for (int i = 0; i < ReplaceLen; i++) {
        dst[start + *Next] = replace[i];
        *Next += 1;
    }
}

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) return NULL;
    int SubstrAmnt = mx_count_substr(str, sub);
    if (SubstrAmnt == 0) return mx_strdup(str);
    int NextSubstrI = Get_substr_index(str, sub, 0);
    char *ReplacedStr = NULL;
    int Next = 0;
    int NextS = 0;
    int i = 0;
    
    ReplacedStr = EmptyReplStr(str, sub, replace, SubstrAmnt);
    if (!ReplacedStr) return NULL;
    while (str[i + Next] != '\0') {
        if (i + Next == NextSubstrI) {
            PutSubstr(ReplacedStr, replace, i, &NextS);
            Next += mx_strlen(sub);
            NextSubstrI = Get_substr_index(str, sub, i + Next);
            SubstrAmnt--;
        }
        else {
            ReplacedStr[i + NextS] = str[i + Next];
            i++;
        }
    }
    return ReplacedStr;
}

// int main() {
//     char *NewStr = NULL;
//     //NewStr = mx_replace_substr("McDonalds", "alds", "uts");
//     //NewStr = mx_replace_substr(NULL, "alds", "uts");  
//     //NewStr = mx_replace_substr("McDonalds", "m", "n");
//     //NewStr = mx_replace_substr("McDonalds, McTook, AwesomeMcCrazy", "Mc", "Good");
//     //NewStr = mx_replace_substr("McDonalds, McTook, AwesomeMcCrazy", "Mc", "M");
//     printf("%s", NewStr);
//     free(NewStr);
//     return 0;
// }
