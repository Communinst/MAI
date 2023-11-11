
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

    unsigned int size;

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

    struct leaf* brother;

    struct leaf* child;

} leaf;


typedef struct 
{
    
    leaf* root;

    int (*comp)(int level1, int level2);

} tree;


/*----------------------------------------------------------------------------------------*/

void init_queue (queue* q);


int is_empty (queue* q);


EXIT_CODE enqueue (queue* q, int data, int level);


node_data dequeue (queue* q);


EXIT_CODE free_queue_content (queue* q);

/*----------------------------------------------------------------------------------------*/




/*----------------------------------------Tree-handling-----------------------------------*/

int comp(int level1, int level2);


EXIT_CODE init_tree (tree* main);


EXIT_CODE destr_tree (tree* main);


EXIT_CODE destr_branches (leaf** root);


EXIT_CODE leaf_constr (leaf* leaf, node_data data);


EXIT_CODE leaf_destr (leaf* leaf);


EXIT_CODE add_leaf (leaf** root, node_data data, int (*comp)(int level1, int level2), int* last_added);
    

EXIT_CODE status_0_handling (leaf** root, node_data data, int* last_added);


/*----------------------------------------------------------------------------------------*/

EXIT_CODE input_control (int argc, char** argv);


EXIT_CODE file_handling (int argc, char** argv);


EXIT_CODE prepare_queue (queue* q, char* c, FILE* in);


EXIT_CODE queue_to_tree (leaf** dest, queue* q);




#endif