
#ifndef PROCEDURE_H
#define PROCEDURE_H


typedef enum 
{

    OK = 0,

    INVALID,

    BAD_ALLOC,

    NO_FILE,

    BRCKTS_DISBALANCE,

    UNCERTAINTY,

    ZERO_DIVISION,

    COMMITTED,

} EXIT_CODE;




typedef struct
{

    int occupied;

    int allocated;

    char* word;

} string;




typedef struct
{

    unsigned int order;

    char* raw_expr;

    char* rev_polish;

    int value;

} expression;




typedef struct
{

    char* filename;

    unsigned int occupied;

    unsigned int allocated;

    expression** data;

} file_stuff;




typedef struct
{

    unsigned int occupied;
    
    unsigned int allocated;

    file_stuff** elem;

} vec_file;




typedef struct node
{

    int op; 

    struct node* next;

} node;




typedef struct
{

    node* head;

} stack;




typedef struct queue_node
{
    
    int op;

    int data;

    struct queue_node* next;

} queue_node;




typedef struct
{

    int size;

    queue_node* front;

    queue_node* rear;

} queue;






EXIT_CODE string_init (string** dest);


EXIT_CODE string_append (string* dest, char to_add);



EXIT_CODE fs_init (file_stuff** dest, char* filename);


EXIT_CODE fs_append (file_stuff* dest, expression* to_add);





EXIT_CODE vec_init (vec_file** dest);




EXIT_CODE stack_init (stack** dest);


EXIT_CODE push (stack* dest, int item);


char pop (stack* src);


int is_stack_empty (stack* src);




EXIT_CODE queue_init (queue** dest);


int is_queue_empty (queue* src);


EXIT_CODE enqueue (queue* dest, int op, int data);


queue_node* dequeue (queue* src);




EXIT_CODE input_handle (int argc, char** argv);



EXIT_CODE prepare_output (int argc, char** argv);


EXIT_CODE files_count (int argc, char** argv, vec_file* vec);


EXIT_CODE file_handle (char* filename, file_stuff* fsd);


EXIT_CODE is_file_proper (FILE** dest, char* src);


EXIT_CODE data_handle (FILE** src, file_stuff* fsd);


EXIT_CODE record_error (FILE** dest, expression* src, EXIT_CODE info);


EXIT_CODE create_rand_file (FILE** dest);


EXIT_CODE get_name (char** dest);


int get_rand();


EXIT_CODE get_expr(expression** dest, unsigned int order, FILE* src, char* c);


EXIT_CODE get_raw (string* dest, FILE* src, char* c);


EXIT_CODE get_polish (string* dest, queue** q, char* src);


EXIT_CODE polish_handle (string* dest, stack* ops, queue* calc, int* n, char c, int* is_bracket);


int priority (char c);


EXIT_CODE calc_polish (int* res, queue* src);


EXIT_CODE execute_op (int* res, stack* src, char c);


#endif