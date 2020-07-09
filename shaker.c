#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void shaker(int data[], int left, int right) {
  int i, n, m;
  int newLeft, newRight;

  for (i = left; i < right - 1; i++) {
    n = data[i];
    m = data[i + 1];
    if (n > m) {
      data[i + 1] = n;
      data[i] = m;
      newRight = i;
    }
  }
  for (i = newRight; i > left; i--) {
    n = data[i - 1];
    m = data[i];
    if (n > m) {
      data[i] = n;
      data[i - 1] = m;
      newLeft = i;
    }
  }

  if (newLeft != newRight) return shaker(data, newLeft, newRight + 1);
}


void sort(int data[], int n, int dir) {
  int i;

  clock_t start = clock();
  shaker(data, 0, n);
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