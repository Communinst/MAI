
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
    STOP,
} EXIT_CODE;


void warning ();


void usage ();


EXIT_CODE double_check (char *argv, long int *value, int base);


EXIT_CODE input_control ();


EXIT_CODE acquire_base (long int *base);


EXIT_CODE string_analysis (char **result);


EXIT_CODE acquire_string (char **result);


EXIT_CODE conv_tenth_any (long int num, long int base, char **result);



#endif