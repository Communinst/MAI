
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

#include "Procedure.h"




int main ()//int argc, char **argv) 
{

    int argc = 3;

    char *data[] = {"yes", "in.txt", "out.txt"};

    char **argv = data;

    switch(input_handle(argc, argv))
    {

        case OK:

            printf("SUCCESS!\n");
            break;

        case INVALID:

            printf("Invalid input!\n");
            break;

        case NO_FILE:

            printf("Make sure the entered file exists.\n");
            break;

        case BAD_ALLOC:

            printf("Memory fault!\n");
            break;

    }
    
    return 0;

}


EXIT_CODE free_str (int amount, ...)
{

    va_list strings;

    va_start(strings, amount);

    for (int i = 0; i < amount; i++)
    {

        void *o = va_arg(strings, void*);
        free(o);

    }

    va_end(strings);

    return OK;

}


EXIT_CODE str_to_ll (char *src, long long int *dest)
{

    char *end_ptr;

    *dest = strtol(src, &end_ptr, 10);

    return (end_ptr == src + strlen(src)) ? OK : INVALID;

}


double machine_EPS ()
{

    double machine_eps = 1;

    while (1.0 + machine_eps > 1.0)
    {
        machine_eps /= 2;

    }

    return machine_eps;

}


EXIT_CODE student_constr (Student **dest, unsigned int id, char *surname, char *name, char *group, unsigned char *grades)
{

    Student *buff = (Student *)malloc(sizeof(Student));

    buff->id = id;

    buff->surname = surname;
    buff->name = name;
    buff->group = group;

    buff->grades = grades;

    *dest = buff;

    return OK;

}


EXIT_CODE student_destr (Student **dest)
{

    (*dest)->id = 0;

    free((*dest)->surname);
    (*dest)->surname = NULL;

    free((*dest)->name);
    (*dest)->name = NULL;

    free((*dest)->group);
    (*dest)->group = NULL;

    free((*dest)->grades);
    (*dest)->grades = NULL;

    free((*dest));
    (*dest) = NULL;

    return OK;

}



EXIT_CODE init_vector (Vector_st *dest)
{

    dest->element = NULL;
    dest->stored = 0;
    dest->capacity = 0;
    dest->average_score = 0;

}


size_t size_vector (Vector_st *inst)
{

    return inst->stored;

}


EXIT_CODE append_vector (Vector_st *dest, Student *to_add)
{

    if (dest->stored == dest->capacity)
    {

        dest->capacity = ((dest->capacity + 1) * 2);

        Student **temp = (Student **)realloc(dest->element, sizeof(Student *) * dest->capacity);

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->element = temp;

    }

    *(dest->element + (dest->stored)) = to_add;

    (dest->stored)++;

    for (int i = 0; i < GRADESSIZE; i++)
    {

        dest->average_score += (to_add->grades[i]) - '0';

    }

    printf("%llf\n", dest->average_score);

    return OK;

}


EXIT_CODE display_vector (Vector_st *dest)
{

    printf("Allocated memory slots: %d\n", dest->capacity);
    printf("Occupied memory slots: %d\n", dest->stored);
    printf("Actual items stored: \n\n");

    Student **cr = dest->element;

    for (int i = 0; i < dest->stored; i++)
    {

        printf("%d %s %s %s %c %c %c %c %c\n", (*cr)->id, (*cr)->surname, (*cr)->name, (*cr)->group, (*cr)->grades[0], (*cr)->grades[1],(*cr)->grades[2],(*cr)->grades[3],(*cr)->grades[4]);

        cr++;

    }

    return OK;

}


EXIT_CODE destr_vector (Vector_st **dest)
{

    Student **crawler = (*dest)->element;
    
    while ((*dest)->stored)
    {

        student_destr(crawler);

        crawler++;

        (*dest)->stored--;

    }

    (*dest)->capacity = 0;

    free(*dest);

    *dest = NULL;

}




EXIT_CODE input_handle (int argc, char **argv)
{

    if (argc != 3)
    {
        return INVALID;
    }

    return vector_base_hub (*(argv + 1), *(argv + 2));

}


EXIT_CODE vector_base_hub (char *in_name, char *out_name)
{

    Vector_st *base = (Vector_st*)malloc(sizeof(Vector_st));

    if (!base)
    {
        return BAD_ALLOC;
    }

    init_vector(base);

    get_vector (base, in_name);
    
    display_vector(base);

    EXIT_CODE assist = dialog(base, out_name);

    destr_vector(&base);

    if (assist == EoS)
    {
        assist = OK;
    }

    return assist;

}


EXIT_CODE get_vector (Vector_st *dest, char *in_name)
{

    FILE *in_stream;

    if (file_handle(&in_stream, in_name) != OK)
    {
        return NO_FILE;
    }

    fill_vector (dest, in_stream);

    dest->average_score /= (5.0 * dest->stored);

    printf("\n%llf\n", dest->average_score);

    fclose(in_stream);


}


