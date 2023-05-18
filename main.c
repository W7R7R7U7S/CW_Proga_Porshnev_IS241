#include <stdio.h>
#include <dlfcn.h>
#include "sort_lib.h"
int main() {
    // Загрузка библиотеки
    void* lib = dlopen("./libsort.so", RTLD_LAZY);
    if (!lib) {
        printf("Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;    }
    // Получение указателей на функции сортировки
    void (*bubble_sort)(int[], int) = dlsym(lib, "bubble_sort");
    void (*quick_sort)(int[], int, int) = dlsym(lib, "quick_sort");
    if (!bubble_sort || !quick_sort) {
        printf("Ошибка получения указателей на функции: %s\n", dlerror());
        dlclose(lib);
        return 1;
    }
    // Пример использования функций сортировки
    int arr[] = {5, 2, 8, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Исходный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Сортировка методом пузырька
    bubble_sort(arr, n);
    printf("Отсортированный массив (метод пузырька): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Сортировка быстрым методом
    quick_sort(arr, 0, n - 1);
    printf("Отсортированный массив (быстрая сортировка): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Выгрузка библиотеки
    dlclose(lib);
    return 0;
}