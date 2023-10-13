
#ifndef PROCEDURES_H
#define PROCEDURES_H



typedef enum 
{

    OK,
    INVALID,
    NO_FILE,
    FILE_ERROR,

} EXIT_CODE;



void usage();



EXIT_CODE input_check (int argc, char** argv);

EXIT_CODE file_handling (char* file_name);

EXIT_CODE print_all_file (FILE* in);

EXIT_CODE acq_req_bytes (FILE* in, char** res);

void print_bytes (char* bytes);

#endif 