
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "Procedure.h"





int main ()//int argc, char** argv)
{

    srand(time(NULL));

    int argc = 4;
    
    char* data[] = {"yes", "in1.txt", "in2.txt", "in3.txt"};

    char** argv = data;

    switch (input_handle(argc, argv))
    {

        case OK:

            printf("Success!\n");
            break;

        case INVALID:

            printf("Invalid input!\n");
            break;

        case NO_FILE:

            printf("File is out!\n");
            break;

        case ZERO_DIVISION:

            printf("Zero division op!\n");
            break;

        case UNCERTAINTY:

            printf("Indefinite op!\n");
            break;

        case BRCKTS_DISBALANCE:

            printf("Brackets disbalance!\n");
            break;

        default:
            break;

    }

    return 0;

}




EXIT_CODE string_init (string** dest)
{

    string* buff = (string*)malloc(sizeof(string));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->word = (char*)malloc(sizeof(char) * 1);

    if (!buff->word)
    {
        return BAD_ALLOC;
    }

    buff->word[0] = '\0';

    buff->allocated = 1;
    buff->occupied = 0;
    

    *dest = buff;

    return OK;

}


EXIT_CODE string_append (string* dest, char to_add)
{

    if (dest->allocated == dest->occupied + 1)
    {

        dest->allocated = (dest->allocated + 1) * 2;

        char* temp = (char*)realloc(dest->word, sizeof(char) * dest->allocated);

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->word = temp;

    }

    *(dest->word + dest->occupied) = to_add;

    dest->occupied++;

    *(dest->word + dest->occupied) = '\0';

    return OK;

}


EXIT_CODE string_dest (string** dest)
{

    free((*dest)->word);
    (*dest)->word = NULL;

    (*dest)->allocated = 0;

    (*dest)->occupied = 0;

    free((*dest));
    (*dest) = NULL;

    return OK;

}



EXIT_CODE expr_constr (expression** dest, unsigned int order, char* raw, char* polish, int value)
{

    expression* buff = (expression*)malloc(sizeof(expression));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->raw_expr = (char*)malloc(sizeof(char) * (strlen(raw) + 1));

    if (!buff->raw_expr) 
    {
        free(buff);
        return BAD_ALLOC;
    }


    if (polish)
    {

        buff->rev_polish = (char*)malloc(sizeof(char) * (strlen(polish) + 1));

        if (!buff->rev_polish) 
        {

            free(buff->raw_expr);

            free(buff);

            return BAD_ALLOC;

        }

        strcpy(buff->rev_polish, polish);

    }

    else
    {
        buff->rev_polish = NULL;
    }
    
    buff->order = order;

    strcpy(buff->raw_expr, raw);

    buff->value = value;

    *dest = buff;

    return OK;

}


EXIT_CODE expr_destr (expression** src)
{

    (*src)->order = 0;

    (*src)->value = 0;

    free((*src)->raw_expr);
    (*src)->raw_expr = NULL;

    free((*src)->rev_polish);
    (*src)->rev_polish = NULL;

    free((*src));
    (*src) = NULL;

    return OK;

}




EXIT_CODE fs_init (file_stuff** dest, char* filename)
{

    file_stuff* buff = (file_stuff*)malloc(sizeof(file_stuff));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->filename = (char*)malloc(sizeof(char) * (strlen(filename) + 1));
    
    if (!buff->filename)
    {
        free(buff);
        return BAD_ALLOC;
    }
    
    strcpy(buff->filename, filename);

    buff->occupied = 0;

    buff->allocated = 0;

    buff->data = NULL;

    *dest = buff;

    return OK;

}


EXIT_CODE fs_append (file_stuff* dest, expression* to_add)
{

    if (dest->allocated == dest->occupied)
    {

        dest->allocated += 1;
        dest->allocated *= 2;

        expression** temp = (expression**)realloc(dest->data, sizeof(expression*) * (dest->allocated));
        
        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->data = temp;

    }

    *(dest->data + dest->occupied) = to_add;

    (dest->occupied)++;

    return OK;

}


