
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{

    YES = 0,
    NO,
    INVALID,
    
} EXIT_CODE;



int is_convex_poly(int amount, ...);

EXIT_CODE res_in_point (double* res, double root, int level, ...);


#endif