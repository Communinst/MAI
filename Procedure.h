
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{

    OK = 0,
    INVALID,
    BAD_ALLOC,
    
} EXIT_CODE;


EXIT_CODE sum_str_long (char** res, int base, int amount, ...);


EXIT_CODE sum_up (char** result, char* adding);


EXIT_CODE adder (char** result, char crawler,int* amount);

#endif