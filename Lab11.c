#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"

bool InputCheck(int argc, char* argv[], long long int *temp) {
    if (argc != 3 || (*argv[2] != '-' && *argv[2] != '/') || (strlen(argv[2]) != 2)) {
        return true;
    }
    return ConverterCharTo(argv[1], temp);
}

void CreateVector(VectorInt* v) {
    v->num_of_el = 0;
    v->el = NULL;
    v->mem_capacity = 0;
}

bool IfEmptyVector(VectorInt* v) {
    return v->num_of_el; 
}

int Adder(VectorInt *v, int new_value)
{
    if (v->mem_capacity == v->num_of_el)
    {
        v->mem_capacity *= 2;
        int *temp = (int*)realloc(v->el, sizeof(int) * v->mem_capacity);

        if (!temp)
        {
            return 1;
        }
        
        v->el = temp;
    }

    v->el[v->num_of_el++] = new_value;
    
    return 0;
}

void VectorPrint(VectorInt* v) {
    int i = 0;
    while (i != v->num_of_el) {
        printf("%d ", v->el[i]);
        i++;
    }
}

void Terminate(VectorInt* v) {
    v->mem_capacity = 0;
    v->num_of_el = 0;
    v->el = NULL;
    free(v);
}

bool Overflow(char in[],int key) {
    bool eq = true;
    if (!key) {
        for (int i = 0; i < 19; i++) {
            if (in[i] > bound_pos[i] && eq) {
                return true;
            }
            if (in[i] < bound_pos[i]) {
                eq = false;
            }
        }
        return false;
    }
    for (int i = 0; i < 19; i++) {
        if (in[i + 1] > bound_pos[i] && eq) {
            return true;
        }
        if (in[i] < bound_pos[i]) {
            eq = false;
        }
    }
    return false;
}

int ConverterCharTo(char s[], long long int *result) {
    int Length = strlen(s);
    int mantis = 0;
    int count = 0;
    
    if (s[0] == '-') { 
        if (Length > 20 || (Length == 20 && Overflow(s, 1))) {
            return 1;
        }
        for(int i = 1; i < Length; i++) {
            if (s[i] < '0' || s[i] > '9') {
                return 2;
            }
            *result = *result * 10 + (s[i] - '0');
        }
        *result *= -1;
        return 0;
    }
    if (Length > 19 || (Length == 19 && Overflow(s, 0))) {
            return 1;
    }
    for(int i = 0; i < Length; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return 2;
        }
        *result = *result * 10 + (s[i] - '0');
    }

    return 0;
}

void Sum(long long int sum_of, long long int *result) {
    if (sum_of == 0) {
        return;
    }
    Sum(sum_of - 1, result);
    *result += sum_of;
}

void Factorial(long long int num, unsigned long long int *result) {
    if (num < 2) 
        return;
    Factorial(num - 1, result);
    *result *= num;
}

void IntLength(long long int temp, int *Length) {
    long long int buff = llabs(temp);
    while (buff > 0) {
        buff /= 10;
        *Length += 1;
    }
}

void prepareTable(int table[10][10], long long int number) {
    int x = 0;
    for (int i = 0; i < 10; i++) {
        x = (i + 1);
        for (int j = 0; j < number; j++) {
            table[i][j] = x;
            x *= (i + 1);
        }
    }
}

void Choice(long long int temp, char key) {
    if (key == 'h') {
        VectorInt divisibles;
        CreateVector(&divisibles);
        HFunc(temp, &divisibles);
        VectorPrint(&divisibles);
        Terminate(&divisibles);
    }
    else if (key == 'p') {
        VectorInt primes;
        CreateVector(&primes);
        if (PFunc(temp, &primes)){
            if (primes.el[primes.num_of_el - 1] == temp) {
                printf("%lld is prime", temp);
            }
            else {printf("%lld is compound", temp);}
            Terminate(&primes);
        }
    }
    else if (key == 's') {
        char *string = (char*)malloc(1);
        string[0] = '\0';
        SFunc(temp, &string);
        printf("%s", string);
        free(string);
    }
    else if (key == 'e') {
        if (!EFunc(temp)) {
            printf("Sorry, it seems entered value exceeded the allowed values: (-1) - (10)");
        }
    }
    else if (key == 'a') {
        long long int result = 0;
        if (AFunc(temp, &result)) {
            printf("%lld", result);
        }
        else {
            printf("Sorry, it seems entered value exceeded the allowed values: range of naturals");
        }    
    }
    else if (key == 'f') {
        long long int result = 1;
        if (FFunc(temp, &result)) {
            printf("%lld", result);
        }    
        else {
            printf("Sorry, it seems entered value exceeded the allowed values: 1 - 20");
        }
    }

}

