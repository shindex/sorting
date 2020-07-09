#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LEFT_CHILD(i)  (((i) + 1) * 2 - 1)
#define RIGHT_CHILD(i) (((i) + 1) * 2)
#define PARENT(i)      (((i) + 1) / 2 - 1)

void swap(int arr[], int a, int b) {
  double tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

void upheap(int arr[], int n) {
  while (n > 0) {
    int m = PARENT(n);

    if (arr[m] < arr[n]) {
      swap(arr, m, n);
    } else {
      break;
    }
    n = m;
  }
}

void downheap(int arr[], int n) {
    int m = 0;
    int tmp = 0;

    for (;;) {
        int l_chld = LEFT_CHILD(m);
        int r_chld = RIGHT_CHILD(m);

        if (l_chld >= n) {
            break;
        }

        if (arr[l_chld] > arr[tmp]) {
            tmp = l_chld;
        }
        if ((r_chld < n) && (arr[r_chld] > arr[tmp])) {
            tmp = r_chld;
        }

        if (tmp == m) {
            break;
        }
        swap(arr, tmp, m);

        m = tmp;
    }
}


void sort(int arr[], int length, int dir)
{
    int i = 0;

    clock_t start = clock();
    while (++i < length) {
        upheap(arr, i);
    }

    while (--i > 0) {
        swap(arr, 0, i);
        downheap(arr, i);
    }
    clock_t end = clock();

    /*
    switch (dir) {
    case 0:
      for (i = 0; i < length; i++) {
        printf("%d\n", arr[i]);
      }
      break;
    case 1:
      for (i = length; i >= 0; i--) {
        printf("%d\n", arr[i]);
      }
      break;
    }
    */

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