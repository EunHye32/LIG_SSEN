#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define SWAP(type, a, b) do { type temp = a; a = b; b = temp; } while(0)

#if 1 // 함수 포인터 - 구조체
#include "week01_day07_mylib.h"
int main(void)
{
  extern calculate arr[6];
  int a = 20, b = 10;
  int input = 0;
  calculate* temp = NULL;

  while (input = get_input(arr, SIZE(arr)))
  {
    if (input < 0 || input >= SIZE(arr)) continue;
    temp = arr + input;
    if (!temp) break;
    printf("%d %c %d = %d\n", a, temp->op_char, b, temp->op_func(a, b));
  }

  return 0;
}
#endif

#if 0 // 함수 포인터 - 함수 포인터 배열
#include "week01_day07_mylib.h"
int main(void)
{
  int a = 20, b = 10;
  int (*farr[])(int, int) = { 0, sum, sub, mul, divi, mod };
  char* names[] = { 0, "sum", "sub", "mul", "divi", "mod" };
  char op[6] = " +-*/%";
  int clc = 0, input = 0;

  while (input = get_input(names, SIZE(names)))
  {
    if (input < 0 || input > 5) continue;
    printf("%d %c %d = %d\n", a, op[input], b, farr[input](a, b));
  }

  /* 함수 포인터 for 문
  int total = 0;
  for (int i = 1; i < SIZE(farr); i++)
  {
    clc = farr[i](a, b);
    total += clc;
    printf("%d %c %d = %d\n", a, op[i], b, farr[i](a, b));
  }
  printf("total = %d\n", total);
  */

  return 0;
}
#endif

#if 0 // qsort - int, float, char*, struct
// 구조체
typedef struct student {
  char name[12];
  int no;
  int score;
} stu;
void print_array(int* a, int n)
{
  for (int i = 0; i < n; i++) printf("%d ", a[i]);
  printf("\n");
}
void print_array2(float* a, int n)
{
  for (int i = 0; i < n; i++) printf("%.2f ", a[i]);
  printf("\n");
}
void print_array3(char** a, int n)
{
  for (int i = 0; i < n; i++) printf("%s ", a[i]);
  printf("\n");
}
void print_array4(stu* a, int n)
{
  stu temp;
  for (int i = 0; i < n; i++)
  {
    temp = a[i];
    printf("%s %d %d\n", temp.name, temp.no, temp.score);
  }
}
int comp_int(const void* ap, const void* bp)
{
  int a = *(int*)ap;
  int b = *(int*)bp;
  return (a > b) - (a < b);
}
int comp_float(const void* ap, const void* bp)
{
  float a = *(float*)ap;
  float b = *(float*)bp;
  return (a > b) - (a < b);
}
int comp_str(const void* ap, const void* bp)
{
  return strcmp(*(char**)ap, *(char**)bp);
}
int comp_struct(const void* a, const void* b)
{
  //return (((stu*)a)->no > ((stu*)b)->no) - (((stu*)a)->no < ((stu*)b)->no); // 구조체의 no 기준 오름차순
  return strcmp(((stu*)a)->name, ((stu*)b)->name); // 구조체의 name 기준 오름차순
}
int main(void)
{
  int arr[6] = { 5, 2, 8, 4, 0, 6 };
  float brr[5] = { 3.12, 5.89, 2.11, 10.9, 3.11 };
  char* str[5] = { "lion", "tiger", "cat", "rabbit", "dog" };
  stu A[5] = {
    {"soyoung", 3, 89},
    {"lignex1", 1, 90},
    {"changhee", 4, 100},
    {"sungshin", 2, 95},
    {"suhwan", 5, 88}
  };

  print_array2(brr, SIZE(brr));
  //qsort(arr, SIZE(arr), sizeof(arr[0]), comp_int); print_array1(arr, SIZE(arr));
  qsort(brr, SIZE(brr), sizeof(float), comp_float);
  print_array2(brr, SIZE(brr));

  print_array3(str, SIZE(str));
  qsort(str, SIZE(str), sizeof(char*), comp_str);
  print_array3(str, SIZE(str));

  qsort(A, SIZE(A), sizeof(A[0]), comp_struct);
  print_array4(A, SIZE(A));

  return 0;
}
#endif

