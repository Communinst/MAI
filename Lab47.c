
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "Procedure.h"



int main (int argc, char** argv)
{

    switch(input_handle(argc, argv))
    {

        case OK:

            printf("SUCCESS!\n");
            break;

        default:
            printf("IDIOT!\n");

    }

    return 0;

}


EXIT_CODE cell_constr (memory_cell** dest, char* name, ll value)
{

    memory_cell* buff = (memory_cell*)malloc(sizeof(memory_cell));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));

    if (!(buff->name))
    {

        free(buff);
        
        return BAD_ALLOC;
    
    }

    buff->value = value;

    strcpy(buff->name, name);

    *dest = buff;

    return OK;

}


EXIT_CODE cell_destr (memory_cell** dest)
{

    free((*dest)->name);
    (*dest)->name = NULL;

    (*dest)->value = 0;

    free(*dest);
    (*dest) == NULL;

    return OK;

}



EXIT_CODE vec_init (memory_vec** dest)
{

    (*dest)->occupied = 0;

    (*dest)->allocated = 0;
    
    (*dest)->cells = NULL;

    return OK;

}


EXIT_CODE vec_append (memory_vec* dest, memory_cell* to_add)
{

    if (dest->occupied == dest->allocated)
    {

        dest->allocated += 1;
        dest->allocated *= 2;       

        memory_cell** temp = (memory_cell**)realloc(dest->cells, sizeof(memory_cell*) * (dest->allocated));

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->cells = temp;

    }

    *((dest->cells) + dest->occupied) = to_add;

    dest->occupied++;

    return OK;

}


EXIT_CODE vec_display (memory_vec* src)
{

    memory_cell** crawler = src->cells;

    for (int i = 0; i < src->occupied; i++)
    {

        printf("%s = %lld\n", (*crawler)->name, (*crawler)->value);

        crawler++;

    }

    return OK;

}


EXIT_CODE vec_destr (memory_vec** dest)
{

    memory_cell** crawler = (*dest)->cells;

    while (((*dest)->occupied)--)
    {

        cell_destr(*crawler);

        crawler++;

    }

    (*dest)->allocated = 0;

}



EXIT_CODE input_handle (int argc, char** argv)
{

    if (argc != 2)
    {
        return INVALID;
    }

    data_handle(*(argv + 1));

}


EXIT_CODE data_handle (char* filename)
{

    FILE* in = NULL;

    EXIT_CODE assist = file_handle(filename, &in);

    if (assist)
    {
        return assist;
    }

    assist = data_handle(in);

    fclose(in);

    return assist;

}


EXIT_CODE file_handle (char* src, FILE** dest)
{

    FILE* buff = fopen(src, "r");

    if (!buff)
    {
        return NO_FILE;
    }

    *dest = buff;

    return OK;

}


EXIT_CODE memory_hub (FILE* src)
{

    memory_vec* memory = NULL;

    vec_init(&memory);


    fill_vec(memory, src);


    vec_destr(&memory);

}


EXIT_CODE fill_vec (memory_vec* dest, FILE* src)
{

    char c = 1;

    while (c > 0)
    {

        memory_cell* unit = NULL;

        get_cell(&unit, src, &c);

        vec_append(dest, unit);

    }



}


EXIT_CODE get_cell(memory_cell** dest, FILE* src, char *c)
{

    char* name;

    get_variable(&name, src, &c);

    OPERATION op = operation_handle(c);

    if (op == NEXT)
    {
        handle_print();
    }

    if (!op)
    {

        ll value = 0;

        complete_inst(src, c, &value);

    }

}


EXIT_CODE get_variable (char** dest, FILE* src, char* c)
{

    char* buff = (char*)malloc(sizeof(char));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    char* crawler = buff;

    *crawler = '\0';

    int amount = 0;

    while (isalpha(*c = fgetc(src)) || isdigit(*c))
    {

        if (amount == strlen(buff))
        {

            char* temp = (char*)realloc(buff, sizeof(char) * (amount++) * 2);

            if (!temp)
            {
                return BAD_ALLOC;
            }

            buff = temp;

        }

        *crawler = *c;

        crawler++;

        *crawler = '\0';

    }

    *dest = buff;

    return OK;

}


OPERATION operation_handle (char c)
{

    if (c < 0 || c == '\n')
    {
        return NEXT;
    }
    switch(c)
    {

        case '=':
            return ASSIGN;
        
        case '+':
            return PLUS;

        case '-':
            return MINUS;

        case '\\':
            return DIVISION;

        case '*':
            return MULTIPLICITY;

        case '%':
            return MODULUS;

        default:
            printf("UNKNOWN SYMBOL!\n");
            return NEXT;

    }
    


}


EXIT_CODE complete_instr (FILE* src, char* c, ll* value)
{

    char* data;

    while (*c != '\n' && *c > 0)
    {

        get_variable(&data, src, c);

        OPERATION op = operation_handle(*c);

        

    }

}
