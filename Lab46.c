
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

#include "Procedure.h"




int main ()//int argc, char **argv)
{

    int argc = 2;

    char *data[] = {"yes", "in.txt"};

    char **argv = data;

    switch (input_handle(argc, argv))
    {

        case OK:

            printf("Success!\n");
            break;

    }

    return 0;

}



EXIT_CODE string_init (String **dest)
{

    String *buff = (String*)malloc(sizeof(String));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->word = NULL;

    buff->allocated = 1;

    buff->occupied = 1;

    *dest = buff;

    return OK;

}


EXIT_CODE string_append (String *dest, char to_add)
{

    if (dest->allocated == dest->occupied)
    {

        dest->allocated += 1;

        dest->allocated *= 2;

        char *temp = (char*)realloc(dest->word, sizeof(char) * dest->allocated);

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->word = temp;

    }

    *(dest->word + (dest->occupied - 1)) = to_add;

    *(dest->word + dest->occupied) = '\0';

    dest->occupied++;

    return OK;

}


EXIT_CODE purge_str (String *dest)
{

    free(dest->word);
    dest->word = NULL;

    dest->allocated = 1;
    dest->occupied = 1;

    return OK;

}


void string_destr (String **dest)
{

    free((*dest)->word);
    (*dest)->word = NULL;

    (*dest)->allocated = 0;

    (*dest)->occupied = 0;

    free((*dest));
    (*dest) = NULL;

}






EXIT_CODE tnode_constr (T_node **dest, DATAFORMAT df, char data)
{

    T_node *buff = (T_node*)malloc(sizeof(T_node));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->format = df;

    buff->data = data;

    buff->left = NULL;

    buff->right = NULL;

    *dest = buff;

    return OK;

}


EXIT_CODE tnode_destr (T_node **dest)
{

    (*dest)->format = 0;

    (*dest)->data = 0;

    free((*dest)->left);

    free((*dest)->right);

    free(*dest);
    *dest = NULL;

    return OK;

}



EXIT_CODE snode_constr (S_node **dest, T_node *data, S_node *next)
{

    S_node *buff = (S_node*)malloc(sizeof(S_node));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->data = data;

    buff->next = next;

    *dest = buff;

    return OK;

}


EXIT_CODE snode_destr (S_node **dest)
{

    tnode_destr(&(*dest)->data);

    free((*dest)->next);
    (*dest)->next = NULL;

    free(*dest);
    *dest = NULL;

    return OK;

}


EXIT_CODE stack_init (Stack **dest)
{

    Stack *buff = (Stack*)malloc(sizeof(Stack));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->head = NULL;

    *dest = buff;

    return OK;

}


int is_stack_empty (Stack *src)
{
    return (src->head == NULL);
}


EXIT_CODE push (Stack *dest, T_node *to_add)
{

    S_node *new = NULL;

    EXIT_CODE assist = snode_constr(&new, to_add, dest->head);

    if (assist)
    {
        return assist;
    }

    dest->head = new;

    return OK;

}


T_node* pop(Stack *src)
{

    S_node *temp = src->head;

    src->head = temp->next;

    T_node *buff = temp->data;

    free(temp);
    temp = NULL;

    return buff; 

}


EXIT_CODE stack_destr (Stack **dest)
{

    while (!is_stack_empty(*dest))
    {

        T_node *buff = pop(*dest);

        tnode_destr(&buff);

    }

    free(*dest);
    *dest = NULL;

    return OK;

}




EXIT_CODE BST_init (BST **dest, int amount)
{

    BST *buff = (BST*)malloc(sizeof(BST));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->root = NULL;

    buff->vars = amount;

    *dest = buff;

    return OK;

}


EXIT_CODE add_leaf (T_node **root, T_node *to_add)
{
    
    EXIT_CODE assist = NO_ROOM;

    if (!(*root))
    {
        *root = to_add;

        return OK;

    }

    else if ((*root)->format <= CONST)
    {
        return NO_ROOM;
    }

    else
    {
        if (!(*root)->left || (*root)->left->format > CONST)
        {
            assist = add_leaf(&(*root)->left, to_add);
        }
        if ((!(*root)->right || (*root)->right->format > CONST) && assist && ((*root)->format != INVER))
        {
            assist = add_leaf(&(*root)->right, to_add);
        }
    }

    return assist;

}


EXIT_CODE tree_display (T_node *root, int tabs)
{

    if (!root)
    {
        return OK;
    }

    tree_display(root->right, tabs + 1);

    for (int i = 0; i < tabs; i++)
    {
        printf("\t");
    }

    printf("%d %c\n", root->format, root->data);

    tree_display(root->left, tabs + 1);

    return OK;

}


