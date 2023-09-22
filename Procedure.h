
#ifndef PROCEDURES_H
#define PROCEDURES_H


const char bound_pos[] = "9223372036854775807";

typedef struct VectorInt{
    int num_of_el;
    int* el;
    int mem_capacity;
} VectorInt;

bool InputCheck(int argc, char* argv[], long long int *temp);

void IntLenght(long long int temp, int *lenght);

void Choice(long long int temp, char key);

void HFunc(long long int temp, VectorInt *divisibles);

bool PFunc(long long int temp, VectorInt *primes);

void SFunc(long long int temp, char* string[]);

bool EFunc(long long int temp);

bool AFunc(long long int temp, long long int *result);

bool FFunc(long long int temp, long long int *result);


void CreateVector(VectorInt* v);
void Adder(VectorInt* v, int new_value);
bool Overflow(char in[],int key);

int ConverterCharTo(char s[], long long int *result);

void Sum(long long int sum_of, long long int *result);

void Factorial(long long int num, unsigned long long int *result);

void Usage();


#endif 