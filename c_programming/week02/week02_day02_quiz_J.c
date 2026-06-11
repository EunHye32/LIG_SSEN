#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 J: 단지 번호
#define MAX_SIZE (25 + 2)
int map[MAX_SIZE][MAX_SIZE] = { 0 };  // 입력배열 + 방문표시
int map_size;
int danji_arr[MAX_SIZE * MAX_SIZE / 2] = { 0 };
int danji_cnt = 0;
int dx[] = {-1, 1, 0, 0};
int dy[] = { 0, 0, -1, 1 };

void input_data(void) // 대용량의 입력값이 들어올때는 scanf(%1d) 보다 문자열로 입력 받는 게 더 빠름
{
  char temp[MAX_SIZE] = { 0 };
  (void)scanf("%d", &map_size);
  for (int i = 1; i <= map_size; i++)
  {
    (void)scanf("%s", temp + 1);
    for (int j = 1; j <= map_size; j++)
    {
      map[i][j] = temp[j] - '0';
    }
  }
}
void print_data(void)
{
  for (int i = 1; i <= map_size; i++)
  {
    for (int j = 1; j <= map_size; j++)
    {
      printf("%d", map[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
void ouput_data(void)
{
  printf("%d\n", danji_cnt);
  for (int i = 0; i < danji_cnt; i++)
  {
    printf("%d\n", danji_arr[i]);
  }
}
void danji(int x, int y)  // 집(x, y)에서 인접한 집을 찾는 함수
{
  int nx = 0, ny = 0;
  ++danji_arr[danji_cnt];
  for (int i = 0; i < 4; i++)
  {
    nx = x + dx[i];
    ny = y + dy[i];
    if (map[nx][ny] == 1)
    {
      map[nx][ny] = 2;
      danji(nx, ny);
    }
  }
}
int compare(const void* a, const void* b)
{
  return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b);
}
int main(void)
{
  (void)freopen("week02_day02_quiz_J.txt", "r", stdin); // 검증용
  input_data();
  print_data(); // 검증용
  danji_cnt = 0;
  for (int i = 1; i <= map_size; i++)
  {
    for (int j = 1; j <= map_size; j++)
    {
      if (map[i][j] != 1) continue;
      map[i][j] = 2;
      danji(i, j);
      danji_cnt++;
    }
  }
  print_data(); // 검증용
  qsort(danji_arr, danji_cnt, sizeof(int), compare);
  ouput_data();

  return 0;
}
#endif