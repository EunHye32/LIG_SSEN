#include <stdio.h>

#if 1 // 함수 포인터 구조체
#include "week01_day07_mylib.h"
calculate arr[] = {
  {0},
  {sum, "sum", '+'},
  {sub, "sub", '-'},
  {mul, "mul", '*'},
  {divi, "divi", '/'},
  {mod, "mod", '%'}
};

int sum(int a, int b)
{
  return a + b;
}
int sub(int a, int b)
{
  return a - b;
}
int mul(int a, int b)
{
  return a * b;
}
int divi(int a, int b)
{
  return a / b;
}
int mod(int a, int b)
{
  return a % b;
}
void print_menu(calculate* arr, int size)
{
  for (int i = 1; i < size; i++) {
    printf("%d. %s\n", i, arr[i].op_name); // (arr + i)->op_name
  }
  printf("0. exit\n");
}
int get_input(calculate* arr, int size)
{
  int num = 0;
  print_menu(arr, size);
  printf("input: ");
  (void)scanf("%d", &num);
  return num;
}
#endif