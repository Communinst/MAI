
#ifndef PROCEDURE_H
#define PROCEDURE_H


typedef long long int ll;


typedef enum
{

    OK = 0,

    INVALID,

    NO_FILE,

    BAD_ALLOC,

} EXIT_CODE;


typedef enum
{

    ASSIGN = 0,

    PLUS,

    MINUS,

    MULTIPLICITY,

    DIVISION,

    MODULUS,

    NEXT,


} OPERATION;




typedef struct
{

    char* name;

    ll value;

} memory_cell;




typedef struct
{

    ll occupied;

    ll allocated;

    memory_cell** cells;

} memory_vec;




#endif