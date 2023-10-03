#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"




/*---------------------------------------Basic--------------------------------------------*/

void usage() 
{
    printf("\n\t\t  ./[exe_name] [- or /][key] [arguments]\n");
    printf("\t\t\t\t  Keys:\n");
    printf("\n\t\tq - solves the quadratic equation. Input:\n\t\t\t q EPS coef1 coef2 coef3\n");
    printf("\nm - checks if the first number is a multiple of the second one. Input:\n\t\t\t m value1_int value2_int\n");
    printf("\n   t - checks if there is a triangle with the entered sides. Input:\n\t\t\t t EPS side1 side2 side3\n\n");  
}

void createVector(vectorInt* v)
{
    v->num_of_el = 0;
    v->el = NULL;
    v->mem_capacity = 0;
}

bool ifEmptyVector(vectorInt* v) 
{
    return v->num_of_el; 
}

EXIT_CODE adder(double EPS, double a, double b, double c, vectorInt *v)
{
    if (v->mem_capacity == v->num_of_el)
    {
        v->mem_capacity *= 2;
        result *temp = (result*)realloc(v->el, sizeof(result) * v->mem_capacity);

        if (!temp)
        {
            return BAD_ALLOC;
        }
        
        v->el = temp;
    }
    double discriminant = 0;
    v->el[v->num_of_el].coefs[0] = a;
    v->el[v->num_of_el].coefs[1] = b;
    v->el[v->num_of_el].coefs[2] = c;
    if (countDiscriminant(a, b, c, &discriminant) == LESS) {
        v->el[v->num_of_el].exist = DONT_EXIST;
    }
    else {
        double res1 = 0;
        double res2 = 0;
        equationsSolutions(a, b, discriminant, &res1, &res2);
        //printf("%llf")
        if (fabs(res1 - res2) <= EPS) {
            v->el[v->num_of_el].exist = THE_ONLY_UNIQUE;
            v->el[v->num_of_el].solution1 = res1;
            v->el[v->num_of_el].solution2 = res2;
        }
        else {
            printf("%llf -> %llf\n", res1, res2);
            v->el[v->num_of_el].exist = EXIST;
            v->el[v->num_of_el].solution1 = res1;
            v->el[v->num_of_el].solution2 = res2;
        }
    }
    v->num_of_el++;
    return OK;
}

EXIT_CODE vectorPrint(vectorInt *v) 
{
    int iterator = 0;
    while (iterator != v->num_of_el) 
    {
        if (v->el[iterator].exist == DONT_EXIST) 
        {
            printf("\nThere're not any solutions for the following equation\n");
            printf("\t%llfx^2 + (%llf)x + (%llf)\n", v->el[iterator].coefs[0], v->el[iterator].coefs[1], v->el[iterator].coefs[2]);
        }
        else if (v->el[iterator].exist == THE_ONLY_UNIQUE)
        {
            printf("\nThere's the only solution for the following equation\n");
            printf("\t%llfx^2 + (%llf)x + (%llf)\n", v->el[iterator].coefs[0], v->el[iterator].coefs[1], v->el[iterator].coefs[2]);
            printf("x1 = %llf\n", v->el[iterator].solution1);
        }
        else {
            printf("\nThere're two solutions for the following equation\n");
            printf("\t%llfx^2 + (%llf)x + (%llf)\n", v->el[iterator].coefs[0], v->el[iterator].coefs[1], v->el[iterator].coefs[2]);
            printf("x1 = %llf\tx2 = %llf\n", v->el[iterator].solution1, v->el[iterator].solution2);
        }
        iterator++;
    }
}

void terminate(vectorInt* v) 
{
    v->mem_capacity = 0;
    v->num_of_el = 0;
    v->el = NULL;
    free(v);
}


EXIT_CODE string_valid_pos_double (int argc, char* argv[]) 
{
    int i = 2;
    while (i < argc) 
    {
        if (*argv[2] == '-') {
            return INVALID;
        }
        if (strstr(argv[i], "e")) {
            if (e_notation(argv[i]) != OK) {
                return INVALID;
            }
        }
        else {
            bool point = false;
            
            for (int step = 0; step < strlen(argv[i]); step++) 
            {
                
                if (((argv[i][step] < '0' || argv[i][step] > '9') && argv[i][step] != '.') || ((argv[i][step] == '.') && (point))) 
                {
                    return INVALID;
                }
                
                if (argv[i][step] == '.') 
                {
                    point = true;
                }
            
            }
        }
        i++;
    }
    return OK;
}

