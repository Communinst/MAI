
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include "Procedure.h"




EXIT_CODE menu()
{

    printf("1 - print the longest word;\n");
    printf("2 - print the shortest word;\n");
    printf("3 - print /n/ the most frequent words;\n");
    printf("4 - find the word requested;\n");
    printf("5 - find the depth of th tree;\n");
    printf("0 - EXIT\n");

}




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
    buff->passed = 0;
    strcpy(buff->key, key);

    *dest = buff;

    return OK;

}


EXIT_CODE DN_destr (data_node **dest)
{

    free((*dest)->key);
    (*dest)->key = NULL;

    (*dest)->frequency = 0;
    (*dest)->passed = 0;

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

    free((*dest)->longest);

    free((*dest)->shortest);

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


EXIT_CODE add_leaf (tree_node **root, char *key, BST *tree)
{

    if (!(*root))
    {

        tree_node *new = NULL;

        TN_constr(&new, 1, key);

        *root = new;

        shortest_longest(tree, key);

    }

    else if ((strcmp(key, (*root)->stuff->key)) < 0)
    {
        add_leaf(&(*root)->left, key, tree);
    }

    else if ((strcmp(key, (*root)->stuff->key)) > 0)
    {
        add_leaf(&(*root)->right, key, tree);
    }

    else 
    {
        ((*root)->stuff->frequency)++;
    }

    return OK;


}


EXIT_CODE shortest_longest (BST *tree, char *key)
{

    size_t size = strlen(key);

    if (!(tree->longest))
    {

        str_copy(&(tree->longest), key);
        str_copy(&(tree->shortest), key);

    }

    else if (strlen(tree->longest) <= size)
    {

        free(tree->longest);
        str_copy(&(tree->longest), key);

    }

    else if (strlen(tree->shortest) >= size)
    {

        free(tree->shortest);
        str_copy(&(tree->shortest), key);

    }

    return OK;


}


EXIT_CODE str_copy (char **dest, char *src)
{

    size_t size = strlen(src);

    char* buff = (char*)malloc(sizeof(char) * (size + 1));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    strcpy(buff, src);

    *dest = buff;

    return OK;

}


EXIT_CODE show_tree(tree_node *root, int tabs) 
{

    if (!root)
    {
        return OK;
    }

    show_tree(root->right, tabs + 1);

    for (int i = 0; i < tabs; i++)
    {
        printf("\t");
    }

    printf("%d %s\n", root->stuff->frequency, root->stuff->key);

    show_tree(root->left, tabs + 1);

    return OK;

}


EXIT_CODE show_n_nodes(tree_node *root, int *n)
{

    if (!root)
    {
        return OK;
    }

    show_n_nodes(root->right, n);

    (*n) = (*n) - 1;

    if (*n < 0)
    {
        return OK;
    }

    printf("%s - %d times; n is %d\n", root->stuff->key, root->stuff->frequency, *n);

    show_n_nodes(root->left, n);

}



EXIT_CODE input_handle (int argc, char **argv)
{

    if (argc < 3)
    {
        return INVALID;
    }


    char *div_coll = NULL;

    collect_divs(&div_coll, argv + 2, argc - 2);

    interactivity(argv[1], div_coll);

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


EXIT_CODE interactivity(char *filename, char *dividers)
{

    BST* res = NULL;
    BST_init(&res);

    get_tree(res, filename, dividers);
    show_tree(res->root, 0);

    int n = 2;

    show_n_nodes(res->root, &n);

    dialog_box(res);

    BST_destr(&res);

}



EXIT_CODE dialog_box(BST *data)
{

    menu();

    char c;

    while (!feof(stdin))
    {

        c = getchar();

        fflush(stdin);

        if (isdigit(c))
        {
            if (choice_handle(c, data) != OK)
            {
                return EoS;
            }
        }

    }
        
    return OK;
}


EXIT_CODE choice_handle (char choice, BST *data)
{

    switch (choice)
    {
        case '1':

            return longest(data);

        case '2':

            return shortest(data);


        case '3':

            return n_frequent(data);

        
        case '5':

            return get_depth(data->root);

        case '0':

            return EoS;


        default:
            printf("Unknown request! Check the menu hub.\n");
            return OK;
    }

}


EXIT_CODE longest (BST *data)
{

    printf("%s\n", data->longest);

    return OK;

}


EXIT_CODE shortest (BST *data)
{

    printf("%s\n", data->shortest);

    return OK;

}


EXIT_CODE n_frequent(BST *data)
{

    int n = 0;

    printf("Enter the amount of values to print:\n");

    if (get_n(&n) != OK)
    {
        return EoS;
    }

    char **res = (char**)malloc(sizeof(char*) * n);

    if (!res)
    {
        return BAD_ALLOC;
    }

    for (int i = 0; i < n; i++)
    {
        res[i] = NULL;
    }

    char **crawl = res;

    get_n_freq(crawl, data->root, n);

    for (int i = 0; i < n; i++)
    {

        printf("%s\n", *(res + i));
        free(*(res + i));
        *(res + i) = NULL;
        printf("%s\n", *(res + i));

    }

    free(res);

    res = NULL;

    return OK;

}


EXIT_CODE get_n(int* n)
{

    char c;

    while ((c = getchar()) > 0 && c != '\n')
    {

        if (isdigit(c))
        {

            *n *= 10;
            *n += (c - '0');

        }

    }

    if (c < 0)
    {
        return EoS;
    }

    return OK;

}


EXIT_CODE get_n_freq (char **dest, tree_node *src, int n)
{

    while (n--)
    {

        int max = 0;

        get_max (dest, src, &max);

        dest++;

    }

    passed_zero(src);

    return OK;


}


EXIT_CODE get_max (char **dest, tree_node *src, int *max)
{

    if (!src)
    {
        return OK;
    }

    if (*max < src->stuff->frequency && !(src->stuff->passed))
    {

        *max = src->stuff->frequency;

        src->stuff->passed = 1;

        free(*dest);

        str_copy(dest, src->stuff->key);

    }

    get_max(dest, src->left, max);
    get_max(dest, src->right, max);

    return OK;

}


EXIT_CODE passed_zero (tree_node *data)
{

    if (!data)
    {
        return OK;
    }

    data->stuff->passed = 0;

    passed_zero(data->right);
    passed_zero(data->left);
    
}



EXIT_CODE get_depth (tree_node *data)
{

    printf("%d\n", tree_depth(data));

    return OK;

}


int tree_depth (tree_node *data)
{

    if (!data)
    {
        return 0;
    }

    int path1 = tree_depth(data->right);
    int path2 = tree_depth(data->left);

    return (path1 > path2) ? path1 + 1 : path2 + 1;

}


EXIT_CODE get_tree (BST *res, char *filename, char *dividers)
{

    FILE* in = fopen(filename, "r");

    if (!in)
    {
        return NO_FILE;
    }

    char c;

    char* temp_str = NULL;

    do
    {

        get_word(&temp_str, &c, dividers, in);

        add_leaf(&(res->root), temp_str, res);

        free(temp_str);

    } while (c > 0);
    
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

    size_t amount = 0;

    while (!strchr(dividers, (*c = fgetc(in))) && (*c > 0))
    {

        if (!isspace(*c))
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

    }

    *dest = buff;

    return OK;

}




int main ()//int argc, char** argv) 
{

    int argc = 3;
    
    char *data[] = {"yes", "in.txt", ","};

    char** argv = data;


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