#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"




void createVector(vector_char* v)
{
    v->num_of_el = 1;
    v->el = NULL;
    v->mem_capacity = 1;
}

bool ifEmptyVector(vector_char* v) 
{
    return v->num_of_el; 
}

EXIT_CODE adder_char(char new_value, vector_char *v)
{
    if (v->mem_capacity == v->num_of_el)
    {
        v->mem_capacity *= 2;
        char *temp = (char*)realloc(v->el, sizeof(char) * v->mem_capacity);

        if (!temp)
        {
            return BAD_ALLOC;
        }
        
        v->el = temp;
    }
    v->num_of_el++;
    v->el[v->num_of_el] = new_value;
    v->el[v->num_of_el + 1] = '\0';

    
}

EXIT_CODE vector_print(vector_char *v) {
    
}

void terminate(vector_char* v) {
    v->mem_capacity = 0;
    v->num_of_el = 0;
    v->el = NULL;
    free(v);
}




EXIT_CODE file_handling(FILE *f, va_list symbol, bool acquired, char **argv) {
    FILE *output;
    if (acquired) {
        output = fopen(argv[3], "w");
    }
    

}
EXIT_CODE path_check(char *s) {
    if (syntacsis_check(s) == OK) {
        
    }
    return syntacsis_check(s)
}


EXIT_CODE syntacsis_check(char *s) {
    char* extention = (char*)malloc(sizeof(char) * 1);
    for (int i = strlen(s) - 1; i >= 0; i++) {
        if (s[i] == '.') {
            break;
        }
        if (adder(s[i], extention) == BAD_ALLOC) {
            return BAD_ALLOC;
        }
    }
    if (strcmp(extention, "txt")) {
        return INVALID;
    }
    return OK;

}

/*---------------------------------------Basic--------------------------------------------*/

EXIT_CODE input_check(int argc, char **argv) 
{   
    //if
    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        return FILE_NULL;
    }
    if(argc < 3)
        return INVALID;
    char *f = argv[1];
    if (*f != '-' || *f != '/') {
        return INVALID;
    }
    f++;
    bool acquired = false;
    if (*f == 'n') {
        f++;
        acquired = true;
    }
    if(argc != (3 + acquired)) {
        return INVALID;
    }
    fileHandling(input, f, acquired, argv);
}

/*----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]) {
    

}