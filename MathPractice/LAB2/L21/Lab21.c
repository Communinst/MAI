
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include "Procedure.h"


void warning ()
{

    printf("");

}

void usage () 
{
    printf("./[exe_name] ['-' or '/'][key] [args]\n\n");
    printf("                                              Key list:\n");
    printf("                         l - returns amount of elements in string. Args:\n\tstring\n\n");
    printf("                                r - returns reversedstring. Args:\n\tstring\n\n");
    printf("                u - returns refister-changed copy of the entered string. Args:\n\tstring\n\n");
    printf("              n - returns sorted by digits, alphas and sybs string's copy. Args:\n\tstring\n\n");
    printf("c - returns an randomly concatenated string containing every entered string. Args:\n\tuns_int_seed [strings]\n\n");
}



EXIT_CODE input_check (int argc, char** argv)
{

    if (argc < 3) 
    {
        return INVALID;
    }

    char* crawler = argv[1];

    if (*crawler != '-' && *crawler != '/')
    {
        return INVALID;
    }

    crawler++;

    return flag_handling(*crawler, argc, argv);

}


EXIT_CODE flag_handling (char flag, int argc, char** argv)
{


    switch (flag)
    {
        case 'l':
            return l_flag(argc, argv[2]);
        
        case 'r':
            return r_flag(argc, argv[2]);

        case 'u':
            return u_flag(argc, argv[2]);

        case 'n':
            return n_flag(argc, argv[2]);

        case 'c':
            return c_flag(argc, argv);

        default:
            break;
    }


}



EXIT_CODE l_flag (int argc, char* argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    printf("%lld", string_length(argv));

    return OK;

}

size_t string_length (char* str)
{

    char* crawler = str;

    while (*crawler != '\0')
    {
        crawler++;
    }

    return (crawler - str);

}



EXIT_CODE r_flag (int argc, char* argv) 
{

    if (argc != 3)
    {
        return INVALID;
    }

    char* str_rev = string_reverse(argv);

    printf("%s", str_rev);

    free(str_rev);

    return OK;

}

char* string_reverse (char* str)
{

    char* rev_str = (char*)malloc(sizeof(char) * string_length(str) + 1);

    rev_str[string_length(str)] = '\0';


    char* crawler = str;
    char* rev_crawler = rev_str + string_length(str) - 1;

    while (*crawler != '\0')
    {
        *rev_crawler = *crawler;

        rev_crawler--;
        crawler++;
    }

    return rev_str;

}   



EXIT_CODE u_flag (int argc, char* argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    char* str_changed = string_change (argv);

    printf("%s", str_changed);

    free(str_changed);

    return OK;


}

char* string_change (char* argv)
{

    char* str_low_up = (char*)malloc(sizeof(char) * string_length(argv) + 1);

    for (int i = 0; i < string_length(argv); i++)
    {

        if (i % 2 == 0)
        {
            str_low_up[i] = argv[i];
        }
        else 
        {
            str_low_up[i] = toupper(argv[i]);
        }

        str_low_up[i + 1] = '\0';

    }

    return str_low_up;


}




EXIT_CODE n_flag (int argc, char* argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    char* sorted_str = string_sort(argv);

    printf("%s", sorted_str);

    free(sorted_str);

    return OK;

}

char* string_sort (char* argv)
{

    char* sorted_str = argv;

    qsort(sorted_str, string_length(sorted_str), sizeof(char), comp);

    return sorted_str;
}

int comp (const void* v1, const void* v2)
{

    char* c1 = (char*) v1;
    char* c2 = (char*) v2;

    if (isdigit(*c1))
    {
        if (isdigit(*c2))
        {
            return (*c1 - *c2);
        }
        return -1;
    }

    else if (isalpha(*c1))
    {
        if (isdigit(*c2)) 
        {
            return 1;
        }
        if (isalpha(*c2))
        {
            return (tolower(*c1) - tolower(*c2));
        }
        return -1;
    }
    else 
    {
        if (!isalnum(*c2))
        {
            return (*c1 - *c2);
        }
        return 1;
    }

}



EXIT_CODE c_flag (int argc, char** argv)
{

    if (argc < 4)
    {
        return INVALID;
    }

    unsigned int seed = 0;

    if (num_check(argv[2], &seed) != OK)
    {
        return INVALID;
    }

    char* str_res = (char*)malloc(sizeof(char) * (get_size(argc, argv) + 1));

    if (!str_res)
    {
        return BAD_ALLOC;
    }

    rand_cat(argc, argv + 3, str_res, seed);

    printf("%s", str_res);

    free(str_res);

    return OK;

}

EXIT_CODE num_check (char* str, unsigned int* res)
{

    char* end_ptr;

    long int buff = strtol(str, &end_ptr, 10);

    if (buff < 0 || buff > UINT_MAX)
    {
        return INVALID;
    }

    *res = buff;

    return (end_ptr == str + string_length(str)) ? OK : INVALID;

}

size_t get_size (int argc, char** argv)
{

    size_t size = 0;

    for (int i = 3; i < argc - 3; i++)
    {

        size += string_length(argv[i]);

    }

    return size;

}

EXIT_CODE rand_cat (int argc, char** argv, char* res, unsigned int seed)
{

    char** rand_arr = (char**)malloc(sizeof(char*) * argc - 3);

    if (!rand_arr)
    {
        return BAD_ALLOC;
    }

    for (int i = 0; i < argc - 3; i++)
    {
        rand_arr[i] = *argv;
        argv++;
    }

    srand(seed);
    qsort(rand_arr, argc - 3, sizeof(char*), randomizer);

    char* cur_pos = res;

    for (int i = 0; i < argc - 3; i++)
    {

        cur_pos = string_cat(cur_pos, rand_arr[i]);
        free(rand_arr[i]);

    }

    free(rand_arr);

}

int randomizer (const void *v1, const void* v2)
{
    return rand() % 2 ? 1 : -1;
}

char* string_cat (char* cur_pos, char* add)
{

    char* crawler = add;

    while (*crawler != '\0')
    {

        *cur_pos = *crawler;
        cur_pos++;
        crawler++;

    }
    *cur_pos = '\0';
    return cur_pos;

}



int main (int argc, char **argv) 
{

    warning();

    


    switch (input_check(argc, argv))
    {
        case OK:
            printf("\nSUCCESS!\n");
            break;
        
        case INVALID:
            printf("Invalid input!\n");
            usage();
            break;

        case BAD_ALLOC:
            printf("Memory fault!");
            break;
        default:
            break;
    }
    return 0;
}