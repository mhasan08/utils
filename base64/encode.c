//
// Created by Munawar Hasan on 05/07/18.
//

#include "encode.h"
#include <stdlib.h>

/*
 * RFC 4648
 * Base64 Encoding
 * */

char base64_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

size_t encoded_length(size_t input_length){

    if ((input_length % 3) == 0){
        return (4 * (input_length / 3));
    } else {
        return (4 * ((input_length / 3) + 1));
    }
}


char *base64Encode(unsigned char *data, size_t data_length){

    if (data_length == 0){
        return NULL;
    }

    size_t out_length = encoded_length(data_length);

    char *output = (char *)malloc(sizeof(char) * (out_length));


    int index = 0;
    for(int i = 0; i < data_length; i++) {

        if ((i + 2) <= (data_length - 1)) {
            int asciiValue = ((int) data[i] << 16) | ((int) data[++i] << 8) | ((int) data[++i]);

            output[index++] = base64_table[asciiValue >> 18];
            output[index++] = base64_table[(asciiValue >> 12) & 0x3f];
            output[index++] = base64_table[(asciiValue >> 6) & 0x3f];
            output[index++] = base64_table[(asciiValue >> 0) & 0x3f];

        }
    }


    if ((data_length % 3) == 1){
        int asciiValue = (int)data[data_length - 1];
        int fValue = asciiValue >> 2;
        int sValue = (asciiValue & 0x03) << 4;

        output[index++] = base64_table[fValue];
        output[index++] = base64_table[sValue];
        output[index++] = '=';
        output[index] = '=';

    }
    if ((data_length % 3) == 2){
        int asciiValue = ((int)data[data_length - 2] << 8) | ((int)data[data_length - 1]);

        output[index++] = base64_table[asciiValue >> 10];
        output[index++] = base64_table[(asciiValue >> 4) & 0x3f];
        output[index++] = base64_table[(asciiValue << 2) & 0x3f];
        output[index] = '=';
    }

    return output;
}