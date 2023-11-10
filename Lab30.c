
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


EXIT_CODE add_leaf (leaf** root, node_data data, int (*comp)(int level1, int level2))
{

    


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

    char c = '1';

    do
    {

        prepare_queue(instance, &c, in);

        


    } while (c > 0);
    
    free(instance);

    fclose(in);
    fclose(out);

    return OK;

}


EXIT_CODE prepare_queue (queue* q, char* c, FILE* in)
{

    int brackets_level = 0;

    while ((*c = fgetc(in)) != '\n' && *c > 0)
    {

        printf("%c", *c);

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
            enqueue(q, *c, brackets_level);
        }

    }

    return OK;

}



int main (int argc, char **argv) 
{

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