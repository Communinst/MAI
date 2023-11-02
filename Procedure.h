
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


EXIT_CODE valid_lint (char* str, long int* dest);

EXIT_CODE valid_lfloat (char* str, double* dest);

EXIT_CODE result_handling (int argc, char** argv, char flag);

EXIT_CODE sort_base (Employee** data_base, int size, char flag);

EXIT_CODE input_check (int argc, char** argv);

void usage();

EXIT_CODE write_down_data (Employee*** data_base, int size, char* out_name);



EXIT_CODE a_flag (int argc, Employee** data_base, int size);

int ascend_comp (const void* v1, const void* v2);

int descend_comp (const void* v1, const void* v2);


EXIT_CODE get_base (int argc, char** argv, Employee*** main_base, int* size);




EXIT_CODE get_node (Employee** main_node, int* current_pos, FILE* in);



EXIT_CODE get_str (FILE* in, int* current_pos, char** dest);



#endif