#ifndef __MY_ALLOC_H__
#define __MY_ALLOC_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE(x) (sizeof(x) / sizeof(x[0]))

void* create_array(int n, int size);
void read_array(int* arr, int n);
void print_array(int* arr, int n);
double get_mean(int* arr, int n);
int* read_array2(int* n);
void free_array(char** str, int n);

#endif