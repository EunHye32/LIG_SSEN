#ifndef __MYLIB_H__
#define __MYLIB_H__

typedef struct _calculate
{
  int (*op_func)(int, int);
  char* op_name;
  char op_char;
} calculate;

int sum(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int divi(int a, int b);
int mod(int a, int b);
void print_menu(calculate* arr, int size);
int get_input(calculate* arr, int size);

#endif