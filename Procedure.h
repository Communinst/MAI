
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


#endif