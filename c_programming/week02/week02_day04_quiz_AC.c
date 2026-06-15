#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0 // OJ 문제 AC: N-Queen
int N, result;
int* board;

int check_queen(int row) {
  for (int i = 0; i < row; i++)
  {
    // 같은 열에 퀸이 있는지 확인 + 대각선에 퀸이 있는지 확인 (행의 차이 == 열의 차이)
    if (board[row] == board[i] || abs(board[row] - board[i]) == (row - i))
    {
      return 0; // 놓을 수 없음 (가지치기)
    }
  }
  return 1;     // 안전함
}
void nqueen_DFS(int row)
{
  //for (int i = 0; i < N; i++) printf("%d ", board[i]);  // 검증용
  //printf(" result : %d\n", result);  // 검증용
  if (row == N)
  {
    result++;
    return;
  }

  for (int col = 0; col < N; col++)
  {
    board[row] = col;

    if (check_queen(row))
    {
      nqueen_DFS(row + 1);
    }
  }
}
void input_data(void)
{
  (void)scanf("%d", &N);
}
int main(void)
{
  freopen("week02_day04_quiz_AC.txt", "r", stdin);   // 검증용
  input_data();
  board = (int*)calloc(N, sizeof(board[0]));

  nqueen_DFS(0);
  printf("%d", result);

  free(board);
  return 0;
}
#endif