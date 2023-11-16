
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{

    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE,
    
} EXIT_CODE;


typedef struct 
{

    int frequency;

    char* key;

} data_node;


typedef struct tnode
{

    data_node *stuff;

    struct tnode *left;

    struct tnode *right;

} tree_node;



typedef struct 
{

    tree_node *root;

    data_node *longest;

    data_node *shortest;

} BST;






EXIT_CODE collect_divs (char **dest, char **argv, int argc);

#endif