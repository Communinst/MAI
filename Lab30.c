
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#include "Procedure.h"



/*------------------------------------------Queue-----------------------------------------*/

void init_queue (queue* q)
{

    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

}


int is_empty (queue* q)
{
    return q->size;
}


EXIT_CODE enqueue (queue* q, int data, int level)
{

    queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));

    if (!new_node)
    {
        return BAD_ALLOC;
    }

    new_node->data = data;

    new_node->level = level;

    new_node->next = NULL;

    if (!is_empty(q))
    {
        q->front = new_node;
        q->rear = new_node;
    }

    else 
    {   

        q->rear->next = new_node;

        q->rear = new_node;
        
    }
    q->size++;

    return OK;

}


node_data dequeue (queue* q)
{

    if (!is_empty(q))
    {
        node_data temp1 = {-1, -1};
        return temp1; 
    }

    queue_node* temp2 = q->front;

    q->front = q->front->next;

    q->size--;

    node_data res = {temp2->data, temp2->level};

    free(temp2);

    if (!is_empty(q))
    {
        q->rear = NULL;
    }

    return res;

}


EXIT_CODE free_queue_content (queue* q)
{

    while (q->size)
    {
        dequeue(q);
    }

    return OK;

}

/*----------------------------------------------------------------------------------------*/




/*----------------------------------------Tree-handling-----------------------------------*/

int comp(int level1, int level2)
{

    return level2 - level1;

}


EXIT_CODE init_tree (tree* main)
{

    main->root = NULL;

    main->comp = 0;

    return OK;

}


EXIT_CODE destr_tree (tree* main)
{

    destr_branches(&(main->root));

    main->comp = 0;

    return OK;

}


EXIT_CODE destr_branches (leaf** root)
{

    if (!(*root))
    {
        return OK;
    }

    destr_branches(&(*root)->child);
    destr_branches(&(*root)->brother);

    leaf_destr((*root));

    return OK;

}


EXIT_CODE leaf_constr (leaf* leaf, node_data data)
{

    leaf->data = data;

    leaf->child = NULL;

    leaf->brother = NULL;

    return OK;

}


EXIT_CODE leaf_destr (leaf* leaf)
{

    leaf->data.data = 0;

    leaf->data.level = 0;

    if (leaf->child)
    {

        free(leaf->child);
    }

    if (leaf->child)
    {
        free(leaf->brother);
    }

}


EXIT_CODE add_leaf (leaf** root, node_data data, int (*comp)(int level1, int level2), node_data* last_added)
{    

    if (((*last_added).data == -1))
    {

        leaf* new_node = (leaf*)malloc(sizeof(leaf));

        if (!new_node)
        {
            return BAD_ALLOC;
        }

        leaf_constr(new_node, data);

        *root = new_node;

        *last_added = data;

        return OK;

    }


    int stat = comp((*root)->data.level, data.level);

    if (stat < 0)
    {
        return OK;
    }

    if (stat == 1)
    {

        if (((*root)->data.data == (*last_added).data) && (!(*root)->child))
        {
            leaf* new_node = (leaf*)malloc(sizeof(leaf));

            if (!new_node)
            {
                return BAD_ALLOC;
            }

            leaf_constr(new_node, data);

            (*root)->child = new_node;

            *last_added = data;

            return OK;
        }
    }

    if (!stat)
    {

        status_0_handling(root, data, last_added);

        return OK;

    }

    if ((*root)->child)
    {
        add_leaf(&(*root)->child, data, comp, last_added);
    }
    if ((*root)->brother)
    {
        add_leaf(&(*root)->brother, data, comp, last_added);
    }

}
    

EXIT_CODE status_0_handling (leaf** root, node_data data, node_data* last_added)
{

    if (((*root)->data.data == (*last_added).data) || (((*root)->data.level) - (*last_added).level) < 0)
    {

        leaf* new_node = (leaf*)malloc(sizeof(leaf));

        if (!new_node)
        {
            return BAD_ALLOC;
        }

        leaf_constr(new_node, data);

        (*root)->brother = new_node;

        *last_added = data;

        return OK;

    }

    if (!(*root)->brother)
    {
        return OK;
    }

    status_0_handling(&(*root)->brother, data, last_added);

}


EXIT_CODE show_tree (leaf* root, FILE* out)
{

    if (!root)
    {
        return OK;
    }

    for (int tabs = 0; tabs < root->data.level; tabs++)
    {
        fprintf(out, "\t");
    }

    fprintf(out, "%c\n", root->data.data);

    show_tree(root->child, out);

    show_tree(root->brother, out);

    return OK;

}

/*----------------------------------------------------------------------------------------*/

EXIT_CODE input_control (int argc, char** argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    return file_handling(argc, argv);

}


EXIT_CODE file_handling (int argc, char** argv)
{

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if (!out || !in)
    {
        return NO_FILE;
    }

    queue* instance = (queue*)malloc(sizeof(queue));
    
    if (!instance)
    {
        return BAD_ALLOC;
    }

    init_queue(instance);

    tree* prepare_repres = (tree*)malloc(sizeof(tree));

    if (!prepare_repres)
    {
        return BAD_ALLOC;
    }

    init_tree(prepare_repres);

    char c = '1';

    do
    {

        if (prepare_queue(instance, &c, in) != OK)
        {
            free_queue_content(instance);
            free(instance);

            free(prepare_repres);

            fclose(in);
            fclose(out);

            return INVALID;

        }

        if (instance->size)
        {

            queue_to_tree(&(prepare_repres->root), instance);

            show_tree(prepare_repres->root, out);

            fprintf(out, "\n\n");

            destr_tree(prepare_repres);
        
        }

    } while (c > 0);
    
    free(instance);

    free(prepare_repres);

    fclose(in);
    fclose(out);

    return OK;

}


EXIT_CODE prepare_queue (queue* q, char* c, FILE* in)
{

    int brackets_level = 0;
    int prev_brackets = 0;


    while ((*c = fgetc(in)) != '\n' && *c > 0)
    {

        if (*c == '(')
        {
            brackets_level++;
        }
        else if (*c == ')')
        {
            brackets_level--;
        }

        else if (!isblank(*c) && (*c != ','))
        {
            
            if (brackets_level - prev_brackets > 1)
            {
                return INVALID;
            }

            enqueue(q, *c, brackets_level);
            prev_brackets = brackets_level;

        }

    }

    if (brackets_level)
    {

        return INVALID;

    }

    return OK;

}


EXIT_CODE queue_to_tree (leaf** dest, queue* q)
{

    node_data last_added = {-1, -1};

    while (q->size)
    {

        node_data buff = dequeue(q);

        add_leaf(dest, buff, comp, &last_added);

    }

    return OK;

}







int main (int argc, char **argv) 
{

    argc = 3;
    argv[1] = "in.txt";
    argv[2] = "out.txt";

    switch (input_control(argc, argv))
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