//
// Created by Munawar Hasan on 05/07/18.
//

#include <memory.h>
#include <stdlib.h>
#include "decode.h"

/*
 * RFC 4648
 * Base64 Decoding
 * */

size_t output_size(char *d){
    size_t input_size = strlen(d);

    size_t out_size = 0;
    if (input_size > 4){
        out_size = out_size + (((input_size - 4) / 4) * 3);
    }

    if (d[input_size - 1] != '='){
        out_size = out_size + 3;
    } else{
        if (d[input_size - 2] == '=')
            out_size = out_size + 1;
        else
            out_size = out_size + 2;
    }

    return out_size;

}

int base64DecodeTable(char c){
    if (c == '+')
        return 62;
    if (c == '/')
        return 63;

    int asciiValue = (int)c;
    if (asciiValue <= 57)
        return (asciiValue + 4);
    if (asciiValue >= 65 && asciiValue <= 90)
        return (asciiValue - 65);
    if (asciiValue >= 97 && asciiValue <= 122)
        return (asciiValue - 71);
}

unsigned char *base64Decode(char *data){
    size_t data_length = strlen(data);

    size_t out_size = output_size(data);

    unsigned char *output = (unsigned char *)malloc(sizeof(unsigned char) * out_size);

    int index = 0;
    for (int i = 0; i < data_length; i++) {

        if (data[i + 2] == '=' || data[i + 3] == '='){

            if (data[i + 2] == '='){
                int base64Value = (base64DecodeTable(data[i]) << 6) | (base64DecodeTable(data[++i]));
                output[index] = (unsigned char)(base64Value >> 4);
            }

            else if (data[i + 3] == '='){
                int base64Value = (base64DecodeTable(data[i]) << 18) | (base64DecodeTable(data[++i]) << 12) | (base64DecodeTable(data[++i]) << 6);
                output[index++] = (unsigned char)(base64Value >> 16);
                output[index] = (unsigned char)((base64Value >> 8) & 0xff);
            }

            break;
        }


        int base64Value = (base64DecodeTable(data[i]) << 18) | (base64DecodeTable(data[++i]) << 12) | (base64DecodeTable(data[++i]) << 6) | (base64DecodeTable(data[++i]));

        output[index++] = (unsigned char)(base64Value >> 16);
        output[index++] = (unsigned char)((base64Value >> 8) & 0xff);
        output[index++] = (unsigned char)((base64Value) & 0xff);

    }

    return output;

}