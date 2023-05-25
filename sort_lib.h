#ifndef SORT_LIB_H
#define SORT_LIB_H

void bubble_sort(int arr[], int n);
void quick_sort(int arr[], int low, int high);
void sortFromFile(const char* filename, void(*sort_func)(int[], int, int), int size);

#endif