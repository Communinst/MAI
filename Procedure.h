#ifndef PROCEDURES_H
#define PROCEDURES_H


typedef enum {
    OK = 1,
    INVALID,
    TOO_MANY,
    TOO_FEW,
    DIVISIBLE,
    NON_DIVISIBLE,
    EXIST,
    DONT_EXIST,
    THE_ONLY_UNIQUE,
    FIRST_SECOND,
    FIRST_THIRD,
    SECOND_THIRD,
    ALL_UNIQUE,
    BAD_ALLOC,
    LESS,
} EXIT_CODE;


typedef struct 
{
    double solution1;
    double solution2;
    EXIT_CODE exist;
    double coefs[3];
} result;


typedef struct vectorInt
{
    int num_of_el;
    result* el;
    int mem_capacity;
} vectorInt;


void usage();

void createVector(vectorInt* v);

bool ifEmptyVector(vectorInt* v);

EXIT_CODE adder(double EPS, double a, double b, double c, vectorInt *v);

EXIT_CODE vectorPrint(vectorInt *v);

void terminate(vectorInt* v);


EXIT_CODE stringValidDouble(int argc, char* argv[]);

EXIT_CODE stringValidInt (int argc, char* argv[]);

EXIT_CODE triangleExistence(double EPS, double side1, double side2, double side3);

EXIT_CODE equalityOfDoubles(double EPS, double coef1, double coef2, double coef3);


EXIT_CODE combinationControl(double EPS, double coef1, double coef2, double coef3, vectorInt *v);

void equationsSolutions(double a, double b, double dis, double *res1, double *res2);

EXIT_CODE countDiscriminant(double a, double b, double c, double *dis);

EXIT_CODE checkDiscriminant(double *dis);

/*---------------------------------------Basis--------------------------------------------*/
EXIT_CODE inputCheck(int argc, char* argv[], vectorInt *solutions);

/*-----------------------------------qKeyTreatment----------------------------------------*/
EXIT_CODE qtArgcCheck(int argc, char *argv[]);

EXIT_CODE qFunc(int argc, char* argv[], vectorInt *solutions);

/*-----------------------------------mKeyTreatment----------------------------------------*/
EXIT_CODE mArgcCheck(int argc, char *argv[]);

EXIT_CODE mFunc(int argc, char* argv[]);

/*-----------------------------------pKeyTreatment----------------------------------------*/
EXIT_CODE tFunc(int argc, char* argv[]);


#endif 
