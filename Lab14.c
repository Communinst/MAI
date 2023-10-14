
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "Procedure.h"


void usage () 
{
    printf("./[exe_name] input_filename [key]\n\n");
    printf("                              Key list:\n");
    printf("             xor8 - exclusive or of each byte in file\n");
    printf("           xor32 - exclusive or of each 4 bytes in file\n");
    printf("mask <hex_num> - find amount of every 4 bytes equals to entered number\n\n");
}


EXIT_CODE num_check (char* str, unsigned long int *res)
{

    char* end_ptr;

    if ((*res = strtol(str, &end_ptr, 16)) < 0)
    {
        return INVALID;
    }

    return (end_ptr == str + strlen(str)) ? OK : INVALID;

}

EXIT_CODE input_control (int argc, char** argv)
{

    if (!strcmp(argv[2], "xor8"))
    {

        if (argc != 3)
        {
            return INVALID;
        }
        return xor8(argv[1]);

    }

    if (!strcmp(argv[2], "xor32"))
    {

        if (argc != 3)
        {
            return INVALID;
        }
        return xor32(argv[1]);

    }

    if (!strcmp(argv[2], "mask"))
    {
        
        if (argc != 4)
        {
            return INVALID;
        }
        return hex_mask (argv[1], argv[3]);

    }

    return INVALID;

}


EXIT_CODE xor8 (char* file)
{

    FILE* in = fopen(file, "rb");

    if (!in)
    {
        return NO_FILE;
    }

    unsigned long long int res = 0;

    sum_up_bytes(in, &res);

    printf("%llu", res);

    return OK;

}

EXIT_CODE sum_up_bytes (FILE* in, unsigned long long int *res)
{

    unsigned char c;

    while (fread(&c, sizeof(char), 1, in))
    {
    
        *res = (*res ^ c);

    }

    return OK;

}



EXIT_CODE xor32 (char* file)
{

    FILE* in = fopen(file, "rb");

    if (!in)
    {
        return NO_FILE;
    }

    unsigned long long int res = 0;

    sum_up_4_bytes (in, &res);

    printf("%llu\n", res);

    return OK;

}

EXIT_CODE sum_up_4_bytes (FILE* in, unsigned long long int *res)
{

    unsigned long int bytes;
    unsigned long int distance = 0;

    while (fread(&bytes, sizeof(int), 1, in))
    {
        distance += 4;
        *res = (*res ^ bytes);

    }
    
    fseek(in, distance, SEEK_SET);
    bytes = 0;
    unsigned char c;

    while (fread(&c, sizeof(char), 1, in))
    {

        bytes << 8;
        bytes = bytes ^ c;

    }

    *res = (*res ^ bytes);

    return OK;

}



EXIT_CODE hex_mask (char* file, char* hex)
{

    FILE* in = fopen(file, "rb");

    if (!in)
    {
        return NO_FILE;
    }

    unsigned long int hex_num = 0;
    if (num_check(hex, &hex_num) != OK)
    {
        return INVALID;
    }

    unsigned long int meeted_amount = 0;

    matching(in, &meeted_amount, hex_num);

    printf("%lu\n", meeted_amount);

    return OK;

}

EXIT_CODE matching (FILE* in, unsigned long int *res, unsigned long int hex)
{

    unsigned long int num = 0;

    fread(&num, sizeof(int), 1, in);

    do 
    {

        if (hex | num == hex)
        {
            (*res)++;
        } 

        num << 8;

    } while (fread(&num, sizeof(int), 1, in));

}



int main (int argc, char** argv) 
{

    switch (input_control(argc, argv))
    {
        case OK:
            printf("SUCCESS!\n");
            break;
        
        case INVALID:
            printf("Invalid input!\n");
            usage();
            break;

        default:
            break;
    }
    return 0;
}