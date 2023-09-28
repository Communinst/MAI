#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Procedure.h"

const double pi = 3.14159265;


/*---------------------------------------Basic--------------------------------------------*/
void machineEPS(double *machine_eps) {
    while (1 + *machine_eps / 2.0 > 1.0)
    {
        *machine_eps /= 2.0;
    }
}

void usage() {
    printf("./exe [epsilon_value] [accuracy_value]\n");
}

/*----------------------------------------------------------------------------------------*/


/*-------------------------------------------Converters-----------------------------------*/

void convCharDouble(char s[], double *result, int *count) {
    int lenght = strlen(s);
    bool flag_dot = true;
    int mantis = 0;
    *count = 0;
    for (int i = 0; i < lenght; i++) {
        if (s[i] == '.') {
            flag_dot = false;
        }
        else if (flag_dot) {
            *result = *result * 10 + (s[i] - '0');
        }
        else if (!flag_dot) {
            mantis = mantis * 10 + (s[i] - '0');
            *count += 1;
        }
    }
    *result += (mantis * pow((0.1), *count));
}

/*----------------------------------------------------------------------------------------*/


/*--------------------------------------Factorial------------------------------------------*/
void factorial(int num, unsigned long long int *result) {
    *result = 1;
    if (num < 2) 
        return;
    factorial(num - 1, result);
    *result *= num;
}
/*----------------------------------------------------------------------------------------*/


/*-----------------------------------econstBlock------------------------------------------*/

void eFunc(double EPS, double *limit, double *row, double *x) {
    *limit = 0.0;
    *row = 0.0;
    *x = 0.0;
    eLim(EPS, limit);
    eRow(EPS, row);
    eEquation(EPS, x);
}

void eLim(double EPS, double *limit) {
    double prev_limit = 0.0;
    int num = 1;
    do {
        prev_limit = *limit;
        *limit = (pow((1 + pow(num, -1)), num));
        num++;
    } while (fabs(prev_limit - *limit) > EPS);
}

void eRow(double EPS, double *row) {
    double prev_row = 0.0;
    int num = 0;
    unsigned long long int fact = 1;
    do {
        prev_row = *row;
        factorial(num, &fact);
        *row += pow(fact, -1); 
        num++;
    } while (fabsl(prev_row - *row) > EPS);
}

void eEquation(double EPS, double *x) {
    double left = 1.0;
    double right = 3.0;
    
    while (fabs(left - right) > EPS) {
        *x = (left + right) / 2;
        if (fabs(log(*x) - 1) < EPS) {
            break;
        }
        if ((log(left) - 1) * (log(*x) - 1) > 0) {
            left = *x;
        } 
        else { 
            right = *x;
        }
    }
    *x = (left + right) / 2;
}

void eFuncPrint(double EPS, double *limit, double *row, double *x, int accuracy) {
    printf("e number by:\nLimit: %.*llf\nRows: %.*llf\nEquation: %.*llf\n", 
    accuracy, *limit, accuracy, *row, accuracy, *x);
}

/*----------------------------------------------------------------------------------------*/

void piFunc(double EPS, double *limit, double *row, double *x) {
    *limit = 0.0;
    *row = 0.0;
    *x = 0.0;
    piLim(EPS, limit);
    piRow(EPS, row);
    piEquation(EPS, x);
}

void piLim(double EPS, double *limit) {
    double prev_limit = 0.0;
    *limit = 4;
    int num = 1;
    do {
        prev_limit = *limit;
        *limit = *limit * (4 * num * (num + 1.0)) / pow((2.0 * num + 1), 2);
        num++;
    } while(fabsl(prev_limit - *limit) >= EPS);
}

void piRow(double EPS, double *row) {
    double prev_row = 0.0;
    double num = 2;
    int count = 0;
    do {
        count %= 2;
        prev_row = *row;
        *row += (4.0 * pow(-1, count) / (num - 1));
        count++;
        num += 2.0;
    } while (fabs(prev_row - *row) > EPS);
}

void piEquation(double EPS, double *x) {
    double left = 2.0;
    double right = 4.0;
    
    do {
        *x = (right + left) / 2;
        if (cos(*x) + 1 < EPS) {
            break;
        }
        if (sin(*x) > 0) {
            left = *x;
        }
        else {
            right = *x;
        }
    } while (fabs(left - right) > EPS);
    *x = (right + left) / 2;
}

