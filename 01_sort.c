#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Вспомогательная функция для вывода на экран массива размера n*/
void printArrayQuick(int *arr, int n)
{
    FILE *fout;
    fout = fopen("quicksort.log", "a+");
    for (int i = 0; i < n; ++i)
        fprintf(fout, "%d ", arr[i]);
    fprintf(fout, "\n");
    fclose(fout);
}

void printArrayHeap(int *arr, int n)
{
    FILE *fout;
    fout = fopen("heapsort.log", "a+");
    for (int i = 0; i < n; ++i)
        fprintf(fout, "%d ", arr[i]);
    fprintf(fout, "\n");
    fclose(fout);
}

void quickSort(int *array, int left, int right)
{
    int *tempArr = (int *)malloc(sizeof(array) * sizeof(int));
    tempArr = array;
    int i = left;
    int j = right;
    printArrayQuick(array, sizeof(array));
    int privot = array[right + (left - right) / 2];
    do
    {
        while (array[i] < privot)
            i++;
        while (array[j] > privot)
            j--;
        if (i <= j)
        {
            if (array[i] > array[j])
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            i++;
            if (j > 0)
                j--;
        }
    } while (i <= j);
    if (i < right)
        quickSort(array, i, right);
    if (j > left)
        quickSort(array, left, j);
}

// Функция "просеивания" через кучу - формирование кучи
void siftDown(int *numbers, int root, int bottom, int size)
{
    printArrayHeap(numbers, size);
    int maxChild; // индекс максимального потомка
    int done = 0; // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom)  // если мы в последнем ряду,
            maxChild = root * 2; // запоминаем левый потомок
        // иначе запоминаем больший потомок из двух
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (numbers[root] < numbers[maxChild])
        {
            int temp = numbers[root]; // меняем их местами
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else          // иначе
            done = 1; // пирамида сформирована
    }
}

// Функция сортировки на куче
void heapSort(int *numbers, int array_size)
{
    // Формируем нижний ряд пирамиды
    for (int i = (array_size / 2); i >= 0; i--)
    {
        siftDown(numbers, i, array_size - 1, array_size);
    }
    // Просеиваем через пирамиду остальные элементы
    for (int i = array_size - 1; i >= 1; i--)
    {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1, array_size);
    }
}

int main()
{
    int size;
    scanf("%d", &size);
    int *arr = (int *)malloc(size * sizeof(int));
    int *arr2 = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }
    quickSort(arr, 0, size - 1);
    heapSort(arr2, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
// end.
