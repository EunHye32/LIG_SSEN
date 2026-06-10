#include "week02_reculsive.h"
#if 1 // 재귀호출
int N = 5; int C = 3;
void func14(int L)
{
  N = 3;
  static int ary_14[10] = { 0 };
  static int ary_14_used[10] = { 0 };
  if (L > N)
  {
    print_13_ary(ary_14, N);
    return;
  }
  for (int i = 1; i <= N; i++)
  {
    if (ary_14_used[i] != 0) continue;
    ary_14[i] = L; ary_14_used[i] = 1;
    func14(L + 1);
    ary_14_used[i] = 0;
  }

  /* for문 버전
  for (int i = 1; i <= 3; i++)
  {
    ary_14[1] = i; ary_14_used[i] = 1;
    for (int j = 1; j <= 3; j++)
    {
      if (ary_14_used[j] == 1) continue;
      ary_14[2] = j; ary_14_used[j] = 1;
      for (int k = 1; k <= 3; k++)
      {
        if (ary_14_used[k] == 1) continue;
        ary_14[3] = k; ary_14_used[k] = 1;
        printf("%d %d %d\n", ary_14[1], ary_14[2], ary_14[3]);
        ary_14_used[k] = 0;
      }
      ary_14_used[j] = 0;
    }
    ary_14_used[i] = 0;
  }
  */
}
void print_13_ary(int* ary, int n)
{
  for (int i = 1; i <= n; i++)
  {
    printf("%d ", ary[i]);
  }
  printf("\n");
}
void func13_1(int start, int L)
{
  static int ary_13_1[10] = { 0 };
  if (L > C)
  {
    print_13_ary(ary_13_1, C);
    return;
  }
  int end = N - (C - L);
  for (int i = start; i <= end; i++)
  {
    ary_13_1[L] = i;
    func13_1(i + 1, L + 1);
  }
}
void func13(int idx, int L)
{
  static int ary_13[10] = { 0 };
  if (L == C)
  {
    for (int i = 0; i < N; i++)
    {
      printf("%d ", ary_13[i]);
    }
    printf("\n");
    return;
  }
  int end = N - (C - L) + 1;      // 함수 호출 감소한 버전
  for (int i = idx; i < end; i++) // for (int i = idx; i < N; i++)
  {
    ary_13[i] = 1;
    func13(i + 1, L + 1);
    ary_13[i] = 0;
  }
}
void func12(int L)
{
  static int str_11_2[10] = { 0 };
  for (int i = 0; i < L - 1; i++)
  {
    str_11_2[0] = i + 1;
    for (int j = i + 1; j < L; j++)
    {
      str_11_2[1] = j + 1;
      printf("%d %d\n", str_11_2[0], str_11_2[1]);
    }
  }
}
void print_i_ary(int* ary, int L)
{
  for (int i = L - 1; i >= 0; i--)
  {
    printf("%d ", ary[i]);
  }
  printf("\n");
}
void func11(int L)
{
  int str_11[10] = { 0 };
  for (int i = 0; i < L - 1; i++)
  {
    for (int j = i + 1; j < L; j++)
    {
      print_i_ary(str_11, L);
      str_11[j] = 0;
    }
    str_11[i] = 0;
  }
}
void func10(int L)
{
  //static char str_10[10] = { 0 };
  //if (L > N)
  //{
  //  printf("%s\n", str_10);
  //  return;
  //}
  //str_10[L - 1] = '0';
  //func10(L + 1);
  //str_10[L - 1] = '1';
  //func10(L + 1);
  static char str_10[3] = { 0, 0, 0 };
  if (L >= N)
  {
    printf("%s\n", str_10);
    return;
  }
  for (int i = 0; i < 2; i++)
  {
    str_10[L] = '0' + i;
    func10(L + 1);
  }
}
void func9(int L)
{
  static char str_2[10] = { 0 };
  if (L > N) return;
  str_2[L - 1] = '*';
  func9(L + 1);
  str_2[L] = '\0';
  printf("%s\n", str_2);
}
//char* str[] = { "*", "**", "***", "****", "*****" }; // V2
void func8(int L)
{
  if (L > N) return;
  // V3. static 사용
  static char str_2[10] = { 0 };
  str_2[L - 1] = '*';
  printf("%s\n", str_2);
  // V2. 배열 사용
  //printf("%s\n", str[L - 1]);
  // V1. for문 사용
  //for (int i = 0; i < L; i++) printf("*");
  //printf("\n");
  func8(L + 1);
}
void func7(int L) // 1 2 3 4 5 1 2 3 4 5
{
  if (L > N) return;
  printf("%d ", L);
  func7(L + 1);
  printf("%d ", (N + 1) - L);
}
void func6(int L) // 1 2 3 4 5 4 3 2 1
{
  printf("%d ", L);
  if (L >= N) return;
  func6(L + 1);
  printf("%d ", L);
}
void func5(int L)
{
  if (L > N) return;
  printf("%d ", L);
  func5(L + 1);
  printf("%d ", L);
}
// 출력이 되지 않음. 재귀호출이 return 되지 않기 때문.
void func3(int L)
{
  func3(L + 1);
  printf("%d\n", L);
}
void func4(int L)
{
  if (L >= N) return;
  printf("%d\n", L);
  func4(L + 1);
}
// 로컬 변수를 많이 갖는 것 (배열 등)은 재귀 호출 횟수를 감소시킴
void func2(int L)
{
  int arr[10] = { 0 };
  printf("%d\n", L);
  func2(L + 1);
}
void func1(int L)
{
  printf("%d\n", L);
  func1(L + 1);
}
#endif