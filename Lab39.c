
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include "Procedure.h"



EXIT_CODE DN_constr (data_node **dest, int frequency, char *key)
{

    int length = strlen(key);

    data_node *buff = (data_node *)malloc(sizeof(data_node));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->key = (char *)malloc(sizeof(char) * (length + 1));

    if (!(buff->key))
    {

        free(buff);
        *dest = NULL;

        return BAD_ALLOC;

    }

    buff->frequency = frequency;
    strcpy(buff->key, key);

    *dest = buff;

    return OK;

}


EXIT_CODE DN_destr (data_node **dest)
{

    free((*dest)->key);
    (*dest)->key = NULL;

    (*dest)->frequency = 0;

    free(*dest);
    *dest = NULL;

    return OK;

}


EXIT_CODE TN_constr (tree_node **dest, int frequency, char *key)
{

    tree_node *buff = (tree_node *)malloc(sizeof(tree_node));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    if (DN_constr(&(buff->stuff), frequency, key) != OK)
    {
        free(buff);
        return BAD_ALLOC;
    }

    buff->left = NULL;
    buff->right = NULL;

    *dest = buff;
    
    return OK;

}


EXIT_CODE TN_destr (tree_node **dest)
{

    free((*dest)->left);
    free((*dest)->right);

    (*dest)->left = NULL;
    (*dest)->right = NULL;

    DN_destr(&((*dest)->stuff));

    free(*dest);

    *dest = NULL;

}


EXIT_CODE BST_init (BST **dest)
{

    BST* buff = (BST*)malloc(sizeof(BST));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->root = NULL;

    buff->longest = NULL;

    buff->shortest = NULL;

    *dest = buff;

    return OK;

}


EXIT_CODE BST_destr (BST **dest)
{

    tree_destr(&((*dest)->root));
    free((*dest)->root);
    (*dest)->root = NULL;

    free((*dest)->shortest);
    (*dest)->shortest = NULL;
    
    free((*dest)->longest);
    (*dest)->longest = NULL;

    return OK;

}


EXIT_CODE tree_destr (tree_node **root)
{

    if (!(*root))
    {
        return OK;
    }

    tree_destr (&((*root)->left));
    tree_destr (&((*root)->right));

    TN_destr(root);

    return OK;

}


EXIT_CODE add_leaf (tree_node **root, char *key)
{

    if (!(*root))
    {
        tree_node *new = NULL;

        TN_constr(&new, 0, key);

        *root = new;
    }

    if (strcmp(key, (*root)->stuff->key) < 0)
    {
        add_leaf(&(*root)->left, key);
    }

    else if (strcmp(key, (*root)->stuff->key) > 0)
    {
        add_leaf(&(*root)->right, key);
    }

    else 
    {
        ((*root)->stuff->frequency)++;
    }

    return OK;


}


EXIT_CODE show_tree()


EXIT_CODE input_handle (int argc, char **argv)
{

    if (argc < 3)
    {
        return INVALID;
    }


    char *div_coll = NULL;

    collect_divs(&div_coll, argv + 2, argc - 2);

    for (int i = 0 ; i < argc - 2; i++)
    {
        printf("%c\n", div_coll[i]);
    }

    file_handle(argv[1], div_coll);

    free(div_coll);

    return OK;
    
}


EXIT_CODE collect_divs (char **dest, char **argv, int argc)
{

    char* buff = (char*)malloc(sizeof(char) * (argc - 1));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff[(argc - 2)] = '\0';

    char* crawl = buff;

    while (argc--)
    {

        *crawl = **argv;

        argv++;

        crawl++;

    }

    *dest = buff;

    return OK;

}



EXIT_CODE file_handle (char *filename, char *dividers)
{

    FILE* in = fopen(filename, "r");

    if (!in)
    {
        return NO_FILE;
    }

    BST* res = NULL;

    char c;

    char* temp_str = NULL;

    do
    {

        get_word(&temp_str, &c, dividers, in);

        add_leaf(&(res->root), temp_str);

        free(temp_str);

    } while (c > 0);
    
    BST_destr(&res);

    return OK;

}



EXIT_CODE get_word (char **dest, char *c, char *dividers, FILE *in)
{

    char *buff = (char*)malloc(sizeof(char) * 1);

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff[0] = '\0';

    int amount = 0;

    while (!strchr(dividers, (*c = fgetc(in))) || (*c < 0))
    {

        if (amount == strlen(buff))
        {

            char* temp = (char*)realloc(buff ,sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            buff = temp;

        }

        buff[amount] = *c;

        buff[++amount] = '\0';

    }

    *dest = buff;

    return OK;

}




int main (int argc, char** argv) 
{
    
    /*data_node* res = NULL;

    DN_constr (&res, 14, "idiot");

    printf("%d %s\n", res->frequency, res->key);

    DN_destr(&res);


    tree_node *out = NULL;

    TN_constr(&out, 14, "moron");

    printf("%d %s\n", out->stuff->frequency, out->stuff->key);

    TN_destr(&out);*/

    switch (input_handle(argc, argv))
    {
        case OK:
            printf("SUCCESS!\n");
            break;
        
        case INVALID:
            printf("Invalid input!\n");
            break;

        default:
            break;
    }

    return 0;

}