void piFuncPrint(double EPS, double *limit, double *row, double *x, int accuracy) {
    printf("pi number by:\nLimit: %.*llf\nRows: %.*llf\nEquation: %.*llf\n", 
    accuracy, *limit, accuracy, *row, accuracy, *x);
}

/*----------------------------------------------------------------------------------------*/

void ln2Func(double EPS, double *limit, double *row, double *x) {
    *limit = 0.0;
    *row = 0.0;
    *x = 0.0;
    ln2Lim(EPS, limit);
    ln2Row(EPS, row);
    ln2Equation(EPS, x);
}

void ln2Lim(double EPS, double *limit) {
    double prev_limit = 0.0;
    *limit = 1;
    int num = 2;
    do {
        prev_limit = *limit;
        *limit = num * (pow(2, pow(num, -1)) - 1);
        num++;
    } while(fabsl(prev_limit - *limit) >= EPS);
}

void ln2Row(double EPS, double *row) {
    double prev_row = 0.0;
    int num = 1;
    int count = 0;
    do {
        count %= 2;
        prev_row = *row;
        *row += pow(-1, count) / (num);
        count++;
        num += 1;
    } while (fabs(prev_row - *row) > EPS);
}

void ln2Equation(double EPS, double *x) {
    double left = 0.0;
    double right = 1.0;
    
    do {
        *x = (right + left) / 2;
        if (fabs(exp(*x) - 2) < EPS) {
            break;
        }
        if ((exp(left) - 2) * (exp(*x) - 2) > 0) {
            left = *x;
        }
        else {
            right = *x;
        }
    } while (fabs(left - right) > EPS);
    *x = (right + left) / 2;
}

void ln2FuncPrint(double EPS, double *limit, double *row, double *x, int accuracy) {
    printf("ln2 number by:\nLimit: %.*llf\nRows: %.*llf\nEquation: %.*llf\n", 
    accuracy, *limit, accuracy, *row, accuracy, *x);
}

/*----------------------------------------------------------------------------------------*/

void sqrt2Func(double EPS, double *limit, double *row, double *x) {
    *limit = 0.0;
    *row = 0.0;
    *x = 0.0;
    sqrt2Lim(EPS, limit);
    sqrt2Row(EPS, row);
    sqrt2Equation(EPS, x);
}

void sqrt2Lim(double EPS, double *limit) {
    double prev_limit = 0.0;
    *limit = 0.5;
    int num = 0;
    do {
        prev_limit = *limit;
        *limit  += 1 - prev_limit * prev_limit / 2;
    } while(fabsl(prev_limit - *limit) >= EPS);
}

void sqrt2Row(double EPS, double *row) {
    double prev_row = 0.0;
    int num = 2;
    *row = 1;
    do {
        prev_row = *row;
        *row *= pow(2, pow(2, -num));
        num++;
    } while (fabs(prev_row - *row) > EPS);
}

void sqrt2Equation(double EPS, double *x) {
    double left = 1.0;
    double right = 2.0;
    
    do {
        *x = (right + left) / 2;
        if (fabs(pow(*x, 2) - 2) < EPS) {
            break;
        }
        if ((pow(left, 2) - 2) * (pow(*x, 2) - 2) > 0) {
            left = *x;
        }
        else {
            right = *x;
        }
    } while (fabs(left - right) > EPS);
    *x = (right + left) / 2;
}

void sqrt2FuncPrint(double EPS, double *limit, double *row, double *x, int accuracy) {
    printf("sqrt2 number by:\nLimit: %.*llf\nRows: %.*llf\nEquation: %.*llf\n", 
    accuracy, *limit, accuracy, *row, accuracy, *x);
}

/*----------------------------------------------------------------------------------------*/

void gammaFunc(double EPS, double *limit, double *row, double *x) {
    *limit = 0.0;
    *row = 0.0;
    *x = 0.0;
    gammaLim(EPS, limit);
    gammaRow(EPS, row);
    gammaEquation(EPS, x);
}

