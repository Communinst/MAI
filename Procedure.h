
#ifndef PROCEDURE_H
#define PROCEDURE_H


typedef enum 
{

    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE,

} EXIT_CODE;

/*------------------------------------------Queue-----------------------------------------*/

typedef struct 
{

    int data;

    int level;

} node_data;


typedef struct node
{

    int data;

    int level;

    struct node* next;

} queue_node;


typedef struct
{

    queue_node* front;
    queue_node* rear;
    int size;

} queue;


void init_queue (queue* q);


int is_empty (queue* q);


EXIT_CODE enqueue (queue* q, int data, int level);


node_data dequeue (queue* q);


EXIT_CODE free_queue_content (queue* q);

/*----------------------------------------------------------------------------------------*/



/*----------------------------------------Tree-handling-----------------------------------*/

typedef struct leaf
{

    node_data data;

    leaf* brother;

    leaf* child;

} leaf;


typedef struct 
{
    
    leaf* root;

    int (*comp)(int level1, int level2);

} tree;


/*----------------------------------------------------------------------------------------*/







EXIT_CODE input_control (int argc, char** argv);


EXIT_CODE file_handling (int argc, char** argv);


EXIT_CODE prepare_queue (queue* q, char* c, FILE* in);




#endif