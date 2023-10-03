
#ifndef PROCEDURES_H
#define PROCEDURES_H


void usage();

bool convCharDouble(char s[], double *result, int *accuracy); 
void choice(double EPS, int accuracy, char key, double *limit, double *row, double *x);

void factorial(int num, unsigned long long int *result);

void eFunc(double EPS, double *limit, double *row, double *x);
void eLim(double EPS, double *limit);
void eRow(double EPS, double *row);
void eEquation(double EPS, double *x);
void eFuncPrint(double EPS, double *limit, double *row, double *x, int accuracy);

void piFunc(double EPS, double *limit, double *row, double *x);
void piLim(double EPS, double *limit);
void piRow(double EPS, double *row);
void piEquation(double EPS, double *x);
void piFuncPrint(double EPS, double *limit, double *row, double *x, int accuracy);

void ln2Func(double EPS, double *limit, double *row, double *x);
void ln2Lim(double EPS, double *limit);
void ln2Row(double EPS, double *row);
void ln2Equation(double EPS, double *x);
void ln2FuncPrint(double EPS, double *limit, double *row, double *x, int accuracy);

void sqrt2Func(double EPS, double *limit, double *row, double *x);
void sqrt2Lim(double EPS, double *limit);
void sqrt2Row(double EPS, double *row);
void sqrt2Equation(double EPS, double *x);
void sqrt2FuncPrint(double EPS, double *limit, double *row, double *x, int accuracy);

void gammaFunc(double EPS, double *limit, double *row, double *x);
void gammaLim(double EPS, double *limit);
void gammaRow(double EPS, double *row);
void gammaEquation(double EPS, double *x);
void gammaFuncPrint(double EPS, double *limit, double *row, double *x, int accuracy);

#endif 