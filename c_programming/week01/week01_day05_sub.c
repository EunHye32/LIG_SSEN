#include <stdio.h>

#if 0 // with static 2 code
// extern 변수는 초기화 하지 말기
// !초기화 X : 다른 파일에서 선언한거를 extern 사용 시 선언하듯 사용하면 X
//extern int a = 100;
extern int a; // -> 옳은 표현
int func(void)
{
  a = 100;
  printf("a = %d\n", a);
  return a;
}
#endif