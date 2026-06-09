#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof(x[0]))

#if 0 // NDEBUG & 경고 msg - assert
#define NDEBUG  // 디버그 안한다는 뜻
#include <assert.h>
int main(void)
{
  int x;
  printf("Enter an integer value: "); (void)scanf("%d", &x);
  assert(x >= 0); // 변수나 임의의 수식으로 false 경우 오류 메세지 뜸
  printf("You entered %d.", x);

  return(0);
}
#endif

#if 0 // 매크로 함수와 #line
#define Assert(x) { \
   if ((x) >= 4) printf("Range error : %s, %d\n", __FILE__, __LINE__);\
   }

int main(void)
{
  int a[4] = { 10,20,30,40 };
  for (int i = 0; i <= 4; ++i)
  {
#line 100 // 임의로 라인 번호 바꿈
    Assert(i);
    printf("a[%d] =%d\n", i, a[i]);
  }
}
#endif

#if 0 // #error 출력
#define SOUND_DEVICE_TYPE 1
int main(void)
{
#if SOUND_DEVICE_TYPE
  printf("Not using soung device.\n");
#else
#error CODE 10 : Unknown Device!
#endif
  printf("Sound mode = %d\n", SOUND_DEVICE_TYPE);
}
#endif

#if 0 // void 포인터의 사용 - swap or #define
#define SWAP(type, a, b) {type temp = a; a = b; b = temp;}
void swap(void* ap, void* bp, int size)
{
  char temp = 0;
  for (int i = 0; i < size; i++)
  {
    temp = ((char*)ap)[i];
    ((char*)ap)[i] = ((char*)bp)[i];
    ((char*)bp)[i] = temp;
  }
}
int main(void)
{
  int a = 10, b = 20;
  swap(&a, &b, sizeof(int));
  printf("a = %d, b = %d\n", a, b);
  SWAP(int, a, b);
  printf("a = %d, b = %d\n", a, b);
  return 0;
}
#endif

#if 0 // typedef 2
typedef char FARRY_10[10];  // char [10]
typedef FARRY_10 FARRY_10_2[];  // char[][10]
typedef FARRY_10* FARRY;   // char [10] *, char (*)[10]
typedef int (*FARRY_P) (FARRY, int size);
void printAry(FARRY ary, int size)
{
  for (int i = 0; i < size; i++) printf("%s ", ary[i]);
  printf("\n");
}
int main(void)
{
  FARRY_10_2 fruit = { "apple", "melon", "cherry" };
  FARRY_P fn = printAry;
  fn(fruit, SIZE(fruit));

  return 0;
}
#endif

#if 0 // typedef 1
typedef int i5ARR_t[5];
typedef i5ARR_t i5ARR3_t[3];

i5ARR_t* func(void);
int main(void)
{
  i5ARR_t x = { 1, 2, 3, 4, 5 };
  i5ARR3_t y = { { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4, 5 } };
  return 0;
}
#endif