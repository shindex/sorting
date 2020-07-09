#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void swap(int data[], int i, int j) {
  int temp = data[i];
  data[i] = data[j];
  data[j] = temp;
}


void quick(int data[], int left, int right) {
  int i = left;
  int j = right;
  
  //int pivot = data[left];
  int pivot = (data[left] + data[right]) / 2;
  
  while (1) {
    while (data[i] < pivot) i++;
    while (pivot < data[j]) j--;
    if (i >= j) break;
    swap(data, i, j);
    i++;
    j--;
  }

  if (left < i - 1)  quick(data, left, i - 1);
  if (j + 1 < right) quick(data, j + 1, right);
}


void sort(int data[], int n, int dir) {
  int i;
  
  clock_t start = clock();
  quick(data, 0, n - 1);
  clock_t end = clock();

  switch (dir) {
    case 0:
      for (i = 0; i < n; i++) {
        printf("%d\n", data[i]);
      }
      break;
    case 1:
      for (i = n; i >= 0; i--) {
        printf("%d\n", data[i]);
      }
      break;
  }

  double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
  printf("time %lf[ms]\n", time);
}


int main(int argc, char *argv[])    
{
  FILE *fp;
  int *data;
  int i, readValue, chk_opt;
  int n = 100000;
  int dir = 0;

  while ((chk_opt = getopt(argc, argv, "adf:n:")) != -1) {
    switch (chk_opt) {
      case 'f':
        fp = fopen(optarg, "r");
        break;
      case 'n':
        sscanf(optarg, "%d", &n);
        break;
      case 'a':
        dir = 0;
        break;
      case 'd':
        dir = 1;
        break;
    }
    optarg = NULL;
  }

  if (fp == NULL) {
    puts("File Open Error"); 
    return 0;
  }

  data = malloc((n) * sizeof(int));
  for (i = 0; i < n; i++) {
	  fscanf(fp, "%d", &readValue);
	  data[i] = readValue;
  }

  sort(data, n, dir);

  fclose(fp);
  return 0;
}