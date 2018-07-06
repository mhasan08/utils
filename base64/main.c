#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "decode.h"

/*
 * Implementation of Base64 encoding and decoding as per RFC 4648
 *
 * Driver program for encoding and decoding
 */

int main() {
    unsigned char *data = (unsigned char *)"hello^$%@";

    char *base64 = base64Encode(data, 9);

    printf("base 64 encoded => %s\n", base64);

    unsigned char *decoded = base64Decode(base64);
    printf("base 64 decoded => %s\n", decoded);

    free(base64);
    free(decoded);

    return 0;
}