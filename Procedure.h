
#ifndef _PROCEDURE_H_
#define _PROCEDURE_H_


typedef enum
{

    OK = 0,

    INVALID_ARGC,
    INVALID_ARGV,

    BAD_ALLOC,

    NO_FILE,

    PRESENCE,
    ABSENCE,

    PROCESS_CREATE_FAIL,

} EXIT_CODE;


typedef struct
{

    size_t allocated;
    size_t occupied;

    char* word;

} String;




void EC_handle (EXIT_CODE c);



EXIT_CODE string_init (String **dest);


EXIT_CODE string_append (String *dest, char to_add);


EXIT_CODE purge_str (String *dest);


void string_destr (String **dest);






EXIT_CODE input_handle (int argc, char **argv);



EXIT_CODE processing (FILE *input, char *to_find);


EXIT_CODE file_proper (FILE **dest, char *src);


EXIT_CODE get_path (String *dest, char *c, FILE *src);


EXIT_CODE search_str (FILE *src, char *to_find);


EXIT_CODE left_shift (String *dest);





#endif