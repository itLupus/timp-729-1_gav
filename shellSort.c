#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printFile(int *arr, int size, char *fileName)
{
  FILE *fout;
  fout = fopen(fileName, "a+");
  for (int i = 0; i < size; ++i)
    fprintf(fout, "%d ", arr[i]);
  fprintf(fout, "\n");
  fclose(fout);
}

void printInfoFile(int size, int operations, double sec, char *fileName)
{
  FILE *fout;
  fout = fopen(fileName, "a+");
  fprintf(fout, "========\n");
  fprintf(fout, "SIZE: %d\n OPERATIONS: %d\n SEC: %f\n", size, operations, sec);
  fprintf(fout, "========\n");
  fprintf(fout, "\n");
  fclose(fout);
}

void printInfoFileAverage(int size, int operations, double sec, char *fileName)
{
  FILE *fout;
  fout = fopen(fileName, "a+");
  fprintf(fout, "========\n");
  fprintf(fout, "SIZE: %d\n\tAVERAGE_SIZE: %d\n", size, size);
  fprintf(fout, "OPERATIONS: %d\n\tAVERAGE_OPERATIONS: %f\n", operations, (double)operations / 1000);
  fprintf(fout, "SECONDS: %f\n\tAVERAGE_SECONDS: %f\n", sec, sec / 1000);
  fprintf(fout, "========\n");
  fprintf(fout, "\n");
  fclose(fout);
}

int shellSort(int *array, int size){
  int cnt = 0;
    for(int s=size/2; s>0; s/=2){
        for(int i=0; i<size; i++){
            for(int j=i+s; j<size; j+=s){
                if(array[i] > array[j]){
                    int temp = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                    cnt++;
                    printFile(array, size, "shellSort.log");
                }
            }
        }
    }
  return cnt;
}


int main()
{
  int *arr = NULL;
  int size;
  int operations = 0;
  double sumTime = 0.0;
  scanf("%d", &size);
  for(int k = 0; k < 1000; k++){
    for (int i = 0; i < size; i++)
    {
      arr = (int *)realloc(arr, size * sizeof(int));
      arr[i] = rand() % 100;
    }
    clock_t time;
    time = clock();
    operations += shellSort(arr, size);
    time = clock() - time;
    double timeSec  = ((double)time)/CLOCKS_PER_SEC;
    printInfoFile(size, operations, timeSec, "shellSort.log");
    sumTime += timeSec;
  }
  printInfoFileAverage(size, operations, sumTime, "shellSortInfo.log");
  return 0;
}
