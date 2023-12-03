
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum 
{

    OK = 0,
    
    INVALID, 

    NO_FILE,

    BAD_ALLOC,

    NO_ROOM,

    
} EXIT_CODE;




typedef enum
{

    NONE = 0,

	VAR,

    CONST,

	L_BRACKET,

	R_BRACKET,

	CONJ,

	DISJ,

	INVER,

	IMPLIC, 

	COIMPLIC,

	EXCLUSIVE,
    
	EQUIVAL,

	SHEFFER_STROKE,

	WEBB_FUNCTION,

} DATAFORMAT;



typedef struct
{

    size_t allocated;

    size_t occupied;

    char* word;

} String;




typedef struct T_node
{

    DATAFORMAT format;

    char data;

    struct T_node *left;

    struct T_node *right;

} T_node;




typedef struct S_node
{

    T_node *data;

    struct S_node *next;

} S_node;




typedef struct
{

    S_node *head;

} Stack;




typedef struct 
{
    
    T_node *root;

    int vars;

} BST;





EXIT_CODE string_init (String **dest);


EXIT_CODE string_append (String *dest, char to_add);


void string_destr (String **dest);






EXIT_CODE tnode_constr (T_node **dest, DATAFORMAT df, char data);


EXIT_CODE tnode_destr (T_node **dest);



EXIT_CODE snode_constr (S_node **dest, T_node *data, S_node *next);


EXIT_CODE snode_destr (S_node **dest);


EXIT_CODE stack_init (Stack **dest);


int is_stack_empty (Stack *src);


EXIT_CODE push (Stack *dest, T_node *to_add);


T_node* pop(Stack *src);


EXIT_CODE stack_destr (Stack **dest);




EXIT_CODE BST_init (BST **dest, int amount);


EXIT_CODE add_leaf (T_node **root, T_node *to_add);


EXIT_CODE tree_display (T_node *root, int tabs);


EXIT_CODE BST_destr (BST **dest);


EXIT_CODE tree_destr (T_node **root);




EXIT_CODE input_handle (int argc, char **argv);


EXIT_CODE file_handle (char *filename);


EXIT_CODE is_file_proper (FILE **src, char *filename);


EXIT_CODE get_stack (FILE *src);


EXIT_CODE get_polish (Stack *dest, FILE *src, String* vars);


EXIT_CODE const_var_handle (Stack *dest, char c, DATAFORMAT df, String *var_cnt);


DATAFORMAT identify_format (char c);


DATAFORMAT identify_op (char op);


EXIT_CODE op_handle (Stack *dest, Stack *ops, DATAFORMAT df, int* is_bracket);


int priority(DATAFORMAT df);


EXIT_CODE tree_handle (Stack *src, String *vars);







#endif