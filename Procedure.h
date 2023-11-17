
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


typedef struct tree_node
{

    data_node *stuff;

    struct tree_node *left;

    struct tree_node *right;

} tree_node;



typedef struct 
{

    tree_node *root;

    char *longest;

    char *shortest;

} BST;






EXIT_CODE DN_constr (data_node **dest, int frequency, char *key);


EXIT_CODE DN_destr (data_node **dest);


EXIT_CODE TN_constr (tree_node **dest, int frequency, char *key);


EXIT_CODE TN_destr (tree_node **dest);


EXIT_CODE BST_init (BST **dest);


EXIT_CODE BST_destr (BST **dest);


EXIT_CODE tree_destr (tree_node **root);


EXIT_CODE add_leaf (tree_node **root, char *key, BST *tree);


EXIT_CODE shortest_longest (BST *tree, char *key);


EXIT_CODE str_copy (char **dest, char *src);


EXIT_CODE input_handle (int argc, char **argv);


EXIT_CODE collect_divs (char **dest, char **argv, int argc);



EXIT_CODE file_handle (char *filename, char *dividers);



EXIT_CODE get_word (char **dest, char *c, char *dividers, FILE *in);

#endif