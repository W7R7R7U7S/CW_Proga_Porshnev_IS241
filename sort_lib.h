#ifndef SORT_LIB_H
#define SORT_LIB_H

void bubble_sort(int arr[], int n);
void quick_sort(int *s_arr, int low, int high, int jopa);
void sortFromFile(const char *filename, void (**sort_func)(int[], int, int, int), int size, int step);
#endif