#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#if 0 // 2차원 배열 입출력
#define SIZE(x) (sizeof(x) / sizeof(x[0]))
void get_array(char (*p)[10], int size)
{
  if (p == NULL) return;
  for (int i = 0; i < size; i++)
  {
    //(void)scanf("%s", p[i]);  // char (*p)[10]
    //(void)scanf("%s", p[i]);  // char (*p)[10]
    (void)scanf("%s", p[i]);    // char *p  --> 이렇게 작성해야 함
  }
}
void get_array2(char** p, int size)
{
  if (p == NULL) return;

  for (int i = 0; i < size; i++) (void)scanf("%s", p[i]);
}
void print_array(char (*p)[10], int size)
{
  for (int i = 0; i < size; i++) printf("%s ", p[i]);
  printf("\n");
}
void print_array2(char** p, int size)
{
  for (int i = 0; i < size; i++) printf("%s ", p[i]); // *(p + i)
  printf("\n");
}
int main(void)
{
  char animals[5][10] = { "rabbit" }; // 2차원 배열
  char (*p)[10] = animals;            // 배열 포인터
  char* arr[5] = { animals[0], animals[1], p[2], p[3], p[4] };  // 포인터 배열
  //printf("%s %s %s\n", animals[0], p[0], arr[0]);

  (void)freopen("day_06_1_animals.txt", "r", stdin);
  //get_array(animals, SIZE(animals));
  get_array2(arr, SIZE(animals));
  print_array(animals, SIZE(animals));
  print_array2(arr, SIZE(animals));
  return 0;
}
#endif

#if 0 // freopen - with day06_1_score.txt
#define SIZE(x) (sizeof(x) / sizeof(x[0]))

void getArray(int (*score)[4], int r);
void printArray(int (*score)[4], int r, int c);
void what(int (*score)[3][4])
{
  printf("%d %d %d\n", sizeof(score), sizeof(*score), sizeof(**score)); // 4 48 16
  int r = SIZE(*score);
  int c = SIZE(**score);
  int n = r * c;

  for (int i = 0; i < n; i++) printf("%d ", *((int*)score + i));
  printf("\n");
}
void print_sum_avg(int (*score)[4], int r, int c)
{
  int sum;
    for (int i = 0; i < r; i++)
    {
      sum = 0;
      for (int j = 0; j < c; j++) sum += score[i][j];
      printf("total : %d, avg : %.2f\n", sum, sum / (float)c);
    }
}
int main(void)
{
  int score[3][4] = { 0 };
  (void)freopen("day06_1_score.txt", "r", stdin);
  getArray(score, 3);
  printArray(score, 3, 4); // 인자로 넘겨주는 방식을 더 선호함
  what(&score); // 요소의 개수까지 안 넘겨줘도 됨

  print_sum_avg(score, 3, 4); // 3명의 총점과 평균을 구해 출력

  return 0;
}
void getArray(int (*score)[4], int r)
{
  if (score == NULL) return;

  int c = SIZE(*score);
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++) (void)scanf("%d", &score[i][j]);
  }
}
void printArray(int (*score)[4], int r, int c)
{
  if (score == NULL) return;

  for (int i = 0; i < r * c; i++) printf("%d ", *((int*)score + i));
  printf("\n");
}
#endif