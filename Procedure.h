
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{

    OK = 0,
    INVALID,
    BAD_ALLOC,
    NO_FILE,
    EoS,
    
} EXIT_CODE;


typedef struct 
{

    int frequency;

    char* key;

    int passed;

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






/*-------------------------------------------------MAIN--------------------------------------------------*/

int main (int argc, char** argv);

/*-------------------------------------------------------------------------------------------------------*/




/*---------------------------------------Trees-constrs-destrs--------------------------------------------*/

EXIT_CODE str_copy (char **dest, char *src);


EXIT_CODE DN_constr (data_node **dest, int frequency, char *key);


EXIT_CODE DN_destr (data_node **dest);


EXIT_CODE TN_constr (tree_node **dest, int frequency, char *key);


EXIT_CODE TN_destr (tree_node **dest);


EXIT_CODE BST_init (BST **dest);


EXIT_CODE BST_destr (BST **dest);


EXIT_CODE shortest_longest (BST *tree, char *key);


EXIT_CODE tree_destr (tree_node **root);


EXIT_CODE add_leaf (tree_node **root, char *key, int frequency, BST *tree);


EXIT_CODE show_tree(tree_node *root, int tabs);


EXIT_CODE show_n_nodes(tree_node *root, int *n);


EXIT_CODE get_tree (BST *res, char *filename, char *dividers);


EXIT_CODE get_word_file (char **dest, char *c, char *dividers, FILE *in);


EXIT_CODE get_word_stdin (char **dest);

/*-------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------Input-hub-------------------------------------------------*/

EXIT_CODE input_handle (int argc, char **argv);


EXIT_CODE collect_divs (char **dest, char **argv, int argc);

/*-------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------Interactivity--------------------------------------------*/

EXIT_CODE interactivity(char *filename, char *dividers);


EXIT_CODE dialog_box(BST *data);


EXIT_CODE menu();


EXIT_CODE choice_handle (char choice, BST *data);

/*-------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------Task-A-------------------------------------------------*/

//1
EXIT_CODE longest (BST *data);


//2
EXIT_CODE shortest (BST *data);


//3
EXIT_CODE n_frequent(BST *data);


EXIT_CODE get_n(int* n);


EXIT_CODE get_n_freq (char **dest, tree_node *src, int n);


EXIT_CODE get_max (char **dest, tree_node *src, int *max);


EXIT_CODE passed_zero (tree_node *data);


//4
EXIT_CODE find_word (tree_node *data);


EXIT_CODE meet_frequency (char *to_find, tree_node *data, int *amount);

/*-------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------Task-B-----------------------------------------------*/

//5
EXIT_CODE get_depth (tree_node *data);

int tree_depth (tree_node *data);

/*-------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------Task-C-----------------------------------------------*/

EXIT_CODE print_tree_file (BST *data);


EXIT_CODE prefix_write (tree_node *data, FILE* out, int tabs);


EXIT_CODE get_new_tree_file (BST *dest);


EXIT_CODE file_valid (FILE *in);


EXIT_CODE read_tree_file (BST *dest, FILE *in);


EXIT_CODE get_max_min (BST *dest, FILE *in);


EXIT_CODE fget_data_node (FILE *in, char **key, int *frequency, char *c);

/*-------------------------------------------------------------------------------------------------------*/


#endif