#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"

bool InputCheck(int argc, char* argv[], long long int *temp) {
    if (argc != 3 || (*argv[2] != '-' && *argv[2] != '/') || (strlen(argv[2]) != 2)) {
        return true;
    }
    else if (ConverterCharTo(argv[1], temp)) {
        return true;
    }
    return false;
}

void CreateVector(VectorInt* v) {
    v->num_of_el = 0;
    v->el = NULL;
    v->mem_capacity = 0;
}

bool IfEmptyVector(VectorInt* v) {
    if (v->num_of_el == 0) 
        return true;
    return false;
}

void Adder(VectorInt* v, int new_value) {
    if (v->mem_capacity == v->num_of_el) {
        v->el = (int*)realloc(v->el, sizeof(int) *(++v->mem_capacity));
    }
    *(v->el + v->num_of_el) = new_value;
    v->num_of_el++;
}

void VectorPrint(VectorInt* v) {
    int i = 0;
    while (i != v->num_of_el) {
        printf("%d ", v->el[i]);
        i++;
    }
}

void Terminate(VectorInt* v) {
    free(v);
}

bool Overflow(char in[],int key) {
    if (!key) {
        for (int i = 0; i < 19; i++) {
            printf("%d -> %d\n", (in[i] - '0'), (bound_pos[i] - '0'));
            if ((in[i] - '0') > (bound_pos[i] - '0')) {
                return true;
            }
        }
        return false;
    }
    for (int i = 0; i < 19; i++) {
        if (in[i + 1] - '0' > bound_pos[i] - '0') {
            return true;
        }
    }
    return false;
}

int ConverterCharTo(char s[], long long int *result) {
    int lenght = strlen(s);
    int mantis = 0;
    int count = 0;
    if (s[0] == '-') { 
        if (lenght > 20 || (lenght == 20 && Overflow(s, 1))) {
            return 1;
        }
        for(int i = 1; i < lenght; i++) {
            if (s[i] < '0' || s[i] > '9') {
                return 2;
            }
            *result = *result * 10 + (s[i] - '0');
        }
        *result *= -1;
        return 0;
    }
    if (lenght > 19 || (lenght == 19 && Overflow(s, 0))) {
            return 1;
    }
    for(int i = 0; i < lenght; i++) {
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

void IntLenght(long long int temp, int *lenght) {
    long long int buff = llabs(temp);
    while (buff > 0) {
        buff /= 10;
        *lenght += 1;
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
            Terminate(&primes);
        }
    }
    else if (key == 's') {
        char *string = (char*)malloc(1);
        string[0] = '\0';
        SFunc(temp, &string);
        //printf("%d", strlen(string));
        printf("\n%s", string);
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
                Adder(divisibles, i);
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
        if (!IfEmptyVector(primes)) {
            for(int i = 0; i < primes->num_of_el; i++) {
                if (num % primes->el[i] == 0) {
                    flag = 0;
                    break;
                }
            }
        }   
        if (flag) {
            Adder(primes, num);
        }
        num++;
    }
    return true;
}

void SFunc(long long int temp, char *string[]) {
    int lenght = 0;
    IntLenght(temp, &lenght);
    long long int buff = llabs(temp);
    char *tmp = (char*)malloc(lenght*2);
    tmp[lenght*2 - 1] = '\0';
    //printf("%d -> %d", strlen(*string), lenght);
    if (temp >= 0) {
        tmp[lenght * 2] = '\0';
        for(int i = lenght * 2 - 2; i >= 0; i--) {
            tmp[i] = (buff % 10) + '0';
            if ((--i) > 0) {
                tmp[i] = ' ';
            }
            buff /= 10;
        }
    }
    else {
        tmp = (char*)realloc(tmp, (lenght*2 + 2) * sizeof(char));
        tmp[lenght * 2 + 1] = '\0';
        for(int i = lenght * 2; i >= 1; i--) {
            tmp[i] = (buff % 10) + '0';
            if ((--i) > 0) {
                tmp[i] = ' ';
            }
            buff /= 10;
        }
        tmp[0] = '-';
    }
    *string = tmp;
}

bool EFunc(long long int temp) {
    if (temp > 10 || temp < -1) {
        return false;
    }
    printf("  ");
    for (int i = -1; i <= temp; i++) {
        printf("%d ", i);
    }
    printf("\n");
    printf("--");
    for (int i = -1; i <= temp; i++) {
        printf("--");
    }
    printf("\n");
    int i = 0;
    while (i != 10) {
        i++;
        printf("%d|", i);
        int result = i;
        for (int count = -1; count <= temp; count++) {
             printf("%lf ", pow(result, count));
        }
        printf("|\n");
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

    
/*-----------------------------------------SFunc------------------------------------------*/
        /*int lenght = 0;
        long long int buff = llabs(temp);
        while (buff > 0) {
            buff /= 10;
            lenght++;
        }
        buff = llabs(temp);
        char *string = (char*)malloc(lenght*2 + 1);
        string[lenght * 2] = '\0';
        for(int i = 0; i < lenght * 2; i += 2) {
            string[i] = ' ';
            string[i + 1] = (buff % 10) + '0';
            buff /= 10;
        }
        if (temp < 0) {
            string = (char*)realloc(string, lenght*2 + 3);
            string[lenght * 2 + 2] = '\0';
            string[lenght * 2 ] = ' ';
            string[lenght * 2 + 1] = '-';
        }
        printf("%s", strrev(string));
        free(string);
    }*/

/*-----------------------------------------FFunc------------------------------------------*/
}