EXIT_CODE fs_display (file_stuff* src)
{

    expression** cr = src->data;

    for (int i = 0; i < src->occupied; i++)
    {

        printf("Order %u:\nRaw: %s\nPolish: %s\nValue: %d\n\n", (*cr)->order, (*cr)->raw_expr, (*cr)->rev_polish, (*cr)->value);

        cr++;

    }

    return OK;

}


EXIT_CODE fs_destr (file_stuff** src)
{

    free((*src)->filename);

    expression** cr = (*src)->data;

    while ((*src)->occupied--)
    {

        expr_destr (&(*cr));

        cr++;

    }

    (*src)->allocated = 0;

    free((*src));

    return OK;

}



EXIT_CODE vec_init (vec_file** dest)
{

    vec_file* buff = (vec_file*)malloc(sizeof(vec_file));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->occupied = 0;
    buff->allocated = 0;
    buff->elem = NULL;

    *dest = buff;

    return OK;

}


EXIT_CODE vec_append (vec_file* dest, file_stuff* to_add)
{

    if (dest->occupied == dest->allocated)
    {

        dest->allocated += 1;

        dest->allocated *= 2;

        file_stuff** temp = (file_stuff**)realloc(dest->elem, sizeof(file_stuff*) * dest->allocated);

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->elem = temp;

    }

    *(dest->elem + dest->occupied) = to_add;

    dest->occupied++;

    return OK;

}


EXIT_CODE vec_display (vec_file* src)
{

    file_stuff** cr = src->elem;
    
    for (int i = 0; i < src->occupied; i++)
    {

        printf("%s:\n", (*cr)->filename);

        fs_display(*cr);

        cr++;

    }

    return OK;

}


EXIT_CODE vec_destr (vec_file** src)
{

    file_stuff** cr = (*src)->elem;

    while ((*src)->occupied--)
    {

        fs_destr(&(*cr));

        cr++;

    }

    (*src)->allocated = 0;

    free((*src));

    return OK;

}



EXIT_CODE stack_init (stack** dest)
{

    stack* buff = (stack*)malloc(sizeof(stack));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->head = NULL;

    *dest = buff;

    return OK;

}


EXIT_CODE push (stack* dest, int op, int item)
{

    node* new = (node*)malloc(sizeof(node));

    if (!new)
    {
        return BAD_ALLOC;
    }

    new->op = item;
    new->data = op;
    new->next = dest->head;

    dest->head = new;

    return OK;

}


char pop (stack* src)
{

    node* temp = src->head;

    src->head = src->head->next;

    char res = temp->op;

    temp->op = 0;

    temp->data = 0;

    temp->next = NULL;

    free(temp);

    return res;

}


int is_stack_empty (stack* src)
{
    return src->head == NULL;
}


EXIT_CODE stack_destr (stack** dest)
{

    while (!is_stack_empty(*dest))
    {
        pop(*dest);
    }

    free(*dest);
     
    *dest = NULL;

    return OK;

}



EXIT_CODE queue_init (queue** dest)
{

    queue* buff = (queue*)malloc(sizeof(queue));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->size = 0;

    buff->front = NULL;

    buff->rear = NULL;

    *dest = buff;

    return OK;

}


int is_queue_empty (queue* src)
{

    return src->size;

}


EXIT_CODE enqueue (queue* dest, int op, int data)
{

    queue_node* new = (queue_node*)malloc(sizeof(queue_node));

    if (!new)
    {
        return BAD_ALLOC;
    }

    new->data = data;
    new->op = op;
    new->next = NULL;

    if (is_queue_empty(dest))
    {
        dest->rear->next = new;
        dest->rear = new;
    }

    else 
    {

        dest->front = new;
        dest->rear = new;

    }

    dest->size++;

    return OK;

}


queue_node* dequeue (queue* src)
{

    queue_node* temp = src->front;

    src->front = temp->next;

    src->size--;

    return temp;

}


EXIT_CODE queue_destr (queue** dest)
{

    while (is_queue_empty(*dest))
    {

        queue_node* temp = dequeue(*dest);

        free(temp);

    }

    (*dest)->front = NULL;

    (*dest)->rear = NULL;

    free(*dest);

    return OK;

}




EXIT_CODE input_handle (int argc, char** argv)
{

    if (argc < 2)
    {
        return INVALID;
    }

    return prepare_output((argc - 1), argv + 1);

}



