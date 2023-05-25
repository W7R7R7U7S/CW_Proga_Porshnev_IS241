#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/time.h>
#include "sort_lib.h"

#define SIZE_1 33024
#define SIZE_2 33024
#define STEP 1024

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

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sortFromFile(const char *filename, void (*sort_func)(int[], int, int), int size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла.\n");
        return;
    }

    int *arr = (int *)malloc(size * sizeof(int));

    int i = 0;
    int num;
    while (fscanf(file, "%d", &num) == 1 && i < size)
    {
        arr[i++] = num;
    }
    fclose(file);

    sort_func(arr, 0, size - 1);

    printf("Отсортированный массив:\n");
    printArray(arr, size);

    free(arr);
}

int main()
{
    // Загрузка библиотеки
    void *lib = dlopen("./libfsdyn.so", RTLD_LAZY);
    if (!lib)
    {
        printf("Ошибка загрузки библиотеки: %s\n", dlerror());
        return 1;
    }

    // Получение указателей на функции сортировки
    void (*bubble_sort)(int[], int) = dlsym(lib, "bubble_sort");
    void (*quick_sort)(int[], int, int) = dlsym(lib, "quick_sort");
    if (!bubble_sort || !quick_sort)
    {
        printf("Ошибка получения указателей на функции: %s\n", dlerror());
        dlclose(lib);
        return 1;
    }

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    printf("Выберите режим:\n");
    printf("1. Ввод с клавиатуры\n");
    printf("2. Сортировка файла\n");

    int mode;
    scanf("%d", &mode);

    if (mode == 1)
    {
        printf("Введите размер массива: ");
        int size;
        scanf("%d", &size);

        int *arr = (int *)malloc(size * sizeof(int));

        printf("Введите элементы массива:\n");
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &arr[i]);
        }

        printf("Исходный массив:\n");
        printArray(arr, size);

        bubble_sort(arr, size);

        printf("Отсортированный массив:\n");
        printArray(arr, size);

        free(arr);
    }
    else if (mode == 2)
    {
        printf("Выберите файл для сортировки:\n");
        printf("1. sorted_numbers_ascending.txt\n");
        printf("2. sorted_numbers_descending.txt\n");
        printf("3. sorted_numbers_random.txt\n");

        int fileNum;
        scanf("%d", &fileNum);

        const char *filenames[] = {
            "sorted_numbers_ascending.txt",
            "sorted_numbers_descending.txt",
            "sorted_numbers_random.txt"};

        if (fileNum >= 1 && fileNum <= 3)
        {
            sortFromFile(filenames[fileNum - 1], quick_sort, SIZE_1);
        }
        else
        {
            printf("Неверный выбор файла.\n");
        }
    }
    else
    {
        printf("Неверный режим.\n");
    }

    // Выгрузка библиотеки
    dlclose(lib);

    return 0;
}