EXIT_CODE calc_tree (FILE *dest, T_node *root, int combs, int mask_sup, char *vars)
{

    if (!root)
    {
        return OK;
    }

    if (root->left->format != CONST && root->left->format != VAR)
    {
        calc_tree(dest, root->left, combs, mask_sup, vars);
    }

    if (root->right->format != CONST && root->right->format != VAR)
    {
        calc_tree(dest, root->right, combs, mask_sup, vars);
    }

    calc_expr(root, root->left, root->right, combs, mask_sup, vars);

    tnode_destr(&(root->left));
    tnode_destr(&(root->right));

}


EXIT_CODE calc_expr (T_node *func, T_node *operand1, T_node *operand2, int comb, int amount, char *vars)
{

    int res = 0;

    int o1 = 0;
    int o2 = 0;

    if (!operand1)
    {
        o2 = comb & (1 << (amount - (strchr(vars, operand2->data) - vars + 1)));
    }

    else if (!operand2)
    {
        o1 = comb & (1 << (amount - (strchr(vars, operand1->data) - vars + 1)));
    }

    else 
    {
        o1 = comb & (1 << (amount - (strchr(vars, operand1->data) - vars + 1)));
        o2 = comb & (1 << (amount - (strchr(vars, operand2->data) - vars + 1)));
    }

    execute_op(func->format, o1, o2, &res);

    func->format = CONST;
    func->data = res;

    return OK;

}


EXIT_CODE execute_op (DATAFORMAT func, int o1, int o2, int *res)
{

    switch (func)
    {
        
        case INVER:

            *res = o1 ^ 1;
            break;

        case WEBB_FUNCTION: 

            *res = (o1 & o2) ^ 1;
            break;

        case SHEFFER_STROKE:

            *res = (o1 | o2) ^ 1;
            break;

        case COIMPLIC:

            *res = (o1 <= o2) ^ 1;
            break;

        case CONJ:

            *res = (o1 & o2);
            break;

        case DISJ:

            *res = (o1 | o2);
            break;

        case IMPLIC:

            *res = (o1 <= o2);
            break;

        case EXCLUSIVE:

            *res = (o1 ^ o2);
            break;

        case EQUIVAL:
            *res = (o1 == o2);
            break;

    }

}






EXIT_CODE BST_destr (BST **dest)
{

    tree_destr(&(*dest)->root);

    (*dest)->vars = 0;

    free(*dest);
    *dest = NULL;

}


EXIT_CODE tree_destr (T_node **root)
{

    if (*root == NULL)
    {
        return OK;
    }

    tree_destr(&(*root)->left);

    tree_destr (&(*root)->right);

    tnode_destr(root);

    return OK;

}







EXIT_CODE input_handle (int argc, char **argv)
{

    if (argc != 2)
    {
        return INVALID;
    }

    return file_handle(*(argv + 1));

}


EXIT_CODE file_handle (char *filename)
{

    EXIT_CODE assist = OK;

    FILE *src = NULL;

    assist = is_file_proper(&src, filename);

    assist = assist ? assist : get_stack(src);

    fclose(src);

    return assist;

}


EXIT_CODE is_file_proper (FILE **src, char *filename)
{

    FILE *buff = fopen(filename, "r");

    if (!buff)
    {
        return BAD_ALLOC;
    }

    *src = buff;

    return OK;

}


EXIT_CODE get_stack (FILE *src)
{

    EXIT_CODE assist = OK;


    Stack *polish = NULL;

    assist = stack_init(&polish);

    String *vars = NULL;

    assist = assist ? assist : string_init(&vars);

    assist = assist ? assist : get_polish(polish, src, vars);

    assist = assist ? assist : tree_handle(polish, vars);

    string_destr(&vars);

    stack_destr(&polish);

    return assist;

}


EXIT_CODE get_polish (Stack *dest, FILE *src, String* vars)
{

    EXIT_CODE assist = OK;

    DATAFORMAT df;

    T_node *t = NULL;


    char c = 1;

    char prev = 1;

    int is_bracket = 0;


    Stack* op_order = NULL;

    assist = stack_init(&op_order);


    String *op = NULL;

    assist = assist ? assist : string_init(&op);


    while ((c = fgetc(src)) > 0 && !assist)
    {

        if (!isdigit(c) && !isalpha(c))
        {

            if (c == '>')
            {
                df = identify_op(*(op->word + (op->occupied - 2)));

                assist = (!df) ? INVALID : OK;
            }
            else
            {
                string_append(op, c);
            }
            
        }

        if ((op->occupied >= 3))
        {

            assist = (op->occupied == 3) ? assist : INVALID;

            DATAFORMAT t1 = identify_op(op->word[0]);
            DATAFORMAT t2 = identify_op(op->word[1]);

            if ((t1 != R_BRACKET && t2 <= 4) && (t2 != L_BRACKET && t1 <= 4))
            {
                return INVALID;
            }

            assist = assist ? assist : op_handle(dest, op_order, t1, &is_bracket);
            assist = assist ? assist : op_handle(dest, op_order, t2, &is_bracket);

            purge_str(op);
                  
        }

        else if ((isdigit(c) || isalpha(c)) && !assist)
        {

            if (op->word)
            {
                df = identify_op(*(op->word)); 

                assist = (!df) ? INVALID : op_handle(dest, op_order, df, &is_bracket);

                purge_str(op);
            }

            df = identify_format(c);

            assist = (!df) ? INVALID : assist; 

            T_node *new = NULL;

            assist = assist ? assist : tnode_constr(&new, df, c);

            assist = assist ? assist : push(dest, new);

            if ((vars->occupied == 1 || strchr(vars->word, c) == NULL) && !assist)
            {
                assist = string_append(vars, c);
            }

        }

    }

    if (!assist)
    {
        assist = (!is_bracket) ? assist : INVALID;

        if (!assist)
        {

            while (!is_stack_empty(op_order))
            {

                t = pop(op_order);

                push(dest, t);

            }
        }

    }

    string_destr(&op);

    stack_destr(&op_order);

    return assist;

}


