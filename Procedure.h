#ifndef PROCEDURES_H
#define PROCEDURES_H


typedef enum {
    OK = 0,
    INVALID,
    FILE_NULL,
    BAD_ALLOC,
} EXIT_CODE;

typedef struct vector_char
{
    int num_of_el;
    char* el;
    int mem_capacity;
} vector_char;



#endif 