
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE
} EXIT_CODE;


void usage ();


EXIT_CODE input_check (int argc, char **argv);

EXIT_CODE flag_handling (char flag, int argc, char **argv);

EXIT_CODE r_flag_handling (char ** argv);

EXIT_CODE write_both (FILE *f1, FILE *f2, char *out);

EXIT_CODE skip_dividers (FILE* f, int *res);

EXIT_CODE write_the_rest_file (FILE *f, FILE* out, int carr);


EXIT_CODE a_flag_handling (char **argv);

EXIT_CODE multiplicity_write (FILE* input, char *out);

EXIT_CODE conv_tenth_any (long int num, long int base, char **result);



#endif