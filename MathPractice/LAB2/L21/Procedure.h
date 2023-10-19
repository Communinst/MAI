
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE,
    EoF,
} EXIT_CODE;


void warning ();


void usage ();


EXIT_CODE input_check (int argc, char** argv);


EXIT_CODE flag_handling (char flag, int argc, char** argv);



EXIT_CODE l_flag (int argc, char* argv);

size_t string_length (char* str);



EXIT_CODE r_flag (int argc, char* argv);

char* string_reverse (char* str);



EXIT_CODE u_flag (int argc, char* argv);

char* string_change (char* argv);



EXIT_CODE n_flag (int argc, char* argv);

char* string_sort (char* argv);

int comp (const void* v1, const void* v2);



EXIT_CODE c_flag (int argc, char** argv);

EXIT_CODE num_check (char* str, unsigned int* res);

size_t get_size (int argc, char** argv);

EXIT_CODE rand_cat (int argc, char** argv, char* res, unsigned int seed);

int randomizer (const void *v1, const void* v2);

char* string_cat (char* cur_pos, char* add);

#endif