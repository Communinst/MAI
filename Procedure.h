
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
} EXIT_CODE;


void usage ();

EXIT_CODE double_check (char *argv, double *value);

EXIT_CODE input_check (int argc, char **argv);


EXIT_CODE a_func (double EPS, double x, double *result);

EXIT_CODE b_func (double EPS, double x, double *result);

EXIT_CODE c_func (double EPS, double x, double *result);

EXIT_CODE d_func (double EPS, double x, double *result);


#endif