#ifndef PROCEDURES_H
#define PROCEDURES_H


typedef enum 
{

    OK,
    INVALID,
    NO_FILE,

} EXIT_CODE;


void usage();


EXIT_CODE input_check (int argc, char** argv);


EXIT_CODE file_cpy (char* in_name, char* out_name);

#endif 