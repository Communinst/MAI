
#ifndef PROCEDURE_H
#define PROCEDURE_H


typedef long long int ll;


typedef enum
{

    OK = 0,

    INVALID,

    NO_FILE,

    BAD_ALLOC,

    NONE,

    APPEND,

} EXIT_CODE;


typedef enum
{

    ASSIGN = 0,

    PLUS,

    MINUS,

    MULTIPLICITY,

    DIVISION,

    MODULUS,

    NEXT,

    SKIP,

    END,

    DEFAULT,


} OPERATION;




typedef struct
{

    char* name;

    ll value;

} memory_cell;




typedef struct
{

    ll occupied;

    ll allocated;

    memory_cell** cells;

} memory_vec;




EXIT_CODE cell_constr (memory_cell** dest, char* name, ll value);


EXIT_CODE cell_destr (memory_cell** dest);



EXIT_CODE vec_init (memory_vec** dest);


EXIT_CODE vec_append (memory_vec* dest, memory_cell* to_add);


int lex_cmp (const void* v1, const void* v2);


EXIT_CODE vec_display (memory_vec* src);


EXIT_CODE vec_destr (memory_vec** dest);



EXIT_CODE input_handle (int argc, char** argv);


EXIT_CODE data_handle (char* filename);


EXIT_CODE file_handle (char* src, FILE** dest);


EXIT_CODE memory_hub (FILE* src);


EXIT_CODE fill_vec (memory_vec* dest, FILE* src);


EXIT_CODE get_cell (memory_cell** dest, memory_vec* base, FILE* src, char* c);


EXIT_CODE get_variable (char** dest, FILE* src, char* c);


OPERATION op_handle (char c);


EXIT_CODE check_op (ll* value, FILE* in, char* c, memory_vec* base);


EXIT_CODE fill_instr(ll* value, FILE* src, char* c, memory_vec* base);



EXIT_CODE identify_var (char* str, ll* dest, memory_vec* base);


EXIT_CODE is_num(char* name, ll* dest);


EXIT_CODE dichotomy_take (memory_vec* base, ll* dest, char* name);


EXIT_CODE dichotomy_rewrite (memory_vec* base, ll value, char* name);


EXIT_CODE execute_op (OPERATION op, ll v1, ll v2, ll* res);



EXIT_CODE fill_print(FILE* src, char* c, memory_vec* base);





#endif