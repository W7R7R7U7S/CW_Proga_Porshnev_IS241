#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/time.h>
#include "sort_lib.h"

#define SIZE_1 28
#define SIZE_2 216
#define STEP 4

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main() {
    // Загрузка библиотеки
    void* lib = dlopen("./libfsdyn.so", RTLD_LAZY);
    if (!lib) {
        printf("Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }
    
    // Получение указателей на функции сортировки
    void (*bubble_sort)(int[], int) = dlsym(lib, "bubble_sort");
    void (*quick_sort)(int[], int, int) = dlsym(lib, "quick_sort");
    if (!bubble_sort || !quick_sort) {
        printf("Ошибка получения указателей на функции: %s\n", dlerror());
        dlclose(lib);
        return 1;
    }
    
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    printf("Count\t      Bubble Sort    Quick Sort\n");

    for (int i = SIZE_1; i <= SIZE_2; i += STEP) {
        int* arr = (int*)malloc(i * sizeof(int));

        if (i == 216){i = 215;}
        printf("%d\t", i);
        for (int j = 0; j < i; j++) {
            arr[j] = getrand(28, 215);
        }

        double start, end;

        start = wtime();
        bubble_sort(arr, i);
        end = wtime() - start;
        printf("%15.7lf", end);

        start = wtime();
        quick_sort(arr, 0, i - 1);
        end = wtime() - start;
        printf("%15.7lf", end);

        printf("\n");

        free(arr);
    }

    // Выгрузка библиотеки
    dlclose(lib);

    return 0;
}