EXIT_CODE op_handle(Stack *dest, Stack* src, DATAFORMAT df, int *is_bracket)
{

    EXIT_CODE assist = OK;

    T_node *buff = NULL;


    if (df == R_BRACKET)
    {

        while (src->head->data->format != L_BRACKET)
        {

            buff = pop(src);

            push(dest, buff);

        }

        buff = pop(src);

        tnode_destr(&buff);

        (*is_bracket)--;

        return OK;

    }

    if (df == L_BRACKET)
    {
        (*is_bracket)++;
    }

    else if (!(*is_bracket) && !is_stack_empty(src))
    {

        while (priority(src->head->data->format) >= priority(df))
        {

            buff = pop(src);

            push(dest, buff);

        }

    }

    assist = tnode_constr(&buff, df, 0);

    assist = assist ? assist : push(src, buff);
    
    return assist;

}


DATAFORMAT identify_format (char c)
{

    if (isdigit(c) && c <= '1')
    {
        return CONST;
    }

    if (isalpha(c))
    {
        return VAR;
    }

    return NONE;

}


DATAFORMAT identify_op (char op)
{

    char c = op;

    switch (c)
    {

        case '(':
            return L_BRACKET;

        case ')':
            return R_BRACKET;

        case '&':
            return CONJ;

        case '|':
            return DISJ;

        case '~':
            return INVER;

        case '=':
            return EQUIVAL;

        case '!':
            return SHEFFER_STROKE;

        case '?':
            return WEBB_FUNCTION;

        case '-':
            return IMPLIC;

        case '+':
            return COIMPLIC;

        case '<':
            return EXCLUSIVE;

    }

    return NONE;

}


int priority(DATAFORMAT df)
{

    switch (df)
    {

        case INVER:
            return 3;

        case WEBB_FUNCTION:
            return 2;

        case SHEFFER_STROKE:
            return 2;

        case COIMPLIC:
            return 2;

        case CONJ:
            return 2;

        case DISJ:
            return 1;

        case IMPLIC:
            return 1;

        case EXCLUSIVE:
            return 1;

        case EQUIVAL:
            return 1;

        case L_BRACKET:
            return 4;

        case R_BRACKET:
            return 4;

    }

}



EXIT_CODE tree_handle (Stack *src, String *vars)
{

    BST *tree = NULL;

    BST_init(&tree, (vars->occupied - 1));

    T_node *buff = NULL;

    while (!is_stack_empty(src))
    {

        buff = pop(src);

        add_leaf(&(tree->root), buff);

    }

    tree_display(tree->root, 0);

    output_process(tree, vars->word);

    BST_destr(&tree);

}


EXIT_CODE output_process (BST *src, char *vars)
{

    srand(time(NULL));

    FILE *output = NULL;

    create_rand_file(&output);

    for (int i = 0; i < src->vars; i++)
    {
        fprintf(output, "%c\t", vars[i]);
    }

    fprintf(output, "Answer\n");

    for (int i = 0; i < pow(2, src->vars); i++)
    {

        for (int t = src->vars - 1; t >= 0; t--)
        {
            fprintf(output, "%d\t", i & (1 << t));
        }

        calc_tree(output, src->root, i, src->vars, vars);
    }

}



EXIT_CODE create_rand_file (FILE** dest)
{

    char* filename;

    get_name(&filename);

    FILE* buff = fopen(filename, "w");

    free(filename);

    filename = NULL;

    printf("%s\n\n", filename);

    *dest = buff;

    return OK;

}


EXIT_CODE get_name (char** dest)
{

    char* filename = (char*)malloc(sizeof(char) * 64);

    if (!filename)
    {
        return BAD_ALLOC;
    }

    filename[63] = '\0';

    char symbols[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    char* c = filename;

    int seed = 19;

    while (*c != '\0')
    {

        int gay = get_rand(&seed);

        *c = symbols[gay];

        c++;

    }

    *dest = filename;

    srand(seed);

}


int get_rand(int* seed)
{

    *seed = rand();

    return *seed % 63;

}


