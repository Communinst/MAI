#ifndef PROCEDURES_H
#define PROCEDURES_H


typedef long long int ll;


typedef enum
{

    OK = 0,

    INVALID_ARGC,

    INVALID_WORD,

    BAD_ALLOC,

    UNEXPECTED_ZERO,

    MULTIPLE,

    NOT_MULTIPLE,

    TRIANGLE, 

    NOT_TRIANGLE,

} EXIT_CODE;




typedef enum
{

    SINGLE,

    DUAL,

    NONE

} solution_type;




typedef struct
{

    size_t allocated;
    size_t occupied;

    double *elems;

} vector_double;



void response (EXIT_CODE res);


void usage();



EXIT_CODE input_handle (int argc, char **argv);



EXIT_CODE key_handle (int argc, char **argv);



EXIT_CODE str_to_lint (char *str, ll *dest);


EXIT_CODE str_to_double (char *str, double *dest);




EXIT_CODE q_handle (int argc, char **argv);


EXIT_CODE q_input_conversion (char **argv);


EXIT_CODE permutations_of_three (double EPS, double coef1, double coef2, double coef3);


int comp (const void *v1, const void *v2);


EXIT_CODE combination_control (double EPS, double c1, double c2, double c3, int *unique, vector_double *res);


EXIT_CODE coefs_handle (double EPS, int comb_amount, vector_double *coefs);


EXIT_CODE get_comb(int variety, vector_double *coefs, double *v1, double *v2, double *v3, int *it, int *r);


EXIT_CODE all_unique(vector_double *coefs, double *v1, double *v2, double *v3, int *it, int *r);


EXIT_CODE only_unique(vector_double *coefs, double *v1, double *v2, double *v3);


solution_type solve (double EPS, double x1, double x2, double x3, double *sol1, double *sol2);


double get_discriminant (double x1, double x2, double x3);


EXIT_CODE output_handle (solution_type type, double x1, double x2, double x3, double sol1, double sol2);



EXIT_CODE m_handle (int argc, char **argv);


EXIT_CODE is_multiple (ll num1, ll num2);




EXIT_CODE t_handle (int argc, char **argv);


EXIT_CODE t_input_conversion (char **argv);


EXIT_CODE is_triangle (double EPS, double s1, double s2, double s3);






#endif 