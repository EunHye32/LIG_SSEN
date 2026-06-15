#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1 // OJ 문제 O: 토마토 (고)
#define MAX_T (1002)
int M, N; // 상자의 가로 칸의 수, 세로 칸의 수
int tomato_c = 0;
int box[MAX_T][MAX_T] = { 0 };
typedef struct _node
{
  int x;
  int y;
}node;
node queue[MAX_T * MAX_T];
int front, rear;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
void enqueue(node data)
{
  queue[rear++] = data;
}
node dequeue(void)
{
  return queue[front++];
}
int tomato_BFS(void)
{
  node curr = { 0 };
  int last_day = 1;

  while (front != rear)
  {
    curr = dequeue();
    int x = curr.x;
    int y = curr.y;

    last_day = box[x][y];
    for (int i = 0; i < 4; i++)
    {
      int xt = x + dx[i];
      int yt = y + dy[i];
      if (xt < 1 || xt > N || yt < 1 || yt > M) continue; // 범위 초과 확인
      if (box[xt][yt] != 0) continue;   // 안 익은 토마토가 아니면 패스

      box[xt][yt] = box[x][y] + 1;
      tomato_c--;   // 안 익은 토마토 개수 차감
      enqueue((node) { xt, yt });
    }
  }
  return last_day - 1;
}
void input_data(void)
{
  front = rear = 0;
  (void)scanf("%d %d", &M, &N);
  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= M; j++)
    {
      (void)scanf("%d", &box[i][j]);
      if (box[i][j] == 1) enqueue((node) { i, j });
      else if (box[i][j] == 0) tomato_c++;
    }
  }
}
void print_data(void)  // 검증용
{
  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= M; j++)
    {
      printf("%d ", box[i][j]);
    }
    printf("\n");
  }
}
int main(void)
{
  freopen("week02_day04_quiz_O.txt", "r", stdin);  // 검증용
  input_data();
  print_data();   // 검증용

  if (tomato_c == 0)
  {
    printf("0"); return 0;
  }

  int days = tomato_BFS();
  if (tomato_c > 0)
  {
    printf("-1");
  }
  else
  {
    printf("%d", days);
  }

  return 0;
}
#endif