EXIT_CODE prepare_output (int argc, char** argv)
{

    printf("%s %s\n", *(argv), *(argv + 1));

    vec_file* vec = NULL;

    EXIT_CODE assist = vec_init(&vec);

    if (assist)
    {
        return assist;
    }

    assist = files_count(argc, argv, vec);

    if (assist)
    {

        vec_destr(&vec);

        return assist;

    }

    vec_display(vec);

    vec_destr(&vec);

    return OK;

}


EXIT_CODE files_count (int argc, char** argv, vec_file* vec)
{   

    EXIT_CODE assist;

    char** cr = argv;

    while (argc--)
    {

        file_stuff* fsd = NULL;

        assist = fs_init(&fsd, *cr);

        if (assist)
        {
            return assist;
        }

        file_handle(*cr, fsd);

        cr++;

        vec_append(vec, fsd);

    }

    return OK;

}


EXIT_CODE file_handle (char* filename, file_stuff* fsd)
{

    EXIT_CODE assist;

    FILE* src = NULL;

    assist = is_file_proper(&src, filename);

    return assist ? assist : data_handle(&src, fsd);

}


EXIT_CODE is_file_proper (FILE** dest, char* src)
{

    FILE* buff = fopen(src, "r");

    if (!buff)
    {
        return NO_FILE;
    }

    *dest = buff;

    return OK;

}


EXIT_CODE data_handle (FILE** src, file_stuff* fsd)
{

    EXIT_CODE assist;

    FILE* error_file = NULL;

    char c = 1;

    unsigned int order = 0;

    while (c > 0)
    {

        expression* expr = NULL;

        assist = get_expr(&expr, order, *src, &c);

        if (assist)
        {

            record_error(&error_file, expr, assist);

        }

        else 
        {
            fs_append(fsd, expr);
        }

        order++;

    }

    if (error_file)
    {
        fclose(error_file);
    }

    fclose(*src);

    return OK;


}


EXIT_CODE record_error (FILE** dest, expression* src, EXIT_CODE info)
{

    if (!(*dest))
    {

        create_rand_file(dest);

    }

    switch (info)
    {

        case BRCKTS_DISBALANCE:

            fprintf((*dest), "Order: %u\nInstance: %s\nError code: Brackets disbalance.\n\n", src->order, src->raw_expr);
            break;

        case ZERO_DIVISION:

            fprintf((*dest), "Order: %u\nInstance: %s\nError code: Zero division operation.\n\n", src->order, src->raw_expr);
            break;

        case UNCERTAINTY:

            fprintf((*dest), "Order: %u\nInstance: %s\nError code: Mathematical uncertainty.\n\n", src->order, src->raw_expr);
            break;

        case INVALID:
            fprintf((*dest), "Order: %u\nInstance: %s\nError code: Invalid instance.\n\n", src->order, src->raw_expr);
            break;

    }

    return OK;

}


