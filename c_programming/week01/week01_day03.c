#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>

#if 0 // 배열 포인터 - 권장X // &str : char (*)[80]
int main(void)
{
  int a = 0;
  scanf("%s", (char*)&a); printf("%s\n", (char*)&a);
  return 0;
}
#endif

#if 0 // 초기화 방법
int main(void)
{
  int a[10] = { 0, }; // { 0 }
  int b[10] = { [3] = 5,[7] = 100 };
  int c[5] = { [1] = 10, 20, 30 };
  
  return 0;
}
#endif

#if 0 // 합계 평균 구하기 - 정수 type의 문자열 배열
int main(void)
{
  int sum = 0, result = 0;
  int input[5] = { 0, };
  int count = sizeof(input) / sizeof(*input); // int count = sizeof(input) / sizeof(input[0]);

  for (int i = 0; i < count; i++)
  {
    scanf("%d", input + i); // scanf("%d", &input[i]);
    sum += input[i];
    printf("score %d: %d\n", i + 1, input[i]);
  }
  result = sum / count;
  printf("result: %d\n", result);
  
  return 0;
}
#endif

#if 0 // 2차원 배열과 2중 for문
int main(void)
{
  int a[2][5] = { 0, };
  for (int i = 0; i < 10; i++) scanf("%d", *a + i); // 아래와 동일하게 작동
  //for (int i = 0; i < 2; i++)
  //{
  //  for (int j = 0; j < 5; j++) scanf("%d", &a[i][j])
  //}
  return 0;
}
#endif