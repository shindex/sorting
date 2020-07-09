#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void sort(int data[], int length, int dir) {
  int i, j, max;
  int *result;

  max = data[0];
  for (i = 0; i < length; i++) {
    if (data[i] > max) max = data[i];
  }

  result = malloc((max) * sizeof(int));
  for (i = 0; i < max; i++) {
    result[i] = 0;
  }

  for (i = 0; i < max; i++) {
    result[i] = 0;
  }

  clock_t start = clock();
  for (i = 0; i < length; i++) {
    result[data[i] - 1]++;
  }
  clock_t end = clock();

  switch (dir) {
    case 0:
      for (i = 0; i < max; i++) {
        for (j = 0; j < result[i]; j++) {
          printf("%d\n", i + 1);
        }
      }
      break;
    case 1:
      for (i = max - 1; i >= 0; i--) {
        for (j = 0; j < result[i]; j++) {
          printf("%d\n", i + 1);
        }
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