EXIT_CODE string_valid_neg_double (int argc, char* argv[])
{
    int i = 2;
    while (i < argc) 
    {   
        if (*argv[2] == '-') {
            return INVALID;
        }
        if (strstr(argv[i], "e")) {
            if (e_notation(argv[i]) != OK) {
                return INVALID;
            }
        }
        else {
            bool point = false;
            int check = 0;
            if (argv[i][0] == '-') {
                check++;
            }
            for (int step = check; step < strlen(argv[i]); step++) 
            {
                if (((argv[i][step] < '0' || argv[i][step] > '9') && argv[i][step] != '.') || ((argv[i][step] == '.') && (point))) 
                {
                    return INVALID;
                }
                
                if (argv[i][step] == '.') 
                {
                    point = true;
                }
            
            }
        }
        i++;
    }
    return OK;
}

EXIT_CODE string_valid_int (int argc, char* argv[]) {
    int i = 2;
    while (i < argc) {
        bool minus = false;
        for (int step = 0; step < strlen(argv[i]); step++) {
            if (((argv[i][step] < '0' || argv[i][step] > '9') && argv[i][step] != '-') || (argv[i][step] == '-' && minus)) {
                return INVALID;
            }
            if (argv[i][step] == '-')
            {
                minus = true;
            }
        }
        i++;
    }
    return OK;
}

EXIT_CODE e_notation (char* argv) {
    int i = 0;
    if (argv[i] < '0' || argv[i] > '9') {
        return INVALID;
    }
    bool e_flag = false;
    bool minus_flag = false;
    while((++i) != strlen(argv)) {
        if (argv[i] == 'e' && !e_flag) {
            e_flag = true;
        }
        else if (argv[i] == '-' && !minus_flag) {
            minus_flag = true;
        }
        else if (argv[i] >= '0' && argv[i] <= '9') {
            continue;
        }
        else {
            return INVALID;
        }
    }
    return OK;
}

EXIT_CODE triangleExistence (double EPS, double side1, double side2, double side3) {
    if ((side1 + side2 - side3 > EPS) && (side1 + side3 - side2 > EPS) && (side2 + side3 - side1 > EPS)) {
        return EXIST;
    }
    return DONT_EXIST;
}

EXIT_CODE equalityOfDoubles (double EPS, double coef1, double coef2, double coef3) {
    if ((fabs(coef1 - coef2) <= EPS) && (fabs(coef1 - coef3) <= EPS) && (fabs(coef2 - coef3) <= EPS)) {
        return THE_ONLY_UNIQUE;
    }
    printf("\n%llf -> %llf\n", coef1, coef2);
    if (fabs(coef1 - coef2) <= EPS) {
        return FIRST_SECOND;
    }
    if (fabs(coef1 - coef3) <= EPS) {
        return FIRST_THIRD;
    }
    if (fabs(coef2 - coef3) <= EPS) {
        return SECOND_THIRD;
    }
    return ALL_UNIQUE;
}


EXIT_CODE combinationControl (double EPS, double coef1, double coef2, double coef3, vectorInt *v) {
    switch (equalityOfDoubles(EPS, coef1, coef2, coef3))
    {
        case ALL_UNIQUE:
            double combination_arr[3] = {coef1, coef2, coef3};
            for (int i = 0; i < 3; i++) {
                if (adder(EPS, combination_arr[i], combination_arr[(i + 1) % 3], combination_arr[(i + 2) % 3], v) != OK) {
                    return BAD_ALLOC;
                }
                if (adder(EPS, combination_arr[i], combination_arr[(i + 2) % 3], combination_arr[(i + 1) % 3], v) != OK) {
                    return BAD_ALLOC;
                }
            }
            return OK;
            break;
        case FIRST_SECOND:
            for (int i = 0; i < 3; i++) {
                if (adder(EPS, combination_arr[i], combination_arr[(i + 1) % 3], combination_arr[(i + 2) % 3], v) != OK) {
                    return BAD_ALLOC;
                }
            }
            return OK;
            break;

        case FIRST_THIRD:
            for (int i = 0; i < 3; i++) {
                if (adder(EPS, combination_arr[i], combination_arr[(i + 1) % 3], combination_arr[(i + 2) % 3], v) != OK) {
                    return BAD_ALLOC;
                }
            }
            return OK;
            break;

        case SECOND_THIRD:
            for (int i = 0; i < 3; i++) {
                if (adder(EPS, combination_arr[i], combination_arr[(i + 1) % 3], combination_arr[(i + 2) % 3], v) != OK) {
                    return BAD_ALLOC;
                }
            }
            return OK;
            break;

        case THE_ONLY_UNIQUE:
            if (adder(EPS, coef1, coef2, coef3, v) != OK) {
                return BAD_ALLOC;
            }
            return OK;
            break;

        default:
            return INVALID;
            break;
        }
}

