#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof(x[0]))

#if 0 // 비트 필드 구조체
struct bit
{
  unsigned a : 3;
  unsigned b : 3;
  unsigned c : 3;
}x;
int main(void)
{
  x.a = 2;
  x.b = 1;
  x.c = 5;

  printf("%X %X\n", *(char*)&x, *((char*)&x + 1));  // 4A 1
  return 0;
}
#endif

#if 0 // 비트 필드 구조체 & union
typedef struct _color1
{
  unsigned int blue : 8;
  unsigned int green : 8;
  unsigned int red : 8;
}color1;
typedef union _dot {
  unsigned int color;
  color1 rgb;
}dot;
typedef struct _color2
{
  unsigned char blue;
  unsigned char green;
  unsigned char red;
}color2;
int main(void)
{
  color1 c1 = { 0x1F, 0x2F, 0x3F };
  color2 c2 = { 0x1F, 0x2F, 0x3F };
  dot d1 = { 0x1F2F3F };
  d1.rgb.green = 0x4F;

  printf("%d %d %d\n", sizeof(color1), sizeof(color2), sizeof(d1));
  printf("%X %X %X\n", c1.blue, c1.green, c1.red);
  printf("%X %X %X\n", c2.blue, c2.green, c2.red);
  printf("%X %X %X %X\n", d1.color, d1.rgb.blue, d1.rgb.green, d1.rgb.red);
  return 0;
}
#endif

#if 0 // 구조체 크기 - pragma pack/pop
#pragma pack(push, 1) // 기존의 룰을 넣어놓고 1을 넣어둠
typedef struct _mix1
{
  double z1;
  int a1;
  char x1;
}mix1;
#pragma pack(pop)     // 기존의 룰로 돌아감
#pragma pack(push, 4)
typedef struct _mix2
{
  int z2;
  double a2;
  char x2;
}mix2;
#pragma pack(pop)
typedef struct _mix3
{
  int z2;
  double a2;
  char x2;
}mix3;
int main(void)
{
  printf("mix1 = %d\n", sizeof(mix1));  // 13
  printf("mix1 = %d\n", sizeof(mix2));  // 16
  printf("mix1 = %d\n", sizeof(mix3));  // 24
  return 0;
}
#endif

#if 0 // 구조체 배열 2
typedef struct _student {
  int id;
  int *scores;
  char *name;
}student;
student* input_data2(int n_arr, int n_score)
{
  student* p = NULL;
  student* temp = NULL;
  char name[20] = { 0 };

  p = (student*)calloc(n_arr, sizeof(student));
  if (p == NULL) exit(1);

  for (int i = 0; i < n_arr; i++)
  {
    temp = p + i;
    (void)scanf("%d", &temp->id);
    int* arr = (int*)calloc(n_score, sizeof(int));
    if (arr == NULL)
    {
      free(p);
      exit(1);
    }
    for (int j = 0; j < n_score; j++)
    {
      (void)scanf("%d", &arr[j]);
    }
    temp->scores = arr;

    (void)scanf("%s", name);
    temp->name = (char*)malloc(strlen(name) + 1);
    if (temp->name == NULL)
    {
      free(temp->scores);
      free(p);
      exit(1);
    }
    strcpy(temp->name, name);
  }
  return p;
}
void print_data(student* stu, int n_arr, int n_scores)
{
  if (stu == NULL) return;

  student* temp = NULL;
  int* s = NULL;
  for (int i = 0; i < n_arr; i++)
  {
    temp = stu + i;
    printf("%d ", temp->id);
    s = temp->scores;
    for (int j = 0; j < n_scores; j++)
      printf("%d ", s[j]);
    printf("%s\n", temp->name);
  }
}
void free_data(student* stu, int n_arr)
{
  if (stu == NULL) return;

  for (int i = 0; i < n_arr; i++)
  {
    free(stu[i].scores);
    free(stu[i].name);
  }
  free(stu);
}
int main(void)
{
  student* stu = NULL;
  int n_arr, n_score;
  (void)freopen("day08_2_student2.txt", "r", stdin);
  (void)scanf("%d %d", &n_arr, &n_score);
  stu = input_data2(n_arr, n_score);
  print_data(stu, n_arr, n_score);
  free_data(stu, n_arr);

  return 0;
}
#endif

