
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE,
    EoF,
} EXIT_CODE;


void usage ();


EXIT_CODE is_str_appropriate (char *str, long int *lint_based, int base);


EXIT_CODE input_check (int argc, char **argv);


EXIT_CODE write_file (int argc, char **argv);


EXIT_CODE aquire_str (FILE* f, char **str, int *base);


EXIT_CODE skip_dividers (FILE* f, int *res);


#endif