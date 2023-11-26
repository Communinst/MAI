
#ifndef PROCEDURE_H
#define PROCEDURE_H

#define GRADESSIZE 5

typedef enum 
{

    OK = 0,

    INVALID,

    BAD_ALLOC,

    NO_FILE,

    EoS,

    INVALID_EXIT,

} EXIT_CODE;



typedef struct
{

    unsigned int id;
    
    char *surname;

    char *name;

    char *group;

    unsigned char *grades;

} Student;


typedef struct
{

    Student **element;

    size_t stored;

    size_t capacity;

    double average_score;

} Vector_st;



EXIT_CODE free_str (int amount, ...);


EXIT_CODE str_to_ll (char *src, long long int *dest);


double machine_EPS ();



EXIT_CODE student_constr (Student **dest, unsigned int id, char *surname, char *name, char *group, unsigned char *grades);


EXIT_CODE student_destr (Student **dest);


EXIT_CODE init_vector (Vector_st *dest);


size_t size_vector (Vector_st *inst);


EXIT_CODE append_vector (Vector_st *dest, Student *to_add);



EXIT_CODE input_handle (int argc, char **argv);


EXIT_CODE vector_base_hub (char *in_name, char *out_name);


EXIT_CODE get_vector (Vector_st *dest, char *in_name);


EXIT_CODE file_handle(FILE **in, char *in_name);


EXIT_CODE fill_vector (Vector_st *dest, FILE *in);


EXIT_CODE get_student_data (Student **dest, FILE *in, char *c);


EXIT_CODE get_int (unsigned int *id, FILE *in, char *c);


EXIT_CODE get_word (char **dest, FILE *in, char *c);


EXIT_CODE get_grades (unsigned char **dest, FILE *in, char *c);



EXIT_CODE dialog (Vector_st *base, char *out_name);


EXIT_CODE choice_menu ();


EXIT_CODE get_choice (char *c);


EXIT_CODE choice_handle (char choice, Vector_st *base, char *out_name);


EXIT_CODE sort_vector (Vector_st *dest);


EXIT_CODE sort_find_menu();


int id_cmp (void const *v1, void const *v2);


int surname_cmp (void const *v1, void const *v2);


int name_cmp (void const *v1, void const *v2);


int group_cmp (void const *v1, void const *v2);



EXIT_CODE find_student (Vector_st *base, char *out_name);


EXIT_CODE get_word_stdin (char **dest, char *c);


EXIT_CODE find_handle (Vector_st *base, char choice, char **to_find, char *out_name);


EXIT_CODE id_find (Vector_st *base, char *to_find, char *out_name);


EXIT_CODE surname_find (Vector_st *base, char *to_find, char *out_name);


EXIT_CODE name_find (Vector_st *base, char *to_find, char *out_name);


EXIT_CODE group_find (Vector_st *base, char *to_find, char *out_name);


EXIT_CODE above_average (Vector_st *base, char *out_name, double EPS);


#endif