
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    OK = 0,
    NO_FILE,
} EXIT_CODE;


void warning ();


void usage ();


EXIT_CODE paths_handling (const char* substr, int amount, ...);


EXIT_CODE str_str (const char* substr, const char* file_name);



size_t string_length (const char* str);


int if_substr (const char* ss, FILE* in, int current, int* passed);

#endif