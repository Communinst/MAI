
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>

#include "Procedure.h"


/*----------------------------------------MAIN--------------------------------------------*/

int main (int argc, char** argv) 
{

    switch (input_check(argc, argv))
    {
        case OK:
            printf("\nSUCCESS!\n");
            break;
        
        case INVALID:
            printf("\nInvalid input!\nStick to the following instructions:\n");
            usage();
            break;

        case NO_FILE:
            printf("\nMake sure entered files exist\n");
            break;

        default:
            break;
    }
    
    return 0;
}

/*----------------------------------------------------------------------------------------*/




/*---------------------------------Additional-stuff---------------------------------------*/

void usage()
{
    printf("|--------------------------------------------------------------|");
    printf("|\n|./[exe_name] input_filename [- or /][flag] output_filename.|\n");
    printf("|                                                              |");
    printf("|\n|List of allowed flags:                                     |\n");
    printf("|\n|a - sort the data_base by ascending;                       |\n");
    printf("|\n|d - sort the data_base by descending;                      |\n|\n|");
    printf("---------------------------------------------------------------");

}

EXIT_CODE valid_lint (char* str, long int* dest)
{

    char* end_ptr;

    *dest = strtol(str, &end_ptr, 10);

    return (end_ptr == str + strlen(str)) ? OK : INVALID;

}


EXIT_CODE valid_lfloat (char* str, double* dest)
{

    char* end_ptr;

    *dest = strtod(str, &end_ptr);

    return (end_ptr == str + strlen(str)) ? OK : INVALID;

}


void free_list (int amount, ...)
{

    va_list dynamics;
    va_start(dynamics, amount);

    for (int i = 0; i < amount; i++)
    {

        void* temp = va_arg(dynamics, void*);
        free(temp);

    }

    va_end(dynamics);

}

/*----------------------------------------------------------------------------------------*/




/*-----------------------------------Validation-------------------------------------------*/

EXIT_CODE input_check (int argc, char** argv)
{

    if (argc != 4)
    {
        return INVALID;
    }

    char* crawler = argv[2];

    if ((*crawler != '-' && *crawler != '/') || strlen(argv[2]) != 2)
    {
        return INVALID;
    }

    crawler++;

    return result_handling (argc, argv, *crawler);

}

/*----------------------------------------------------------------------------------------*/




/*-----------------------------Main-hub-and-two-roots-below-------------------------------*/

EXIT_CODE result_handling (int argc, char** argv, char flag)
{

    Employee** data_base;
    int size = 0;

    if (get_base (argc, argv, &data_base, &size) != OK)
    {
        return INVALID;
    }

    sort_base (data_base, size, flag);

    return write_down_data (&data_base, size, argv[3]);

}

/*----------------------------------------------------------------------------------------*/




/*---------------------------Dump-process-handling-root-----------------------------------*/

EXIT_CODE get_base (int argc, char** argv, Employee*** main_base, int* size)
{

    FILE* in = fopen(argv[1], "r");

    if (!in)
    {
        return BAD_ALLOC;
    }

    Employee** data_base = (Employee**)malloc(sizeof(Employee*) * 0);
    int current_allocated = 0;

    int c = fgetc(in);
    int current_contained = 0;

    do
    {

        Employee* temp_node = (Employee*)malloc(sizeof(Employee) * 1);

        if (get_node(&temp_node, &c, in) != OK)
        {
            return INVALID;
        }

        if (current_contained == current_allocated)
        {

            Employee** temp_base = (Employee**)realloc(data_base, sizeof(Employee*) * ((current_contained + 1) * 2));
            
            if(!temp_base)
            {
                return BAD_ALLOC;
            }

            current_allocated = ((current_contained + 1) * 2);

            data_base = temp_base;

        }

        data_base[current_contained++] = temp_node;

    } while (c > 0);
    
    *main_base = data_base;
    *size = current_contained;

    fclose(in);

    return OK;

}