EXIT_CODE file_handle(FILE **in, char *in_name)
{

    *in = fopen(in_name, "r");

    if (!(*in))
    {
        return NO_FILE;
    }

    return OK;

}


EXIT_CODE fill_vector (Vector_st *dest, FILE *in)
{

    char c = 1;

    while (c > 0)
    {

        Student *buff = NULL;

        get_student_data(&buff, in, &c);

        append_vector(dest, buff);

    }

}


/*EXIT_CODE get_student_data (Student **dest, FILE *in, char *c)
{

    Student *temp = NULL;

    unsigned int id = 0;

    char *surname = NULL;

    char *name = NULL;

    char *group = NULL;

    unsigned char *grades = NULL;

    while ((*c != '\n') && *c > 0)
    {

        get_int(&id, in, c);

        get_word(&surname, in, c);
        get_word(&name, in, c);
        get_word(&group, in, c);

        get_grades(&grades, in, c);

        student_constr(&temp, id, surname, name, group, grades);
        
        id = 0;
        free_str(3, surname, name, group);
        free(grades);

    }

    *dest = temp;

    return OK;


EXIT_CODE student_constr (Student **dest, unsigned int id, char *surname, char *name, char *group, unsigned char *grades)
{

    Student *buff = (Student *)malloc(sizeof(Student));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->surname = (char*)malloc(sizeof(char) * (strlen(surname) + 1));

    if (!buff->surname)
    {
        free(buff);
        return BAD_ALLOC;
    }

    buff->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));

    if (!buff->name)
    {

        free(buff);

        free(buff->surname);

        return BAD_ALLOC;

    }

    buff->group = (char *)malloc(sizeof(char) * (strlen(group) + 1));

    if (!buff->group)
    {

        free(buff);

        free_str(2, buff->surname, buff->name);

        return BAD_ALLOC;

    }

    int cnt = GRADESSIZE;

    buff->grades = (unsigned char *)malloc(sizeof(unsigned char) * cnt);

    if (!buff->grades)
    {

        free(buff);

        free_str(3, buff->surname, buff->name, buff->group);

        return BAD_ALLOC;


    }

    buff->id = id;

    strcpy(buff->surname, surname);
    strcpy(buff->name, name);
    strcpy(buff->group, group);

    

    unsigned char *cr_src = grades;
    unsigned char *cr_dst = buff->grades;

    while (cnt--)
    {

        *cr_dst = *cr_src;

        cr_dst++;

        cr_src++;

    }


    *dest = buff;

    return OK;

}


}*/


EXIT_CODE get_student_data (Student **dest, FILE *in, char *c)
{

    Student *temp = NULL;

    unsigned int id = 0;

    char *surname = NULL;

    char *name = NULL;

    char *group = NULL;

    unsigned char *grades = NULL;

    get_int(&id, in, c);

    get_word(&surname, in, c);
    get_word(&name, in, c);
    get_word(&group, in, c);

    get_grades(&grades, in, c);

    student_constr(&temp, id, surname, name, group, grades);

    *dest = temp;

    return OK;

}


EXIT_CODE get_int (unsigned int *id, FILE *in, char *c)
{

    while ((*c = fgetc(in)) > 0 && !isspace(*c))
    {

        if (!isdigit(*c))
        {
            *id = 0;
            break;
        }
        *id *= 10;
        *id += (*c - '0');

    }

    return OK;

}