void HFunc(long long int temp, VectorInt *divisibles) {
    if (temp <= 0 || temp > 100) {
        printf("It seems there're not any divisible by %lld numbers", temp);
    }
    else {
        for (long long int i = temp; i <= 100; i++) {
            if (i % temp == 0) {
                if (Adder(divisibles, i)) {
                    printf("Bad allocation");
                    return;
                }
                
            }
        }
        if (!(divisibles->num_of_el)) {
            printf("It seems there're not any divisible by %lld numbers", temp);
        }
    }
}

bool PFunc(long long int temp, VectorInt *primes) {
    if (temp <= 0) {
        printf("Primes list starts with 2, but %lld < 2", temp);
        return false;
    }
    long long int num = 2;
    while(num <= temp) {
        bool flag = 1;
        if (IfEmptyVector(primes)) {
            for(int i = 0; i < primes->num_of_el; i++) {
                if (num % primes->el[i] == 0) {
                    //printf("%d", primes->el[i]);
                    flag = 0;
                    break;
                }
            }
        }   
        //printf("murder");
        if (flag) {
            if (Adder(primes, num)) {
                printf("Bad allocation");
                return false;
            }
        }
        num++;
    }
    return true;
}

void SFunc(long long int temp, char *string[]) {
    int Length = 0;
    IntLength(temp, &Length);
    long long int buff = llabs(temp);
    char *tmp = (char*)malloc(Length*2);
    tmp[Length*2 - 1] = '\0';
    //printf("%d -> %d", strlen(*string), Length);
    if (temp >= 0) {
        char *tmp = (char*)malloc(Length*2);
        tmp[Length*2 - 1] = '\0';
        for(int i = Length * 2 - 2; i >= 0; i--) {
            tmp[i] = (buff % 10) + '0';
            if ((--i) > 0) {
                tmp[i] = ' ';
            }
            buff /= 10;
        }
        *string = tmp;
    }
    else {
        char *tmp = (char*)malloc(Length*2 + 2);
        tmp[Length * 2 + 1] = '\0';
        for(int i = Length * 2; i >= 1; i--) {
            tmp[i] = (buff % 10) + '0';
            if ((--i) > 0) {
                tmp[i] = ' ';
            }
            buff /= 10;
        }
        tmp[0] = '-';
        *string = tmp;
    }
    
}

bool EFunc(long long int temp) {
    if (temp > 10 || temp < -1) {
        return false;
    }
    int table[10][10];
    prepareTable(table, temp);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < temp; j++) {
            int base = i + 1;
            int grade = j + 1;
            printf("\t%d in %d grade equals to: %d\n", base, grade, table[i][j]);
        }
        printf("---------------------------\n");
    }

    return true;
}

bool AFunc(long long int temp, long long int *result) {
    if (temp < 1) {
        return false;
    }
    Sum(temp, result);
    return true;
}

bool FFunc(long long int temp, long long int *result) {
    if (temp < 1 || temp > 20) {
        return false;
    }
    Factorial(temp, result);
    return true;
}

void Usage() {
    printf("                     ./exe [any_int_number] ['-' or '/'flag]                    \n");
    printf("      h - print out natural numbers up to 100 divisible by specified    \n");
    printf("             p - is the specified number primal or compound             \n");
    printf("           s - divide the number by it's digits and print it            \n");
    printf("     e - print out power table for 1 - 10 bases within entered degree   \n");
    printf("          f - Outputs the factorial of numbers less than 20             \n");
}

int main(int argc, char *argv[]) {
    long long int temp = 0;
    if (InputCheck(argc, argv, &temp)) {
        Usage();
        return 1;
    }
    Choice(temp, argv[2][1]);
    return 0;

    
}