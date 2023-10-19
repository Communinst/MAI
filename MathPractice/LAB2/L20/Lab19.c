
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "Procedure.h"



void usage () 
{
    printf("\n./[name_of_exe] left_board_ld_value right_board_ld_value.\n");
    printf("  Allowed range of values: [-2147483647 -> 2147483647]\n\n");
}


EXIT_CODE str_proper_check (char *str, long int *value)
{

    char *end_o_str;

    *value = strtol(str, &end_o_str, 10);

    if (end_o_str != str + strlen(str))
    {
        return INVALID;
    }
    return OK;

}


EXIT_CODE input_check (int argc, char **argv) 
{

    srand(time(NULL));

    if (argc != 3) 
    {
        return INVALID;
    }

    long int l_board, r_board;
    
    if ((str_proper_check(argv[1], &l_board) == INVALID) || (str_proper_check(argv[2], &r_board)) == INVALID)
    {
        return INVALID;
    }

    if (l_board > r_board)
    {
        return INVALID;
    }

    int arr_1[ARR_SIZE];
    fill_with_rands(arr_1, l_board, r_board, ARR_SIZE);

    long int min = LONG_MAX;
    long int max = LONG_MIN;

    find_min_max(arr_1, &min, &max);
    printf("Part 1:\nMin - %ld\nMax = %ld\n", min, max);


    int size_arr1 = get_rand(10, 10000);
    int arr1[size_arr1];

    int size_arr2 = get_rand(10, 10000);
    int arr2[size_arr2];

    fill_with_rands(arr1, -1000, 1000, size_arr1);
    fill_with_rands(arr2, -1000, 1000, size_arr2);

    int *arr_resulted = (int*)malloc(sizeof(int) * size_arr1);
    if (!arr_resulted)
    {
        return BAD_ALLOC;
    }

    merge_two_arrs(arr1, size_arr1, arr2, size_arr2, arr_resulted);

    printf("Part 2:\n");
    for (int i = 0; i < size_arr1; i++)
    {
        printf("%d\n", arr_resulted[i]);
    }

    free(arr_resulted);

    return OK;

}


EXIT_CODE find_min_max (int arr[ARR_SIZE], long int *min, long int *max)
{

    for (int i = 0; i < ARR_SIZE; i++)
    {

        if (*min > arr[i])
        {
            *min = arr[i];
        }

        if (*max < arr[i])
        {
            *max = arr[i];
        }

    } 

    return OK;

}


EXIT_CODE fill_with_rands (int *arr, long int l_board, long int r_board, int size)
{

    for (int i = 0; i < size; i++)
    {
        arr[i] = get_rand(l_board, r_board);
    }

    return OK;

}


long int get_rand (long int l_board, long int r_board)
{
    return (rand() % (r_board - l_board + 1) + l_board);
}


EXIT_CODE merge_two_arrs (int *arr1, int size1, int *arr2, int size2, int *arr_res)
{

    for (int i = 0; i < size1; i++)
    {
        arr_res[i] = arr1[i] + find_closest(arr1[i], arr2, size2);
    }

}


int find_closest (int target, int *arr, int size)
{

    int closest = LONG_MAX;
    int diff = LONG_MAX;
    for (int i = 0; i < size; i++)
    {

        if (abs(target - arr[i]) < diff) 
        {
            diff = abs(target - arr[i]);
            closest = arr[i];
        }

    }

    return closest;

}


int main (int argc, char **argv) 
{

    switch (input_check(argc, argv))
    {
        case OK:
            printf("SUCCESS!\n");
            break;
        
        case INVALID:
            printf("\n                     Invalid input!\n");
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