EXIT_CODE get_node (Employee** main_node, int* current_pos, FILE* in)
{

    Employee* temp_node = (Employee*)malloc(sizeof(Employee) * 1);

    if (!temp_node)
    {
        return BAD_ALLOC;
    }

    char* temp;
    int num = 0;
    long int id;
    double fee;


    do
    {

        if (get_str(in, current_pos, &temp) != OK)
        {
            return INVALID;
        }

        switch (num)
        {
            
            case 0:

                if (valid_lint(temp, &id) != OK)
                {
                    return INVALID;
                }

                temp_node->id = id;
                break;


            case 1:
            
                temp_node->name = (char*)malloc(sizeof(char) * strlen(temp) + 1);

                if (!temp_node->name)
                {
                    return BAD_ALLOC;
                } 

                strcpy(temp_node->name, temp);

                temp_node->name[strlen(temp)] = '\0';   

                break;


            case 2:

                temp_node->surname = (char*)malloc(sizeof(char) * strlen(temp) + 1);

                if (!temp_node->surname)
                {
                    return BAD_ALLOC;
                }                             

                strcpy(temp_node->surname, temp);

                temp_node->surname[strlen(temp)] = '\0'; 

                break;


            case 3:

                if (valid_lfloat(temp, &fee) != OK)
                {
                    return INVALID;
                }

                temp_node->fee = fee;
                break;
            

            default:
                return INVALID;

        }

        free(temp);

    } while (++num != 4);

    if (*current_pos != '\n' && *current_pos > 0)
    {
        return INVALID;
    }

    *main_node = temp_node;

    return OK;

}


EXIT_CODE get_str (FILE* in, int* current_pos, char** dest)
{

    char* temp = (char*)malloc(sizeof(char) * 1);

    if (!temp)
    {
        return BAD_ALLOC;
    }

    temp[0] = '\0';

    int amount = 0;

    while (isspace(*current_pos))
    {
        *current_pos = fgetc(in);
    }

    do
    {

        if (*current_pos < 0)
        {
            return OK;
        }

        if (amount == strlen(temp))
        {

            char* buff = (char*)realloc(temp, sizeof(char) * ((amount + 1) * 2));

            if (!buff)
            {
                return BAD_ALLOC;
            }

            temp = buff;

        }

        temp[amount] = *current_pos;

        temp[++amount] = '\0';
        
    } while (!(isspace(*current_pos = fgetc(in))));
    
    *dest = temp;

    return OK;

}


/*---------------------------------Sort-subroot-------------------------------------------*/

EXIT_CODE sort_base (Employee** data_base, int size, char flag)
{

    switch (flag)
    {
        case 'a':
            qsort(data_base, size, sizeof(Employee*), ascend_comp);
            break;
        
        case 'd':
            qsort(data_base, size, sizeof(Employee*), descend_comp);
            break;

        default:
            return UNKNOWN_COMMAND;
    }
    
    return OK;

}


int ascend_comp (const void* v1, const void* v2)
{

    Employee* e1 = (Employee*) v1;
    Employee* e2 = (Employee*) v2;

    if (e1->fee != e2->fee)
    {
        return e1->fee - e2->fee;
    }

    else if (strcmp(e1->surname, e2->surname))
    {
        return strcmp(e1->surname, e2->surname);
    }

    else if (strcmp(e1->name, e2->name))
    {
        return strcmp(e1->name,e2->name);
    }
    else 
    {
        return e1->id - e2->id;
    }

    free(e1);
    free(e2);

}


int descend_comp (const void* v1, const void* v2)
{
    ascend_comp(v2, v1);
}

/*----------------------------------------------------------------------------------------*/



/*---------------------------------Drop-process-handling----------------------------------*/

EXIT_CODE write_down_data (Employee*** data_base, int size, char* out_name)
{

    FILE* output = fopen(out_name, "wb");

    if (!output)
    {
        return NO_FILE;
    }

    fprintf(output, "Data:\n");

    for (int i = 0; i < size; i++)
    {

        fprintf(output, "%u: %s %s %.5llf\n", (*data_base)[i]->id, (*data_base)[i]->name, (*data_base)[i]->surname, (*data_base)[i]->fee);

        free_list(3, (*data_base)[i]->name, (*data_base)[i]->surname, (*data_base)[i]);

    }

    free(*data_base);

    return OK;

}

/*----------------------------------------------------------------------------------------*/