void gammaLim(double EPS, double *limit) {
    double prev_limit = 0.0;
    double num = 4;
    *limit = (1.0 / 2.0) + (2 - 3.0 / 2.0);
    do {
        int k = 1;
        prev_limit = *limit;
        *limit = 0;
        do {
            *limit += ((1.0 / num) * (ceil(num / k) - (num / k)));
            k++;
        } while (k <= num);
        num++;
    } while(fabsl(prev_limit - *limit) >= EPS);
}

void gammaRow(double EPS, double *row) {
    double prev_row = 0.0;
    int num = 2;
    *row = ((-1.0) * (pi * pi / 6.0));
    do {
        if (pow(floor(sqrt(num)), 2) != num) {
            prev_row = *row;
            *row += ((1.0 / (floor(sqrt(num)) * floor(sqrt(num)))) - (1.0 / num));
        }
        num++;
        
    } while (fabs(prev_row - *row) > EPS);
}

void gammaEquation(double EPS, double *x) {
    double left = 0.0;
    double right = 1.0;
    double multipl = 1;
    double prev_limit = 0;
    double limit = 0;
    int num = 2;
    do {
        bool prime = true;
        if (prime) {
            for (int i = 2; i <= sqrt(num); i++) {
                if (((num % i) == 0) && num != 2) {
                    prime = false;
                    break;
                }
            }
        }
        if (prime) {
            multipl *= ((num - 1.0) / num);
        }
        prev_limit = limit;
        limit = log(num) * multipl;
        num++;
        
    } while (fabs(prev_limit - limit) > EPS);
    do {
        *x = (left + right) / 2;

        if (fabs((1 / exp(*x)) - limit) < EPS) {
            break;
        }
        if (((1 / exp(left)) - limit) * ((1 / exp(*x)) - limit) > 0) {
            left = *x;
        }
        else {
            right = *x;
        }
    } while (fabs(left - right) > EPS);
    *x = (left + right) / 2;
}

void gammaFuncPrint(double EPS, double *limit, double *row, double *x, int accuracy) {
    printf("gamma number by:\nLimit: %.*llf\nRows: %.*llf\nEquation: %.*llf\n", 
    accuracy, *limit, accuracy, *row, accuracy, *x);
}

/*----------------------------------------------------------------------------------------*/

void menu(double EPS, int accuracy, double *limit, double *row, double *x) {
    printf("key list:\n'e' - e number value;\n'p' - pi number value;\n'l' - ln(2) number value;\n's' - sqrt(2) number value;\n'g' - gamma number value;\n");
    printf("Enter the key:\n");
    char key;
    while ((key = getchar()) != EOF){
        choice(EPS, accuracy, key, limit, row, x);
    }   
}

void choice(double EPS, int accuracy, char key, double *limit, double *row, double *x) {
    switch (key) {
        case 'e':
            eFunc(EPS, limit, row, x);
            eFuncPrint(EPS, limit, row, x, accuracy);
            break;
        case 'p':
            while (accuracy > 8) {
                printf("Invalid EPS value: <= 1e-8\n");
            }
            piFunc(EPS, limit, row, x);
            piFuncPrint(EPS, limit, row, x, accuracy);        
            break;
        case 'l':
            while (accuracy > 8) {
                printf("Invalid EPS value: <= 1e-8");
            }
            ln2Func(EPS, limit, row, x);
            ln2FuncPrint(EPS, limit, row, x, accuracy);
            break;
        case 's':
            while (accuracy > 15) {
                printf("Invalid EPS value: <= 1e-15\n");
            }
            sqrt2Func(EPS, limit, row, x);
            sqrt2FuncPrint(EPS, limit, row, x, accuracy);
            break;
        case 'g':
            while (accuracy > 7) {
                printf("Invalid EPS value: <= 1e-8");
            }
            gammaFunc(EPS, limit, row, x);
            gammaFuncPrint(EPS, limit, row, x, accuracy);
            break;
        default:
            break;
        }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        return 1;
    }
    double EPS = 0.0;
    int accuracy = 0;
    convCharDouble(argv[1], &EPS, &accuracy);

    double limit = 0.0;
    double row = 0.0;
    double equation = 0.0;
    printf("%d", accuracy);
    
    menu(EPS, accuracy, &limit, &row, &equation);
    return 0;
}