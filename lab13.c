#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "Procedure.h"



int main ()//int argc, char **argv)
{

    int argc = 6;

    char *data[] = {"gay", "-q", "0.1", "7", "4", "3"};

    char **argv = data;

    response(input_handle(argc, argv));

    return 0;

}




EXIT_CODE vector_init (vector_double **dest)
{

    vector_double *buff = (vector_double*)malloc(sizeof(vector_double));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->allocated = 0;
    buff->occupied = 0;
    buff->elems = NULL;

    *dest = buff;

    return OK;

}


EXIT_CODE vector_append (vector_double *dest, double to_add)
{

    if (dest->allocated == dest->occupied)
    {

        dest->allocated += 1;
        dest->allocated *= 2;

        double *temp = (double*)realloc(dest->elems, sizeof(double) * dest->allocated);

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->elems = temp;

    }

    *(dest->elems + dest->occupied) = to_add;

    (dest->occupied)++;

    return OK;

}


EXIT_CODE vector_destr (vector_double **dest)
{

    (*dest)->allocated = 0;
    (*dest)->occupied = 0;

    free((*dest)->elems);
    (*dest)->elems = NULL;

    free((*dest));
    (*dest) = NULL;

    return OK;

}




void response (EXIT_CODE res)
{

    switch (res)
    {

        case OK:
            printf("Success!\n");
            break;
        
        case INVALID_ARGC:
            printf("Invalid amount of arguments!\n");
            usage();
            break;

        case INVALID_WORD:
            printf("Unexpected lexeme!\n");
            usage();
            break;

        case BAD_ALLOC:
            printf("Memory fault!\n");
            break;
            
        case UNEXPECTED_ZERO:
            printf("Zero's invalid in current request!\n");
            break;

        case MULTIPLE:
            printf("First value is a multiple of the second one!\n");
            break;

        case NOT_MULTIPLE:
            printf("First value isn't a multiple of the second one!\n");
            break;

        case TRIANGLE:
            printf("That sided triangle does exist!\n");
            break;
            
        case NOT_TRIANGLE:
            printf("That sided triangle doesn't exist!\n");
            break;

        default:
            break;
    }

}


void usage() 
{
    printf("\n\t\t  ./[exe_name] [- or /][key] [arguments]\n");
    printf("\t\t\t\t  Keys:\n");
    printf("\n\t\tq - solves the quadratic equation. Input:\n\t\t\t q EPS coef1 coef2 coef3\n");
    printf("\nm - checks if the first number is a multiple of the second one. Input:\n\t\t\t m value1_int value2_int\n");
    printf("\n   t - checks if there is a triangle with the entered sides. Input:\n\t\t\t t EPS side1 side2 side3\n\n");  
}



EXIT_CODE input_handle (int argc, char **argv)
{

    if (argc < 2)
    {
        return INVALID_ARGC;
    }

    return key_handle(argc, argv);  

}



EXIT_CODE key_handle (int argc, char **argv)
{

    char *ch = *(argv + 1);

    if ((*ch != '-' && *ch != '/') || strlen(*(argv + 1)) != 2)
    {
        return INVALID_WORD;
    }

    ch++;

    switch (*ch)
    {
        case 'q':
            return q_handle(argc - 2, (argv + 2));

        case 'm':
            return m_handle(argc - 2, (argv + 2));

        case 't':
            return t_handle(argc - 2, (argv + 2));
        
        default:
            return INVALID_WORD;
    }

}



EXIT_CODE str_to_lint (char *str, ll *dest)
{

    char *end_ptr;

    *dest = strtol(str, &end_ptr, 10);

    return (end_ptr == str + strlen(str)) ? OK : INVALID_WORD;

}


EXIT_CODE str_to_double (char *str, double *dest)
{

    errno = 0;

    char *end_ptr;

    *dest = strtod(str, &end_ptr);

    return (end_ptr == str + strlen(str) && !errno) ? OK : INVALID_WORD;

}



EXIT_CODE q_handle (int argc, char **argv)
{

    EXIT_CODE sup = OK;

    sup = (argc != 4) ? INVALID_ARGC : sup;

    return sup ? sup : q_input_conversion(argv);

}


EXIT_CODE q_input_conversion (char **argv)
{

    double EPS = 0;
    double coef1 = 0;
    double coef2 = 0;
    double coef3 = 0;

    EXIT_CODE sup = OK;

    sup = str_to_double(*(argv), &EPS);
    sup = sup ? sup : str_to_double(*(argv + 1), &coef1);
    sup = sup ? sup : str_to_double(*(argv + 2), &coef2);
    sup = sup ? sup : str_to_double(*(argv + 3), &coef3);

    return sup ? sup : permutations_of_three(EPS, coef1, coef2, coef3);

}


