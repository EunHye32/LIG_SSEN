#include <stdio.h>
#include <string.h>

#if 0 // static 2 with file "day05_sub.c"
// 다른 파일에서도 사용할 수 있도록 하는 변수는 명시적 초기화
int a = 0; // !초기화 해줘야함
int main(void)
{
  printf("%d\n", a);
  func();
  return 0;
}
#endif

#if 0 // static 1
int a = 10; // 데이터 영역의 .data 영역 사용
int a;      // 데이터 영역의 .bss 영역 사용 --> 초기화되는 값이 들어가는 메모리
// const int a = 50; // X : 재정의 오류
int main(void)
{
  printf("%d\n", a); // stack
  return 0;
}
#endif

#if 0 // strcat, strncpy
char* my_strcat(char* s1, const char* s2)
{
  char* save = s1;

  for (;*s1; s1++); // while (*++s1);
  while (*s1++ = *s2++);

  return save;
}
char* my_strncpy(char* s1, const char* s2, int n)
{
  if (!n) return s1;
  
  char* s1_save = s1;
  const char* s2_save = s2;
  do
  {
    if (!(*s1_save++ = *s2_save++))
    {
      while (--n) *s1_save++ = 0;
      break;
    }
  } while (--n);

  return s1;
}
int main(void)
{
  char name[30] = "EunHye";
  printf("%s\n", my_strcat(name, "EunHye"));
  printf("%s\n", my_strncpy(name, "KimEunHye", 3));
  return 0;
}
#endif

#if 0 // strcmp
int my_strcmp(const char* s1, const char* s2)
{
  for (; *s1 == *s2; s1++, s2++)
  {
    if (!(*s1)) return 0;
  }
  // (*(const char*)s1 > *(const char*)s2) * 2 - 1;
  return (*(unsigned const char*)s1 > *(unsigned const char*)s2) - (*(unsigned const char*)s1 < *(unsigned const char*)s2);
}
int main(void)
{
  char name[30] = "EunHye";
  printf("%d\n", my_strcmp(name, "EunHye"));
  printf("%d\n", strcmp(name, "EunHye"));
  return 0;
}
#endif

#if 0 // strcpy, strlen
char* my_strcpy(char* to, const char* from)
{
  char* save = to;
  for (; (*to++ = *from++);); // for (; (*to = *from); from++, to++);
  return save;
}
int my_strlen(const char* str)
{
  const char* s;

  if (str == 0) return 0;
  for (s = str; *s; ++s);
  return s - str;
}
int main(void)
{
  char name[30];
  printf("%s\n", my_strcpy(name, "EunHye"));
  printf("%d\n", my_strlen(name));
  return 0;
}
#endif

#if 0 // 입력받기(모두 끝에는 널) - scanf, gets, fgets
int main(void)
{
  char str[30];
  // scanf("%s", str);
  // gets(str); // 공백 포함됨
  fgets(str, sizeof(str), stdin); // 엔터 포함됨
  printf("%s\nThe End!\n", str);
  return 0;
}
#endif