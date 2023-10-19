
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    INAPPROPRIATE,
} EXIT_CODE;


void warning ();


void usage ();


EXIT_CODE double_check (char *argv, double *value);

EXIT_CODE input_control (char *str_EPS);

EXIT_CODE a_right_rectangle (int a, int b, double EPS, double *result);

EXIT_CODE b_right_rectangle (int a, int b, double EPS, double *result);

EXIT_CODE c_left_rectangle (int a, int b, double EPS, double *result);

EXIT_CODE d_right_rectangle (int a, int b, double EPS, double *result);

#endif