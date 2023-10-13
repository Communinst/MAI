
#ifndef PROCEDURE_H
#define PROCEDURE_H

typedef enum {
    
    OK = 0,
    INVALID,
    NO_FILE

} EXIT_CODE;


void warning ();


void usage ();


EXIT_CODE num_check (char* str, unsigned long int *res);


EXIT_CODE input_control (int argc, char** argv);


EXIT_CODE xor8 (char* file);

EXIT_CODE sum_up_bytes (FILE* in, unsigned long long int *res);



EXIT_CODE xor32 (char* file);

EXIT_CODE sum_up_4_bytes (FILE* in, unsigned long long int *res);



EXIT_CODE hex_mask (char* file, char* hex);

EXIT_CODE matching (FILE* in, unsigned long int *res, unsigned long int hex);

#endif