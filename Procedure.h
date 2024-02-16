
#ifndef PROCEDURE_H
#define PROCEDURE_H

#define EPS 0.001
typedef unsigned int UI;

typedef enum {
    OK,

    INVALID_ARG,

    BAD_ALLOC

} EXIT_CODE;


typedef struct {
    double* elems;

    int n;

} vector;



#endif