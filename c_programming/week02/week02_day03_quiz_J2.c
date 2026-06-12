#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 J2: 단지 번호 (BFS)
#define MAX_N (25 + 2)
int map[MAX_N][MAX_N];
int danji_arr[MAX_N * MAX_N / 2] = { 0 };
int danji_cnt = 0;
typedef struct _node
{
  int r, c;
}node;

node queue[MAX_N * MAX_N];
int front, rear;
int C, R;
int sC, sR, eC, eR;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void enqueue(node data)  // 한번에 주는 경우
{
  queue[rear++] = data;
}
node dequeue(void)
{
  return queue[front++];
}
void input_data(void)
{
  char temp[MAX_N] = { 0 };
  (void)scanf("%d", &C); R = C;
  for (int i = 1; i <= R; i++)
  {
    (void)scanf("%s", temp + 1);
    for (int j = 1; j <= C; j++)
    {
      map[i][j] = temp[j] - '0';
    }
  }
}
void print_data(void)  // 검증용
{
  for (int i = 1; i <= R; i++)
  {
    for (int j = 1; j <= C; j++)
    {
      printf("%d", map[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
int danji_bfs(int sR, int sC)
{
  node curr = { 0 };
  int nR, nC, count = 1;

  front = rear = 0;               // 큐 초기화
  enqueue((node) { sR, sC });     // 시작점 넣기
  map[sR][sC] = 0;                // 방문 표시

  while (front != rear)
  {
    curr = dequeue();
    for (int i = 0; i < 4; i++)
    {
      nR = curr.r + dr[i];
      nC = curr.c + dc[i];
      if (map[nR][nC] == 1) // 1이면 감
      {
        enqueue((node) { nR, nC });
        map[nR][nC] = 0;
        count++;
      }
    }
  }
  return count;
}
int compare(const void* a, const void* b)
{
  return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b);
}
int main(void)
{
  (void)freopen("week02_day02_quiz_J.txt", "r", stdin);  // 검증용
  input_data();
  print_data();  // 검증용

  danji_cnt = 0;
  for (int i = 1; i <= R; i++)
  {
    for (int j = 1; j <= C; j++)
    {
      if (map[i][j] != 1) continue;
      danji_arr[danji_cnt] = danji_bfs(i, j);
      danji_cnt++;
    }
  }
  
  qsort(danji_arr, danji_cnt, sizeof(int), compare);

  printf("%d\n", danji_cnt);
  for (int i = 0; i < danji_cnt; i++)
  {
    printf("%d\n", danji_arr[i]);
  }

  return 0;
}
#endif