EXIT_CODE permutations_of_three (double EPS, double coef1, double coef2, double coef3)
{

    vector_double *coefs = NULL;
    vector_init(&coefs);

    double src_coefs[3] = {coef1, coef2, coef3};

    qsort(src_coefs, 3, sizeof(double), comp);

    int unique = 0;

    combination_control(EPS, coef1, coef2, coef3, &unique, coefs);

    discriminant_handle(EPS, unique, coefs);

    vector_destr(&coefs);

    return OK;

}


int comp (const void *v1, const void *v2)
{

    double *d1 = (double*)v1;
    double *d2 = (double*)v2;

    return (*d1 <= *d2) ? -1 : 1;

}


EXIT_CODE combination_control (double EPS, double c1, double c2, double c3, int *unique, vector_double *res)
{

    if (fabs(c1 - c2) < EPS)
    {
        *unique = 2;
        vector_append(res, c2);
        vector_append(res, c2);
    }

    if (fabs(c2 - c3) < EPS)
    {
        if (*unique == 2)
        {
            *unique = 1;
        }
        else
        {
            vector_append(res, c2);
            vector_append(res, c2);
            vector_append(res, c1);
        }
    }

    else if (res->occupied)
    {
        vector_append(res, c3);
        vector_append(res, c2);
    }

    else
    {
        *unique = 3;

        vector_append(res, c1);

        vector_append(res, c2);

        vector_append(res, c3);
    }



}


EXIT_CODE discriminant_handle (double EPS, int comb_amount, vector_double *coefs)
{

    int t_amount = 0;

    t_amount = t_amount | comb_amount;

    if (comb_amount > 1)
    {
        t_amount | 1;
    }

    printf("moron");

    if (comb_amount > 2)
    {
        t_amount << 1;
    }

    int iterator = 0;
    int reverse = 0;

    while (t_amount--)
    {

        double x1, x2, x3;

        get_comb(comb_amount, coefs, &x1, &x2, &x3, &iterator, &reverse);

        printf("%llf %llf %llf\n", x1, x2, x3);

    }

}


EXIT_CODE get_comb(int variety, vector_double *coefs, double *v1, double *v2, double *v3, int *it, int *r)
{

    switch (variety)
    {
        case 1:
            only_unique(coefs, v1, v2, v3);
            break;

        default:
            all_unique(coefs, v1, v2, v3, it, r);
            break;
    }

}


EXIT_CODE all_unique(vector_double *coefs, double *v1, double *v2, double *v3, int *it, int *r)
{

    if (!(*r))
    {
        *v1 = coefs->elems[*it];
        *v2 = coefs->elems[(*it + 1) % 3];
        *v3 = coefs->elems[(*it + 2) % 3];
    }

    else if (*r)
    {

        *v1 = coefs->elems[*it % 3];
        *v2 = coefs->elems[(*it - 1) % 3];
        *v3 = coefs->elems[(*it - 2) % 3];

    }

    *r = (*it == 2) ? 1 : 0;

    *it++;

    return OK;

}


EXIT_CODE only_unique(vector_double *coefs, double *v1, double *v2, double *v3)
{

    *v1 = *(coefs->elems);
    *v2 = *(coefs->elems);
    *v3 = *(coefs->elems);

}



EXIT_CODE m_handle (int argc, char **argv)
{

    EXIT_CODE sup = OK;

    sup = (argc != 2) ? INVALID_ARGC : sup;

    ll num1 = 0;
    ll num2 = 0;

    sup = sup ? sup : str_to_lint(*(argv), &num1);
    sup = sup ? sup : str_to_lint(*(argv + 1), &num2);
    
    return sup ? sup : is_multiple(num1, num2); 

}


EXIT_CODE is_multiple (ll num1, ll num2)
{

    if (num1 % num2)
    {   
        return NOT_MULTIPLE;
    }
    return MULTIPLE;

}




EXIT_CODE t_handle (int argc, char **argv)
{

    EXIT_CODE sup = OK;

    sup = (argc != 4) ? INVALID_ARGC : sup;

    return sup ? sup : t_input_conversion(argv);

}


EXIT_CODE t_input_conversion (char **argv)
{

    double EPS = 0;
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;

    EXIT_CODE sup = OK;

    sup = str_to_double(*(argv), &EPS);
    sup = sup ? sup : str_to_double(*(argv + 1), &side1);
    sup = sup ? sup : str_to_double(*(argv + 2), &side2);
    sup = sup ? sup : str_to_double(*(argv + 3), &side3);

    sup = (EPS < 0 || side1 < 0 || side2 < 0 || side3 < 0) ? INVALID_WORD : sup;

    return sup ? sup : is_triangle(EPS, side1, side2, side3);

}


EXIT_CODE is_triangle (double EPS, double s1, double s2, double s3)
{


    if (s1 - s2 - s3 > EPS)
    {
        return NOT_TRIANGLE;
    }

    if (s2 - s1 - s3 > EPS)
    {
        return NOT_TRIANGLE;
    }

    if (s3 - s1 - s2 > EPS)
    {
        return NOT_TRIANGLE;
    }

    return TRIANGLE;


}


