#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "sort_lib.h"

#define SIZE_1 32768
#define STEP 1024

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sortFromFile(const char *filename, void (**sort_func)(int[], int, int, int), int size, int step)
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

    printf("Count     Quick          Bubble\n");
    for (int currSize = 256; currSize <= size; currSize += step)
    {
        double start_time, end_time;
        double sort_times[2];

        // Создаем копии массива для каждой сортировки
        int *arr_bubble = (int *)malloc(currSize * sizeof(int));
        int *arr_quick = (int *)malloc(currSize * sizeof(int));

        // Копируем исходный массив в копии
        memcpy(arr_bubble, arr, currSize * sizeof(int));
        memcpy(arr_quick, arr, currSize * sizeof(int));

        // Сортировка пузырьком
        start_time = wtime();
        (*sort_func[0])(arr_bubble, 0, currSize - 1, 0);
        end_time = wtime();
        sort_times[0] = end_time - start_time;

        // Сортировка быстрая
        start_time = wtime();
        (*sort_func[1])(arr_quick, currSize, 0, currSize - 1);
        end_time = wtime();
        sort_times[1] = end_time - start_time;

        printf("%d\t%.6f\t%.6f\n", currSize, sort_times[0], sort_times[1]);

        // Освобождаем память
        free(arr_bubble);
        free(arr_quick);
    }

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
    void (*bubble_sort)(int[], int, int, int) = dlsym(lib, "bubble_sort");
    void (*quick_sort)(int[], int, int, int) = dlsym(lib, "quick_sort");
    if (!bubble_sort || !quick_sort)
    {
        printf("Ошибка получения указателей на функции: %s\n", dlerror());
        dlclose(lib);
        return 1;
    }

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

        int *arr_bubble = (int *)malloc(size * sizeof(int));
        int *arr_quick = (int *)malloc(size * sizeof(int));

        printf("Введите элементы массива:\n");
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &arr_bubble[i]);
            arr_quick[i] = arr_bubble[i];
        }

        printf("Исходный массив:\n");
        printArray(arr_bubble, size);

        printf("Сортировка пузырьком:\n");
        bubble_sort(arr_bubble, size, size, 0);
        printArray(arr_bubble, size);

        printf("Сортировка быстрая:\n");
        quick_sort(arr_quick, 0, size - 1, 0);
        printArray(arr_quick, size);

        free(arr_bubble);
        free(arr_quick);
    }
    else if (mode == 2)
    {
        // Режим ввода из файла
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
            void (*sort_funcs[2])(int[], int, int, int) = {quick_sort, bubble_sort};
            sortFromFile(filenames[fileNum - 1], sort_funcs, SIZE_1, STEP);
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