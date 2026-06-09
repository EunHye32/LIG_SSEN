#include <stdio.h>
#if 0 // extern
// 경고 안뜨게 하기 위해 다른 파일에 있는 사용할 함수 선언해줘야 함
void Increment(void);
int GetNum(void);

int main(void)
{
  printf("num : %d\n", GetNum());
  Increment();
  printf("num : %d\n", GetNum());
  Increment();
  printf("num : %d\n", GetNum());

  return 0;
}
#endif