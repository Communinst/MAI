
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
} EXIT_CODE;


void usage ();

EXIT_CODE input_check(int argc, char **argv);

EXIT_CODE file_check(char *argv, FILE* in);

EXIT_CODE extention_check(char *argv);


#endif