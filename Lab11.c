#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char bound_pos[] = "9223372036854775807";

typedef struct VectorInt{
    int num_of_el;
    int* el;
    int mem_capacity;
} VectorInt;

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
    bool flag_dot = true;
    int mantis = 0;
    int count = 0;
    if (s[0] == '-') { 
        if (lenght > 20 || (lenght == 20 && Overflow(s, 1))) {
            return 1;
        }
        for(int i = 1; i < lenght; i++) {
            if (s[i] < '0' || s[i] > '9') {
                if (s[i] == '.') {
                    flag_dot = false;
                }
                else {return 2;}
            }
            else if (flag_dot) {
                *result = *result * 10 + (s[i] - '0');
            }
            else if (!flag_dot) {
                mantis = mantis * 10 + (s[i] - '0');
                count++;
            }
        }
        *result += (mantis * pow((0.1), count));
        *result *= -1;
        return 0;
    }
    if (lenght > 19 || (lenght == 19 && Overflow(s, 0))) {
            return 1;
    }
    for(int i = 0; i < lenght; i++) {
        if (s[i] < '0' || s[i] > '9') {
            if (s[i] == '.') {
                flag_dot = false;
            }
            else {return 2;}
        }
        else if (flag_dot) {
            *result = *result * 10 + (s[i] - '0');
        }
        else if (!flag_dot) {
            mantis = mantis * 10 + (s[i] - '0');
            count++;
        }
    }
    *result += (mantis * pow((0.1), count));
    return false;
}

void ConvCharDouble(char s[], double *result) {
    int lenght = strlen(s);
    bool flag_dot = true;
    int mantis = 0;
    int count = 0;
    for (int i = 0; i < lenght; i++) {
        if (s[i] == '.') {
            flag_dot = false;
        }
        else if (flag_dot) {
            *result = *result * 10 + (s[i] - '0');
        }
        else if (!flag_dot) {
            mantis = mantis * 10 + (s[i] - '0');
            count++;
        }
    }
    *result += (mantis * pow((0.1), count));
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

void Usage() {
    printf("                     ./exe [number] ['-' or '/'flag]                    \n");
    printf("      h - print out natural numbers up to 100 divisible by specified    \n");
    printf("             p - is the specified number primal or compound             \n");
    printf("           s - divide the number by it's digits and print it            \n");
    printf("     e - print out power table for 1 - 10 bases within entered degree   \n");
    printf("          f - Outputs the factorial of numbers less than 20             \n");
}

int main(int argc, char *argv[]) {
    if (argc != 3 || (*argv[2] != '-' && *argv[2] != '/') || (strlen(argv[2]) != 2)) {
        Usage();
        return 1;
    }
    long long int temp = 0;
    if (ConverterCharTo(argv[1], &temp) == 1) {
        printf("Error: Overflow.");
        return 2;
    }
    else if (ConverterCharTo(argv[1], &temp) == 2) {
        printf("Error: Invalid input type.");
        return 2;
    }
/*-----------------------------------------HFunc------------------------------------------*/
    if (argv[2][1] == 'h') { 
        if (temp <= 0 || temp > 100) {
            printf("It seems there're not any divisible by %lld numbers", temp);
        }
        else {
            int count = 0;
            for (long long i = temp; i <= 100; i++) {
                if (i % temp == 0) {
                    printf("%lld ", i);
                    count++;
                }
            }
            if (count == 0) {
                printf("It seems there're not any divisible by %lld numbers", temp);
            }
        }
    }

/*-----------------------------------------PFunc------------------------------------------*/
    else if (argv[2][1] == 'p') {
        if (temp <= 0) {
            printf("Primes list starts with 2, but %lld < 2", temp);
            return 2;
        }
        long long int num = 2;
        VectorInt vec;
        CreateVector(&vec);
        while(num <= temp) {
            bool flag = 1;
            if (!IfEmptyVector(&vec)) {
                for(int i = 0; i < vec.num_of_el; i++) {
                    if (num % vec.el[i] == 0) {
                        flag = 0;
                        break;
                    }
                }
            }   
            if (flag) {
                Adder(&vec, num);
            }
            num++;
        }
        if (vec.el[vec.num_of_el - 1] == temp) {
            printf("%lld is prime", temp);
        }
        else {printf("%lld is compound", temp);}
        Terminate(&vec);
    }

/*-----------------------------------------SFunc------------------------------------------*/
    else if (argv[2][1] == 's') {
        int lenght = 0;
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
    }
/*-----------------------------------------EFunc------------------------------------------*/
    else if (argv[2][1] == 'e') {
        if (temp > 10 || temp < -1) {
            printf("Sorry, it seems entered value exceeded the allowed values: (-1) - (10)");
            return 3;
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
    }

/*-----------------------------------------AFunc------------------------------------------*/
    else if (argv[2][1] == 'a') {
        if (temp < 1) {
            printf("Sorry, it seems entered value exceeded the allowed values: range of naturals");
            return 4;
        }
        long long int result = 0;
        Sum(temp, &result);
        printf("%lld", result);
    }
    
/*-----------------------------------------FFunc------------------------------------------*/
    else if (argv[2][1] == 'f') {
        if (temp < 1 || temp > 20) {
            printf("Sorry, it seems entered value exceeded the allowed values: 1 - 20");
            return 4;
        }
        unsigned long long int result = 1;
        Factorial(temp, &result);
        printf("%llu", result);
    }
    
    
    return 0;
}