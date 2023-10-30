
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {

    OK = 0,
    BAD_ALLOC,

} EXIT_CODE;


/*-------------------------------Ten-to-any-2^r-(r-in-[1-5])------------------------------*/
EXIT_CODE ten_to_n (long long int tenth, char** result, int pow_of_two);

/*----------------------------------------------------------------------------------------*/


/*------------------------------'+'-by-means-of-bits--------------------------------------*/
int sum_up_by_bits (int residue, int ascii);

/*----------------------------------------------------------------------------------------*/


#endif