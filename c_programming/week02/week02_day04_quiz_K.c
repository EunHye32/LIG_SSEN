#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 K: 에디터
#define MAX_SIZE (100000 + 500000 + 5)
char left_stack[MAX_SIZE];
char right_stack[MAX_SIZE];
int left_top = -1;
int right_top = -1;

// 초기 문자열을 Left Stack에 셋팅
void init_editor(const char* str)
{
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    left_stack[++left_top] = str[i];
  }
}
void print_editor()
{
  for (int i = 0; i <= left_top; i++)
  {
    putchar(left_stack[i]);
  }
  for (int i = right_top; i >= 0; i--)
  {
    putchar(right_stack[i]);
  }
  putchar('\n');
}
int main(void)
{
  freopen("week02_day04_quiz_K.txt", "r", stdin);  // 검증용

  char init_str[100005];
  (void)scanf("%s", init_str);

  init_editor(init_str);

  int M;
  (void)scanf("%d", &M);

  while (M--)
  {
    char cmd;
    scanf(" %c", &cmd); // 공백을 넣어 앞의 줄바꿈 문자 무시

    if (cmd == 'L')     // 커서를 한 문자 왼쪽으로 이동
    {
      if (left_top >= 0)
      {
        right_stack[++right_top] = left_stack[left_top--];
      }
    }
    else if (cmd == 'D')  // 커서를 한 문자 오른쪽으로 이동
    {
      if (right_top >= 0)
      {
        left_stack[++left_top] = right_stack[right_top--];
      }
    }
    else if (cmd == 'B')  // 커서 왼쪽의 문자를 삭제
    {
      if (left_top >= 0)
      {
        left_top--;
      }
    }
    else if (cmd == 'P')  // 커서 왼쪽에 문자 $를 추가
    {
      char ch;
      scanf(" %c", &ch);
      left_stack[++left_top] = ch;
    }
  }

  print_editor();

  return 0;
}
#endif