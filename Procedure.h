
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{
    OK = 0,
    INVALID,
    BAD_ALLOC,

} EXIT_CODE;


EXIT_CODE string_rev (char** dest, char* src);


EXIT_CODE last_residue (int value, char** dest);


EXIT_CODE sum_up (char** sum, char* adden, int base);


EXIT_CODE long_str_sum (char** result, int base, int amount, ...);


#endif