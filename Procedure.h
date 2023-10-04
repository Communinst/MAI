
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE
} EXIT_CODE;


void usage ();

EXIT_CODE input_check(int argc, char **argv);

EXIT_CODE file_check(char *argv, FILE** in);

EXIT_CODE extention_check (char *argv);

EXIT_CODE path_handling (char *argv, char **result);

EXIT_CODE flag_handling (char *c, FILE* in, FILE* out);



EXIT_CODE i_func(FILE *in, FILE *out);

EXIT_CODE s_func (FILE *in, FILE *out);

EXIT_CODE a_func (FILE *in, FILE *out);


#endif