#if 0 // 구조체 배열
typedef struct _student {
  int id;
  int scores[3];
  char name[20];
}student;
void input_data(student *data_i, int size)
{
  if (data_i == NULL) return;

  student* temp = NULL;
  int* s = NULL;
  for (int i = 0; i < size; i++)
  {
    temp = data_i + i;
    s = temp->scores;
    scanf("%d %d %d %d %s", &temp->id, &s[0], &s[1], &s[2], temp->name);
  }
}
void print_data(student* data_p, int size)
{
  if (data_p == NULL) return;

  student* temp = NULL;
  int* s = NULL;
  for (int i = 0; i < size; i++)
  {
    temp = data_p + i;
    s = temp->scores;
    printf("%d %d %d %d %s\n", temp->id, s[0], s[1], s[2], temp->name);
  }
}
int main(void)
{
  student stu[5] = { 0 };
  (void)freopen("day08_2_student.txt", "r", stdin);
  input_data(stu, SIZE(stu));
  print_data(stu, SIZE(stu));
  return 0;
}
#endif

#if 0 // 구조체 2
typedef struct _profile
{
  int age;
  double height;
  char* name;
}profile;
typedef struct _student
{
  profile pf;
  int num;
  double grade;
}student;

int main(void)
{
  student s1 = { {20, 160, "eunhye"}, 1, 4.5 };
  student* p = &s1;
  printf("%d %.2f %s %d %.2f\n", s1.pf.age, s1.pf.height, s1.pf.name, s1.num, s1.grade);
  printf("%d %.2f %s %d %.2f\n", p->pf.age, p->pf.height, p->pf.name, p->num, p->grade);
  p->pf.name = "EunHye";  // .rodata의 주소를 l-value로 사용하여 일부 바꾸는건 안됨. p->pf.name은 포인터 변수.
  printf("%d %.2f %s %d %.2f\n", p->pf.age, p->pf.height, p->pf.name, p->num, p->grade);
  return 0;
}
#endif

#if 0 // 구조체 1
typedef struct _student
{
  int num;
  double grade;
}student;
int main(void)
{
  student s1 = { 0 };
  student* sp = &s1;
  s1.num = 2;
  s1.grade = 2.7;

  printf("num: %d, grade: %.2lf\n", s1.num, s1.grade);
  printf("num: %d, grade: %.2f\n", sp->num, (*sp).grade);
  return 0;
}
#endif

#if 0 // string malloc
int main(void)
{
  char temp[80] = { 0 };
  char** str = NULL;
  int N = 3;

  str = (char**)calloc(N, sizeof(char*));
  if (str == NULL) exit(1);
  for (int i = 0; i < 3; i++)
  {
    gets(temp);
    str[i] = (char*)calloc(strlen(temp) + 1, sizeof(char));
    if (str[i] == NULL)
    {
      free_array(str, N);
      exit(1);
    }
    strcpy(str[i], temp);
  }

  for (int i = 0; i < N; i++)
  {
    printf("%s\n", str[i]);
  }

  free_array(str, N);
  return 0;
}
#endif

#if 0 // realloc
#include "day08_my_alloc.h"
int main(void)
{
  int N = 0, data = 0, i = 0;
  int* pi = NULL;

  pi = read_array2(&N);
  print_array(pi, N);

  if (pi)
  {
    printf("Final pi free.\n");
    free(pi);
    pi = NULL;
  }

  return 0;
}
#endif

#if 0 // malloc with day08_my_alloc files
#include "day08_my_alloc.h"
int main(void)
{
  int* arr = NULL;
  int num = 5;

  arr = (int*)create_array(num, sizeof(int));

  read_array(arr, num);
  print_array(arr, num);
  printf("%f\n", get_mean(arr, num));

  free(arr);
  arr = NULL; // 이게 없는 상황에서는 올바르게 작동하는 것으로 보여 위험함!

  return 0;
}
#endif