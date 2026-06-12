#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 U: 미로 탈출 (BFS)
#define MAX_N (100 + 2)
int map[MAX_N][MAX_N];
typedef struct _node
{
  int r, c;
  int dist;
}node;

node queue[MAX_N * MAX_N];
int front, rear;
int C, R;
int sC, sR, eC, eR;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void enqueue2(node data)  // 한번에 주는 경우
{
  queue[rear++] = data;
}
void enqueue1(int r, int c, int dist) // 1개씩 주는 경우
{
  queue[rear].r = r;
  queue[rear].c = c;
  queue[rear++].dist = dist;
}
node dequeue(void)
{
  return queue[front++];
}
void input_data(void)
{
  char temp[MAX_N];
  (void)scanf("%d %d %d %d %d %d", &C, &R, &sC, &sR, &eC, &eR);
  for (int i = 1; i <= R; i++)
  {
    (void)scanf("%s", temp + 1);
    for (int j = 1; j <= C; j++)
    {
      map[i][j] = !(temp[j] - '0');
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
int miro_dfs(int sR, int sC)
{
  node curr = { 0 };
  int nR, nC;

  front = rear = 0;               // 큐 초기화
  enqueue2((node) { sR, sC, 0 }); // 시작점 넣기
  map[sR][sC] = 2;                // 방문 표시 (2->3...)
  
  while (front != rear)
  {
    curr = dequeue();
    if (curr.r == eR && curr.c == eC) return curr.dist;
    for (int i = 0; i < 4; i++)
    {
      nR = curr.r + dr[i];
      nC = curr.c + dc[i];
      if (map[nR][nC] == 1) // 1이면 감
      {
        enqueue2((node) { nR, nC, curr.dist + 1 });
        map[nR][nC] = map[curr.r][curr.c] + 1;  //  방문 표시
      }
    }
  }
  return -1;  // 예외 처리
}
int main(void)
{
  (void)freopen("week02_day03_quiz_U.txt", "r", stdin);  // 검증용
  input_data();
  print_data();  // 검증용
  printf("%d", miro_dfs(sR, sC));
  return 0;
}
#endif