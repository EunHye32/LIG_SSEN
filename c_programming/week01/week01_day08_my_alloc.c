#include "day08_my_alloc.h"
void* create_array(int n, int size)
{
  void* temp = calloc(n, size);
  if (!temp)
  {
    printf("leak of memory!\n");
    exit(1);
  }
  return temp;
}
void read_array(int* arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
}
void print_array(int* arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
double get_mean(int* arr, int n)
{
  int tot = arr[0];
  for (int i = 1; i < n; i++) tot += arr[i];
  return tot / (double)n;
}
#if 1 // realloc
int* read_array2(int* n)
{
  int* pi = NULL;
  int data = 0, N = 0, i = 0;
  for (i = 0; scanf("%d", &data) && data > 0; i++)
  {
    if (N == i)
    {
      N += 3;
      int* temp = (int*)realloc(pi, N * sizeof(int));
      if (temp == NULL)
      {
        printf("Leak of memory!\n");
        free(pi);
        pi = NULL;
        return NULL;
      }
      pi = temp;
    }
    pi[i] = data;
    printf("N = %d, pi[count] = %d\n", N, pi[i]);
  }
  *n = i;
  int* temp = (int*)realloc(pi, sizeof(int) * i); // 메모리 크기를 i개 데이터 저장가능한 크기로 줄임
  if (temp != NULL) pi = temp;
  return pi;
}
#endif
#if 1 // string malloc
void free_array(char** str, int n)
{
  for (int i = 0; i < n; i++)
  {
    free(str[i]);
  }
  free(str);
  str = NULL;
}
#endif