#if 0 // 함수포인터 - 정렬(오름차순, 내림차순)
void print_array(int* a, int n)
{
  for (int i = 0; i < n; i++) printf("%d ", a[i]);
  printf("\n");
}
void sort_array(int* a, int n, int h)
{
  int target_i = 0;
  if (h != 0 && h != 1) return;
  if (h) // 오름차순
  {
    for (int i = 0; i < n - 1; i++)
    {
      //for (int j = i + 1; j < n; j++) if (a[i] > a[j]) SWAP(int, a[i], a[j]); // 오름차순
      target_i = i;
      for (int j = i + 1; j < n; j++) if (a[target_i] > a[j]) target_i = j;
      if(i != target_i) SWAP(int, a[i], a[target_i]);
    }
  }
  else // 내림차순
  {
    for (int i = 0; i < n - 1; i++)
    {
      //for (int j = i + 1; j < n; j++) if (a[i] < a[j]) SWAP(int, a[i], a[j]); // 내림차순
      target_i = i;
      for (int j = i + 1; j < n; j++) if (a[target_i] < a[j]) target_i = j;
      if (i != target_i) SWAP(int, a[i], a[target_i]);
    }
  }
}
// sort_array2 : 함수 포인터 사용한 버전
int ascending(int a, int b);
int decending(int a, int b);
void sort_array2(int* a, int n, int (*comp)(int, int))
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++) if (comp(a[i], a[j])) SWAP(int, a[i], a[j]);
  }
}
int ascending(int a, int b)
{
  return a > b;
}
int decending(int a, int b)
{
  return a < b;
}
int main(void)
{
  int a[10] = { 9, 4, 8, 7, 1, 2, 3, 5, 6, 2 };
  //print_array(a, SIZE(a)); sort_array(a, SIZE(a), 1); // 오름차순
  //print_array(a, SIZE(a)); sort_array(a, SIZE(a), 0); // 내림차순
  print_array(a, SIZE(a)); sort_array2(a, SIZE(a), ascending); // 오름차순
  print_array(a, SIZE(a)); sort_array2(a, SIZE(a), decending); // 내림차순
  print_array(a, SIZE(a));
  return 0;
}
#endif

#if 0 // 문자열 char *pary[5]의 등가 포인터
void printf_ary(char** p, int size)
{
  for (int i = 0; i < size; i++) printf("%s\n", p[i]);
}
int main(void)
{
  char* pary[5] = { "tiger", "rabbit", "cat", "dog", "lion" };
  printf_ary(pary, SIZE(pary));
  return 0;
}
#endif

#if 0 // 다중 포인터의 call by reference
void exchange1(int **p1, int **p2) // ap, bp 변수의 주소를 전달받아 교환
{
  int temp = **p1;
  **p1 = **p2;
  **p2 = temp;
}
void exchange2(int*** p1, int*** p2) // app, bpp 변수의 주소를 전달받아 교환
{
  int temp = ***p1;
  ***p1 = ***p2;
  ***p2 = temp;
}
void exchange3(int** p1, int** p2) // ap, bp 변수의 주소를 전달받아 주소 교환
{
  int *temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
void exchange4(int** p1, int** p2) // app, bpp 변수의 주소를 전달받아 주소 교환
{
  int* temp = **p1;
  **p1 = **p2;
  **p2 = temp;
}
void exchange5(int* p1, int* p2) // app, bpp 변수의 주소를 전달받아 주소 교환
{
  int* temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
int main(void)
{
  int a = 0, b = 5;
  int* ap = &a, * bp = &b;
  int** app = &ap, ** bpp = &bp;

  //printf("%d %d\n", a, b); exchange1(&ap, &bp); printf("%d %d\n", a, b);
  //printf("%d %d\n", a, b); exchange2(&app, &bpp); printf("%d %d\n", a, b);
  //printf("%p %p\n", ap, bp); exchange3(&ap, &bp); printf("%p %p\n", ap, bp);
  //printf("%p %p\n", ap, bp); exchange4(&app, &bpp); printf("%p %p\n", ap, bp);
  //printf("%p %p\n", app, bpp); exchange5(&app, &bpp); printf("%p %p\n", app, bpp);
  return 0;
}
#endif

#if 0 // 함수 인자 넘기기
void func(int** app, int** bpp) // 주소값 바꾸기. 이렇게 작성해줘야 함
{
  int* temp = *app;
  *app = *bpp;
  *bpp = temp;
}
void func2(int** app, int** bpp)
{
  int temp = **app;
  **app = **bpp;
  **bpp = temp;
}
int main(void)
{
  int a = 10, b = 20;
  int* ap = &a;
  int* bp = &b;
  printf("%p %p\n", ap, bp);
  //func(&ap, &bp);
  func2(&ap, &bp);
  printf("%d %d\n", a, b);
  return 0;
}
#endif