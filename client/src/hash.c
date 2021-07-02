#include "client.h"

char *hash(char *data, char *key) {
    unsigned char *result = NULL;
    unsigned int result_len = 0;

    result = HMAC(EVP_sha256(), (const void *)key, strlen(key),
                  (const unsigned char *)data, strlen(data), result,
                  &result_len);
    return (char *)result;
}
