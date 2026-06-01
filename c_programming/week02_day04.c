#include <stdio.h>
#include <math.h>
#include <ctype.h>

#if 0 // 대소문자 바꾸기
char* to_upper(char* name)
{
  if (name == NULL) return NULL;

  char* save = name;
  char c;
  while (c = *name)
  {
    if ((c >= 'a') && (c <= 'z')) *name -= 'a' - 'A'; //*name = toupper(*name);
    else if ((c >= 'A') && (c <= 'Z')) *name += 'a' - 'A'; //*name = tolower(*name);
    name++;
  }
  return save;
}
int main(void)
{
  char name[40] = "Tom & Jerry!";
  printf("%s\n", to_upper(name));

  return 0;
}
#endif

#if 0 // getchar 사용한 함수 만들기
#define size_ary(x) (sizeof(x) / sizeof((x)[0]))
/* better version
void my_gets(char* str, int size)
{
  int c;
  int idx = 0;
  while ((idx < size - 1) && (c = getchar()) != '\n')
  {
    str[idx++] = c;
  }
  str[idx] = '\0';
}
*/
void my_gets(char* str, int size)
{
  char temp = '\0';
  for (int i = 0; i < size - 1; i++)
  {
    temp = getchar();
    if (temp == '\n')
    {
      str[i] = '\0';
      break;
    }
    str[i] = temp;
    str[i + 1] = '\0';
  }
}
int main(void)
{
  char str[11] = { 0 };

  my_gets(str, size_ary(str));
  printf("%s\n", str);
  return 0;
}
#endif

#if 0 // 함수들 만들기
#define INDEX_SIZE 5
int print_ary(int* num); // 2. ary 배열에 있는 값을 출력하는 함수
int scanf_ary(int *num)
{
  scanf("%d %d %d %d %d", num, num + 1, num + 2, num + 3, num + 4);
  print_ary(num);
  return 0;
}
int print_ary(int* num)
{
  for (int i = 0; i < INDEX_SIZE; i++) printf("%d\n", *(num + i));
  return 0;
}
int findmax_ary(int* num)
{
  int max = num[0];
  for (int i = 1; i < INDEX_SIZE; i++)
  {
    if (max < *(num + i)) max = *(num + i);
  }
  return max;
}
int findmin_ary(int* num)
{
  int min = num[0];
  for (int i = 1; i < INDEX_SIZE; i++)
  {
    if (min > *(num + i)) min = *(num + i);
  }
  return min;
}
int sum_ary(int* num)
{
  int sum = 0;
  for (int i = 0; i < INDEX_SIZE; i++) sum += *(num + i);
  return sum;
}
int avg_ary(int* num)
{
  // (int)round(sum_ary(num) / INDEX_SIZE)
  // (int)(sum_ary(num) / INDEX_SIZE + 0.5)
  return sum_ary(num) / INDEX_SIZE + (sum_ary(num) % INDEX_SIZE > 5 ? 1: 0);
}
int main(void)
{
  int ary[5] = { 0 };
  scanf_ary(ary); // 1. ary 배열에 5개 정수 값을 입력 받는 함수
  printf("Max num: %d\n", findmax_ary(ary)); // 3. ary 배열에 있는 값에서 가장 큰 수를 찾아 반환하는 함수
  printf("Min num: %d\n", findmin_ary(ary)); // 3. ary 배열에 있는 값에서 가장 큰 작은 수를 찾아 반환하는 함수
  printf("Sum: %d\n", sum_ary(ary)); // 4. ary 배열에 있는 모든 값을 더한 값을 반환하는 함수
  printf("Average: %d\n", avg_ary(ary)); // 5. ary 배열에 있는 모든 값의 평균을 반환하는 함수
  printf("Var: %d\n", avg_ary(ary)); // 5. ary 배열에 있는 모든 값의 분산을 반환하는 함수
  return 0;
}
#endif

#if 0 // 함수 포인터 3
int* func(void)
{
  static int arr[5] = { 10, 20, 30, 40, 50 };
  return arr;
}
int main(void)
{
  printf("%d\n", func()[3]); // arr에 static 써야 메모리에 계속 값이 남아있어 안전
  return 0;
}
#endif

#if 0 // 함수 포인터 2
int func(int a, int b)
{
  return a + b;
}
int main(void)
{
  int (*p)(int, int) = func;
  printf("%d\n", (*p)(10, 20)); // printf("%d\n", p(10, 20));
  return 0;
}
#endif

#if 0 // 함수 포인터 1
int sub1(void)
{
  int a = 10;
  return a;
}
int (*func1())()
{
  return sub1;
}
int main(void)
{
  int(*(*ap)())() = func1;
  //char* (*(*var)())[10] = func2;
  return 0;
}
#endif

#if 0 // 포인터 배열과 배열 포인터
int main(void)
{
  int a[5] = { 0 };

  printf("%p %p %p\n", &a[0], a, &a);
  printf("%p %p\n", a + 1, &a + 1);
  printf("%d %d %d %d\n", sizeof(a), sizeof(&a), sizeof(*a), sizeof(*&a));

  return 0;
}
#endif

#if 0 // swap 함수
#define SWAP_PTR(pa, pb) do { int temp = *(pa); *(pa) = *(pb); *(pb) = temp; } while(0) // 전처리기 방식
#define SWAP(a, b, type) do { type temp = (a); (a) = (b); (b) = temp; } while(0) // type까지 넘기는 전처리기 방식
void swap(int* pa, int* pb)
{
  int temp = 0;
  
  temp = *pa;
  *pa = *pb;
  *pb = temp;
}
int main(void)
{
  int a = 10, b = 20;
  printf("a = %d, b = %d\n", a, b);
  swap(&a, &b);
  printf("a = %d, b = %d\n", a, b);
  return 0;
}
#endif