void equationsSolutions (double a, double b, double dis, double *res1, double *res2) {
    *res1 = ((-1.0) * b * b + sqrt(dis)) / 2.0 / a;
    *res2 = ((-1.0) * b * b - sqrt(dis)) / 2.0 / a;
}

EXIT_CODE countDiscriminant (double a, double b, double c, double *dis) {
    *dis = b * b - 4.0 * a * c;
    return checkDiscriminant(dis);
}

EXIT_CODE checkDiscriminant (double *dis) {
    if (*dis < 0) {
        return LESS;
    }
    return OK;
}

/*---------------------------------------Basis--------------------------------------------*/
EXIT_CODE inputCheck (int argc, char* argv[], vectorInt *solutions) {
    if ((*argv[1] != '/' && *argv[1] != '-') || (strlen(argv[1]) != 2)) {
        return INVALID;
    }
    
    if (argv[1][1] == 'q') {
        return qFunc(argc, argv, solutions);
    }
    if (argv[1][1] == 'm') {
        return mFunc(argc, argv);
    }
    if (argv[1][1] == 't') {
        return tFunc(argc, argv);
    }
    
}

/*-----------------------------------qKeyTreatment----------------------------------------*/
EXIT_CODE qArgcCheck (int argc, char *argv[]) {
    if (argc > 6) {
       return TOO_MANY;
    }
    if (argc < 6) {
       return TOO_FEW;
    }
    if (string_valid_neg_double(argc, argv) != OK){
        return INVALID;
    }
    return OK;
}

EXIT_CODE qFunc (int argc, char* argv[], vectorInt *solutions) 
{

    if (qArgcCheck(argc, argv) != OK) 
    {
        return (qArgcCheck(argc, argv));
    }
    double EPS = strtod(argv[2], NULL);
    double coef1 = strtod(argv[3], NULL);
    double coef2 = strtod(argv[4], NULL);
    double coef3 = strtod(argv[5], NULL);


    return combinationControl(EPS, coef1, coef2, coef3, solutions);
    
}

/*-----------------------------------mKeyTreatment----------------------------------------*/
EXIT_CODE mArgcCheck (int argc, char *argv[]) {
    if (argc > 4) {
       return TOO_MANY;
    }
    if (argc < 4) {
       return TOO_FEW;
    }
    if (string_valid_int(argc, argv) != OK){
        return INVALID;
    }
    return OK;
}

EXIT_CODE mFunc (int argc, char* argv[]) {
    if (mArgcCheck(argc, argv) != OK) {
        return mArgcCheck(argc, argv);
    }
    long int num1 = strtol(argv[2], NULL, 10);
    long int num2 = strtol(argv[3], NULL, 10);
    if (num1 % num2) {
        return NON_DIVISIBLE;
    }
    return DIVISIBLE;
}

/*-----------------------------------pKeyTreatment----------------------------------------*/

EXIT_CODE tArgcCheck (int argc, char *argv[]) {
    if (argc > 6) {
       return TOO_MANY;
    }
    if (argc < 6) {
       return TOO_FEW;
    }
    if (string_valid_pos_double(argc, argv) != OK){
        return INVALID;
    }
    return OK;
}

EXIT_CODE tFunc (int argc, char* argv[]) {
    if (tArgcCheck(argc, argv) != OK) {
        return (tArgcCheck(argc, argv));
    }
    double EPS = strtod(argv[2], NULL);
    double side1 = strtod(argv[3], NULL);
    double side2 = strtod(argv[4], NULL);
    double side3 = strtod(argv[5], NULL);
    return triangleExistence(EPS, side1, side2, side3);   
}

/*----------------------------------------------------------------------------------------*/

EXIT_CODE main (int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        return TOO_FEW;
    }
    vectorInt solutions;
    createVector(&solutions);

    switch (inputCheck(argc, argv, &solutions)) {
        case TOO_MANY:
            printf("Enter the less amount of arguments, please!");
            break;
        case TOO_FEW:
            printf("Enter more amount of arguments, please!");
            break;
        case INVALID:
            printf("You violated the input rules!");
            usage();
            break;
        case DIVISIBLE:
            printf("The first entered value divisible by the second one!\n");
            break;
        case NON_DIVISIBLE:
            printf("It seems, the first entered value is NOT divisible by the second one!\n");
            break;
        case EXIST:
            printf("These sides triangle can exist!\n");
            break;
        case DONT_EXIST:
            printf("It seems, these sides triangle can NOT exist!\n");
            break;
        case BAD_ALLOC:
            printf("Memory handling error!1!");
            break;
        case OK:

            printf("\n%d\n", solutions.num_of_el);
            if (ifEmptyVector(&solutions)) {
                vectorPrint(&solutions);
            }
            break;
    }
    terminate(&solutions);
    
}