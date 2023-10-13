#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"


#define REQ_BUFF 4


void usage ()
{
    printf("idiot");
}




EXIT_CODE input_check (int argc, char** argv)
{

    if (argc != 2)
    {
        return INVALID;
    }

    return file_handling(argv[1]);

}


EXIT_CODE file_handling (char* file_name)
{

    char pi[11] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    
    FILE* in = fopen(file_name, "wb");

    if (!in)
    {
        return NO_FILE;
    }

    fwrite(pi, sizeof(char), 11, in);
    fclose(in);

    in = fopen(file_name, "rb");

    if (!in)
    {
        return NO_FILE;
    }

    if (print_all_file(in) != OK)
    {
        return FILE_ERROR;
    }
    fclose(in);

    in = fopen(file_name, "rb");

    if (!in)
    {
        return NO_FILE;
    }
    fseek(in, 3, SEEK_SET);
    char* res;

    acq_req_bytes(in, &res);
    
    print_bytes(res);

    free(res);
    fclose(in);

    return OK;


}


EXIT_CODE print_all_file (FILE* in)
{

    char c[1];

    fread(&c, sizeof(char), 1, in);

    do 
    {
        printf("char: %d\n_ptr: %p\n_cnt: %d\n_base: %p\n_flag: %d\n_file: %d\n _charbuf: %d\n_bufsiz: %p\n\n",
            c[0], in->_ptr, in->_cnt, in->_base, in->_flag, 
            in->_file, in->_charbuf, in->_bufsiz);

        fread(&c, sizeof(char), 1, in);

    } while (!feof(in));

    return OK;

}


EXIT_CODE acq_req_bytes (FILE* in, char** res)
{

    char* buff = (char*)malloc(sizeof(char) * (REQ_BUFF + 1));
    fread(buff, sizeof(char), REQ_BUFF, in);

    buff[REQ_BUFF] = '\0';

    *res = buff;

    return OK;

}


void print_bytes (char* bytes)
{
    
    printf("Required row of bytes: ");

    while (*bytes != '\0')
    {
        printf("%c ", *bytes + 48);
        bytes++;
    }
    printf("\n");
    

}


int main(int argc, char *argv[]) {
    
    switch (input_check(argc, argv))
    {
        case INVALID:
            usage();
            break;
        
        case OK:
            printf("SUCCESS!");
            break;

        default:
            break;
    }
    
    return 0;

}