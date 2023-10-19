
#ifndef PROCEDURE_H
#define PROCEDURE_H

#define ARR_SIZE 20

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE
} EXIT_CODE;





void usage ();


EXIT_CODE input_check (int argc, char **argv);


EXIT_CODE find_min_max (int arr[ARR_SIZE], long int *min, long int *max);


EXIT_CODE fill_with_rands (int *arr, long int l_board, long int r_board, int size);


long int get_rand (long int l_board, long int r_board);


EXIT_CODE merge_two_arrs (int *arr1, int size1, int *arr2, int size2, int *arr_res);


int find_closest (int target, int *arr, int size);

#endif