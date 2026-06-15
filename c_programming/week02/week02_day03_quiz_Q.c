#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 Q: 등산로 (BFS)
#define MAX_N (100 + 2)
int map[MAX_N][MAX_N];  // 산의 지형
int cost[MAX_N][MAX_N]; // 각 지점까지의 최소비용(걸린 힘)
int N;      // 산의 크기
int tR, tC; // 산의 꼭대기 위치
typedef struct _node
{
  int r, c;
}node;

node queue[MAX_N * MAX_N * 10];
int front, rear;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void enqueue(node data)
{
  queue[rear++] = data;
}
node dequeue(void)
{
  return queue[front++];
}
void input_data(void)
{
  (void)scanf("%d %d %d", &N, &tR, &tC);
  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= N; j++)
    {
      (void)scanf("%d", &map[i][j]);
    }
  }
  memset(cost, 0x0F, sizeof(cost)); // 큰 값으로 초기화
}
void init_queue(void)
{
  front = rear = 0;
  for (int i = 1; i <= N; i++)
  {
    enqueue((node) { 1, i });
    cost[1][i] = map[1][i] * map[1][i];
    enqueue((node) { N, i });
    cost[N][i] = map[N][i] * map[N][i];
  }
  for (int i = 2; i < N; i++)
  {
    enqueue((node) { i, 1 });
    cost[i][1] = map[i][1] * map[i][1];
    enqueue((node) { i, N });
    cost[i][N] = map[i][N] * map[i][N];
  }
}
void mount_BFS(void)
{
  node curr;
  int nR, nC, cR, cC;
  int diff, m_cost;

  while (front != rear)
  {
    curr = dequeue();
    cR = curr.r;
    cC = curr.c;

    for (int i = 0; i < 4; i++)
    {
      nR = cR + dr[i];
      nC = cC + dc[i];

      //if (nR < 1 || nR > N || nC < 1 || nC > N) continue;  // 맵 범위 벗어나면 패스
      if (map[nR][nC] == 0) continue;

      diff = map[nR][nC] - map[cR][cC];         // 높이 차이 계산
      if (diff > 0)     // 오르막길
      {
        m_cost = diff * diff;
      }
      else              // 평지 또는 내리막길
      {
        m_cost = -diff; // 음수인 diff를 양수로 변환
      }
      // (현재까지의 비용 + 이동 비용)이 (기록된 다음 칸의 비용)보다 작으면 갱신
      if (cost[cR][cC] + m_cost < cost[nR][nC])
      {
        cost[nR][nC] = cost[cR][cC] + m_cost;
        enqueue((node) { nR, nC });
      }
    }
  }
}
void print_data(int (*arr)[MAX_N], int s, int e)  // 검증용
{
  for (int i = s; i <= e; i++)
  {
    for (int j = s; j <= e; j++)
    {
      if (arr[i][j] == 0x0F0F0F0F)
      {
        printf(" - ");
      }
      else
      {
        printf("%2d ", arr[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

int main(void)
{
  (void)freopen("week02_day03_quiz_Q.txt", "r", stdin);  // 검증용
  input_data();
  print_data(map, 1, N);        // 검증용
  print_data(cost, 0, N + 1);   // 검증용
  init_queue();
  print_data(cost, 0, N + 1);   // 검증용

  mount_BFS();
  printf("%d\n", cost[tR][tC]);

  return 0;
}
#endif