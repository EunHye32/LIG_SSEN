#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 H: 바이러스 (인접 리스트, 인접 행렬)
#define MAX_N (100 + 2)
int mat[MAX_N][MAX_N] = { 0 };
int used[MAX_N] = { 0 };
int V, count;
void input_data1(void) // 인접 행렬
{
  int E, a, b;
  (void)scanf("%d %d", &V, &E);
  for (int i = 0; i < E; i++)
  {
    (void)scanf("%d %d", &a, &b);
    mat[a][b] = 1;
    mat[b][a] = 1;
  }
}
void input_data2(void) // 인접 리스트
{
  int E, a, b, temp;
  (void)scanf("%d %d", &V, &E);
  for (int i = 0; i < E; i++)
  {
    (void)scanf("%d %d", &a, &b);
    temp = ++mat[a][0]; mat[a][temp] = b;
    temp = ++mat[b][0]; mat[b][temp] = a;
  }
}
void print_data1(int s, int e)
{
  for (int i = s; i <= e; i++)
  {
    for (int j = s; j <= e; j++)
    {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
void print_data2(int s, int e)
{
  for (int i = s; i <= e; i++)
  {
    for (int j = s; j <= mat[i][0]; j++)
    {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
void check_func1(int current) // 감염된 PC에서 인접한 감염되지 않은 PC를 감염시키는 함수
{
  for (int i = 1; i <= V; i++) // i: PC 번호
  {
    if ((mat[current][i] == 1) && (used[i] == 0))
    {
      used[i] = 1;
      count++;
      check_func1(i);
    }
  }
}
void check_func2(int current)
{
  for (int i = 1; i <= mat[current][0]; i++)
  {
    int next = mat[current][i];
    if (used[next] == 0)
    {
      used[next] = 1;
      count++;
      check_func2(next);
    }
  }
}
#if 1 // 인접 리스트
int main(void)
{
  (void)freopen("day02_quiz_H.txt", "r", stdin); // 검증용
  input_data2();
  print_data2(1, V); // 검증용

  used[1] = 1;
  count = 0;
  check_func2(1);
  printf("%d\n", count);

  return 0;
}
#endif
#if 0 // 인접 행렬
int main(void)
{
  (void)freopen("week02_day02_quiz_H.txt", "r", stdin); // 검증용
  input_data1();
  print_data1(1, V); // 검증용

  used[1] = 1;
  check_func1(1);
  printf("%d\n", count);

  return 0;
}
#endif
#endif