EXIT_CODE create_rand_file (FILE** dest)
{

    char* filename;

    get_name(&filename);

    printf("\n%s\n", filename);

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

        printf("%d! ", gay);

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



EXIT_CODE get_expr(expression** dest, unsigned int order, FILE* src, char* c)
{

    EXIT_CODE assist = OK;

    string* raw = NULL;

    string_init(&raw);

    assist = get_raw(raw, src, c); //if brackets are correct

    if (assist)
    {

        expr_constr(dest, order, raw->word, NULL, 0);

        string_dest(&raw);

        return assist;
    }


    string* polish = NULL;

    string_init(&polish);


    queue* calc = NULL;


    get_polish(polish, &calc, raw->word);
    

    int value = 0;


    assist = (calc->size <= 3) ? INVALID : assist;

    assist = assist ? assist : calc_polish(&value, calc);

    if (assist)
    {

        expr_constr(dest, order, raw->word, NULL, 0);

        string_dest(&raw);

        string_dest(&polish);

        queue_destr(&calc);

        return assist;

    }

    queue_destr(&calc);


    expr_constr(dest, order, raw->word, polish->word, value);


    string_dest(&raw);
    string_dest(&polish);

    return OK;

}


EXIT_CODE get_raw (string* dest, FILE* src, char* c)
{

    int brackets_cnt = 0;

    while ((*c = fgetc(src)) != '\n' && *c > 0)
    {

        if (*c == '(')
        {
            brackets_cnt++;
        }

        else if (*c == ')')
        {
            brackets_cnt--;
        }

        string_append(dest, *c);
    }

    if (brackets_cnt)
    {
        return BRCKTS_DISBALANCE;
    }

    return OK;

}


EXIT_CODE get_polish (string* dest, queue** q, char* src)
{

    EXIT_CODE assist = OK;


    stack* ops = NULL;

    stack_init(&ops);


    queue* calc = NULL;

    queue_init(&calc);


    int is_brackets = 0;

    int number = 0;


    char* cr = src;

    while (*cr != '\0')
    {

        assist = polish_handle(dest, ops, calc, &number, *cr, &is_brackets, &assist);

        cr++;

    }

    assist = is_brackets ? INVALID : assist;

    if (assist == COMMITTED)
    {
        enqueue(calc, 0, number);
        assist = OK;
    }

    while (!is_stack_empty(ops) && !assist)
    {

        char bff = pop(ops);

        string_append(dest, bff);

        enqueue(calc, 1, bff);

    }

    stack_destr(&ops);

    *q = calc;

    return assist;

}


EXIT_CODE polish_handle (string* dest, stack* ops, queue* calc, int* n, char c, int* is_bracket, EXIT_CODE *assist)
{

    

    if (isdigit(c))
    {

        string_append(dest, c);

        *n *= 10;
        *n += c - '0';

        return COMMITTED;

    }

    if (*assist == COMMITTED)
    {
        enqueue(calc, 0, *n);
        *n = 0;
    }

    if (c == '(')
    {

        (*is_bracket)++;

        push(ops, 1, c);

    }

    else if (c == ')')
    {

        if (!is_stack_empty(ops))
        {
            while (ops->head->op != '(')
            {
                char bff = pop(ops);

                string_append(dest, bff);

                enqueue(calc, 1, bff);
            }

            pop(ops);

            (*is_bracket)--;

        }

    }

    else if (!(*is_bracket))
    {

        while (!is_stack_empty(ops) && priority(ops->head->op) >= priority(c))
        {

            char bff = pop(ops);

            string_append(dest, bff);

            enqueue(calc, 1, bff);

        }
        
        push(ops, 1, c);

    }

    else 
    {
        push(ops, 1, c);
    }


    return OK;

}


int priority (char c)
{

    switch (c)
    {

        case '+':
            return 2;

        case '-':
            return 2;

        case '*':
            return 3;

        case '/':
            return 3;

        case '%':
            return 3;

        case '^':
            return 3;

        default:
            return 0;

    }

}


EXIT_CODE calc_polish (int* res, queue* src)
{

    EXIT_CODE assist = OK;

    stack* buff = NULL;

    stack_init(&buff);

    int temp = 0;

    queue_node* cr = NULL;

    while (is_queue_empty(src))
    {

        cr = dequeue(src);

        if (cr->op)
        {
            assist = execute_op(&temp, buff, cr->data);

            if (assist)
            {

                stack_destr(&buff);

                return assist;
                
            }

            push(buff, 0, temp);
        }

        else 
        {
            push(buff, 0, cr->data);
        }

    }

    *res = pop(buff);

    stack_destr(&buff);

    return OK;

}


EXIT_CODE execute_op (int* res, stack* src, char c)
{
    if (is_stack_empty(src) || !src->head->next || src->head->data || src->head->next->data)
    {
        return INVALID;
    }

    int val2 = pop(src);

    int val1 = pop(src);

    switch (c)
    {
        case '+':

            *res = val1 + val2;
            break;
        
        case '-':

            *res = val1 - val2;
            break;

        case '*':

            *res = val1 * val2;
            break;

        case '/':

            if (!val2)
            {
                return ZERO_DIVISION;
            }

            *res = val1 / val2;
            break;

        case '%':

            if (!val2)
            {
                return ZERO_DIVISION;
            }

            *res = val1 % val2;
            break;

        case '^':

            if (!val1 && !val2)
            {
                return UNCERTAINTY;
            }

            *res = pow(val1, val2);
            break;

        default:
            return INVALID;
    }

    return OK;


}