EXIT_CODE get_word (char **dest, FILE *in, char *c)
{

    char *buff = (char*)malloc(sizeof(char) * 1);

    if (!buff)
    {
        return BAD_ALLOC;
    }

    char *crawler = buff;

    *crawler = '\0';

    int amount = 0;

    while ((*c = fgetc(in)) > 0 && !isspace(*c))
    {

        if (!isalpha(*c))
        {

            *c = '#';

        }

        if (amount == strlen(buff))
        {

            char *temp = (char*)realloc(buff, sizeof(char) * (++amount * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            buff = temp;

        }

        *crawler = *c;

        crawler++;

        *crawler = '\0';

    }

    *dest = buff;

    return OK;

}


EXIT_CODE get_grades (unsigned char **dest, FILE *in, char *c)
{

    unsigned char *buff = (char*)malloc(sizeof(char) * GRADESSIZE);

    if (!buff)
    {
        return BAD_ALLOC;
    }

    int counter = GRADESSIZE;

    for (int i = 0; i < counter; i++)
    {
        buff[i] = 0;
    }

    unsigned char *crawler = buff;

    int flug = 1;

    while ((*c = fgetc(in)) > 0 && (counter) && (*c != '\n'))
    {

        if (isspace(*c))
        {
            flug = 1;
        }

        if (!isspace(*c) && flug)
        {

            if (!isdigit(*c))
            {

                *c = '0';

            }

            *crawler = *c;

            crawler++;

            flug = 0;

        }

    }

    *dest = buff;

}



EXIT_CODE dialog (Vector_st *base, char *out_name)
{

    choice_menu();


    char choice = 1;

    while (!feof(stdin))
    {

        printf("Choose required option: ");

        get_choice(&choice);

        if (choice < 0)
        {

            return INVALID_EXIT;
        }

        EXIT_CODE assist = choice_handle (choice, base, out_name);

        if (assist != OK)
        {
            return assist;
        }

    }

}


EXIT_CODE choice_menu ()
{

    printf("|---------------------------------------------------------------|\n");
    printf("|     Note any enxpected 0 value and # symbol means entered     |\n");
    printf("| data is invalid or corrupted. Check if it meets the conditions|\n");
    printf("|---------------------------------------------------------------|\n");
    printf("|               1 - sort the student collection;                |\n");
    printf("|                 2 - find particular student                   |\n");
    printf("|      3 - find student with average > base average grade       |\n");
    printf("|                        4 - display base                       |\n");
    printf("|                            0 - EXIT                           |\n");
    printf("|---------------------------------------------------------------|\n");

}


EXIT_CODE get_choice (char *c)
{

    *c = getchar();

    fflush(stdin);

}


EXIT_CODE choice_handle (char choice, Vector_st *base, char *out_name)
{

    switch (choice)
    {
        case '1':

            return sort_vector(base);

        case '2':

            return find_student(base, out_name);

        case '3':

            double EPS = machine_EPS();

            above_average(base, out_name, EPS);

            break;
        
        case '4':

            display_vector(base);
            break;

        case '0':

            return EoS;

        default:

            break;
    }

    return OK;

}


EXIT_CODE sort_vector (Vector_st *dest)
{

    sort_find_menu();

    char choice;

    printf("Choose the oprion to sort: ");

    get_choice(&choice);

    if (choice < 0)
    {
        return INVALID_EXIT;
    }

    switch (choice)
    {
        case 'i':

            qsort(dest->element, dest->stored, sizeof(Student *), id_cmp);
            break;

        case 's':

            qsort(dest->element, dest->stored, sizeof(Student *), surname_cmp);
            break;

        case 'n':

            qsort(dest->element, dest->stored, sizeof(Student *), name_cmp);
            break;

        case 'g':

            qsort(dest->element, dest->stored, sizeof(Student *), group_cmp);
            break;
        
        case 'b':

            return OK;

        default:

            break;

    }

    return OK;

}


EXIT_CODE sort_find_menu ()
{

    printf("|---------------------------------------------------------------|\n");
    printf("|                   i - sort/find by id;                        |\n");
    printf("|                 s - sort/find by surname;                     |\n");
    printf("|                  n - sort/find by name;                       |\n");
    printf("|                  g - sort/find by group;                      |\n");
    printf("|                           b - back;                           |\n");
    printf("|---------------------------------------------------------------|\n");

}


int id_cmp (const void *v1, const void *v2)
{

    const Student **s1 = (const Student **)v1;
    const Student **s2 = (const Student **)v2;

    return (*s1)->id - (*s2)->id;

}


int surname_cmp (void const *v1, void const *v2)
{

    const Student **s1 = (const Student **)v1;    
    const Student **s2 = (const Student **)v2;

    return strcmp((*s1)->surname, (*s2)->surname);

}


int name_cmp (void const *v1, void const *v2)
{

    const Student **s1 = (const Student **)v1;
    const Student **s2 = (const Student **)v2;

    return strcmp((*s1)->name, (*s2)->name);

}


int group_cmp (void const *v1, void const *v2)
{

    const Student **s1 = (const Student **)v1;
    const Student **s2 = (const Student **)v2;

    return strcmp((*s1)->group, (*s1)->group);

}



EXIT_CODE find_student (Vector_st *base, char *out_name)
{

    sort_find_menu();

    char *to_find;

    char c = 1;

    printf("\nEnter the value to search by: ");

    get_word_stdin(&to_find, &c);

    if (c < 0)
    {
        free(to_find);
        return INVALID_EXIT;
    }

    printf("\nSelect an option to search: ");

    get_choice(&c);

    if (c < 0)
    {
        free(to_find);
        return INVALID_EXIT;
    }

    return find_handle(base, c, &to_find, out_name);

}


EXIT_CODE get_word_stdin (char **dest, char *c)
{

    char *buff = (char*)malloc(sizeof(char) * 1);

    if (!buff)
    {
        return BAD_ALLOC;
    }

    *buff = '\0';

    int amount = 0;

    while ((*c = getchar()) > 0 && *c != '\n')
    {

        if (amount == strlen(buff))
        {

            char *temp = (char*)realloc(buff ,sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            buff = temp;

        }

        *(buff + amount) = *c;

        *(buff + (++amount)) = '\0';

    }

    *dest = buff;

    return OK;

}



EXIT_CODE find_handle (Vector_st *base, char choice, char **to_find, char *out_name)
{

    switch(choice)
    {

        case 'i':

            id_find(base, *to_find, out_name);
            break;
        
        case 's':

            surname_find(base, *to_find, out_name);
            break;
        
        case 'n':

            name_find(base, *to_find, out_name);
            break;

        case 'g':

            group_find(base, *to_find, out_name);
            break;

        default:

            break;

    }

    free(*to_find);

    *to_find = NULL;

    return OK;

}


EXIT_CODE id_find (Vector_st *base, char *to_find, char *out_name)
{

    FILE *trace = fopen(out_name, "w");

    if (!trace)
    {
        return NO_FILE;
    } 

    long long int id;
    
    if (str_to_ll(to_find, &id) != OK)
    {

        printf("Done!\n");

        fclose(trace);

        return OK;

    }

    Student **crawler = base->element;

    for (int i = 0; i < base->stored; i++)
    {

        if (id == (*crawler)->id)
        {
            fprintf(trace, "id %lld: %s %s %s %llf\n", id, (*crawler)->surname, (*crawler)->name, (*crawler)->group, (((*crawler)->grades[0] + (*crawler)->grades[1] + (*crawler)->grades[2] + (*crawler)->grades[3] + (*crawler)->grades[4] - ('0' * 5)) / 5.0));
        }

        crawler++;

    }

    printf("Done!\n");

    fclose(trace);

    return OK;

}


EXIT_CODE surname_find (Vector_st *base, char *to_find, char *out_name)
{

    FILE *trace = fopen(out_name, "w");

    if (!trace)
    {
        return NO_FILE;
    } 

    Student **crawler = base->element;

    for (int i = 0; i < base->stored; i++)
    {

        if (!strcmp(to_find, (*crawler)->surname))
        {
            fprintf(trace, "%u %s %s %s %c %c %c %c %c\n", (*crawler)->id, (*crawler)->surname, (*crawler)->name, (*crawler)->group, (*crawler)->grades[0], (*crawler)->grades[1], (*crawler)->grades[2], (*crawler)->grades[3], (*crawler)->grades[4]);
        }

        crawler++;

    }

    printf("Done!\n");

    fclose(trace);

    return OK;

}


EXIT_CODE name_find (Vector_st *base, char *to_find, char *out_name)
{

    FILE *trace = fopen(out_name, "w");

    if (!trace)
    {
        return NO_FILE;
    } 

    Student **crawler = base->element;

    for (int i = 0; i < base->stored; i++)
    {

        if (!strcmp(to_find, (*crawler)->name))
        {
            fprintf(trace, "%u %s %s %s %c %c %c %c %c\n", (*crawler)->id, (*crawler)->surname, (*crawler)->name, (*crawler)->group, (*crawler)->grades[0], (*crawler)->grades[1], (*crawler)->grades[2], (*crawler)->grades[3], (*crawler)->grades[4]);
        }

        crawler++;

    }

    printf("Done!\n");

    fclose(trace);

    return OK;

}


EXIT_CODE group_find (Vector_st *base, char *to_find, char *out_name)
{

    FILE *trace = fopen(out_name, "w");

    if (!trace)
    {
        return NO_FILE;
    } 

    Student **crawler = base->element;

    for (int i = 0; i < base->stored; i++)
    {

        if (!strcmp(to_find, (*crawler)->group))
        {
            fprintf(trace, "%u %s %s %s %c %c %c %c %c\n", (*crawler)->id, (*crawler)->surname, (*crawler)->name, (*crawler)->group, (*crawler)->grades[0], (*crawler)->grades[1], (*crawler)->grades[2], (*crawler)->grades[3], (*crawler)->grades[4]);
        }

        crawler++;

    }

    printf("Done!\n");

    fclose(trace);

    return OK;

}



EXIT_CODE above_average (Vector_st *base, char *out_name, double EPS)
{

    FILE *trace = fopen(out_name, "w");

    if (!trace)
    {
        return NO_FILE;
    }

    Student **crawler = base->element;

    for (int i = 0; i < base->stored; i++)
    {

        double av = ((*crawler)->grades[0] + (*crawler)->grades[1] + (*crawler)->grades[2] + (*crawler)->grades[3] + (*crawler)->grades[4] - ('0' * 5)) / 5.0;

        if (av - base->average_score >= EPS)
        {

            fprintf(trace, "Average of %s %s (id: %u) is: %llf\n", (*crawler)->surname, (*crawler)->name, (*crawler)->id, av);

        }

        crawler++;

    }

    printf("Done!\n");

    fclose(trace);

    return OK;



}

