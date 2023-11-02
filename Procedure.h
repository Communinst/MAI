
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{

    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE,
    UNKNOWN_COMMAND,

} EXIT_CODE;



typedef struct
{

    unsigned int id;
    
    char* name;

    char* surname;

    double fee;

} Employee;


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

#include "Procedure.h"




/*---------------------------------Additional-stuff---------------------------------------*/

void usage();


EXIT_CODE valid_lint (char* str, long int* dest);


EXIT_CODE valid_lfloat (char* str, double* dest);


void free_list (int amount, ...);

/*----------------------------------------------------------------------------------------*/




/*-----------------------------------Validation-------------------------------------------*/

EXIT_CODE input_check (int argc, char** argv);

/*----------------------------------------------------------------------------------------*/




/*-----------------------------Main-hub-and-two-roots-below-------------------------------*/

EXIT_CODE result_handling (int argc, char** argv, char flag);

/*----------------------------------------------------------------------------------------*/




/*---------------------------Dump-process-handling-root-----------------------------------*/

EXIT_CODE get_base (int argc, char** argv, Employee*** main_base, int* size);


EXIT_CODE get_node (Employee** main_node, int* current_pos, FILE* in);


EXIT_CODE get_str (FILE* in, int* current_pos, char** dest);


/*---------------------------------Sort-subroot-------------------------------------------*/

EXIT_CODE sort_base (Employee** data_base, int size, char flag);


int ascend_comp (const void* v1, const void* v2);


int descend_comp (const void* v1, const void* v2);

/*----------------------------------------------------------------------------------------*/



/*---------------------------------Drop-process-handling----------------------------------*/

EXIT_CODE write_down_data (Employee*** data_base, int size, char* out_name);

/*----------------------------------------------------------------------------------------*/




#endif