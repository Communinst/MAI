
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {

    OK = 0,
    BAD_ALLOC,

} EXIT_CODE;


/*-----------------------------------To-free-every-char*----------------------------------*/
EXIT_CODE free_list (int amount, ...);

/*----------------------------------------------------------------------------------------*/


/*--------------------------------------Ten-to's-hub--------------------------------------*/
EXIT_CODE ten_to_grades_of_2 (long long int tenth, char** two, char** four, char** eight, char** sixteen, char** thirty_two);

/*----------------------------------------------------------------------------------------*/


/*-------------------------------Ten-to-any-2^r-(r-in-[1-5])------------------------------*/
EXIT_CODE ten_two (long long int tenth, char** two);


EXIT_CODE ten_four (long long int tenth, char** four);


EXIT_CODE ten_eight (long long int tenth, char** four);


EXIT_CODE ten_sixteen (long long int tenth, char** four);


EXIT_CODE ten_thirty_two (long long int tenth, char** four);

/*----------------------------------------------------------------------------------------*/


/*------------------------------'+'-by-means-of-bits--------------------------------------*/
int sum_up_by_bits (int residue, int ascii);

/*----------------------------------------------------------------------------------------*/


#endif