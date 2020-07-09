#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void sort(int data[], int length, int dir) {
  int i, j, l;
  int n, m;

  clock_t start = clock();
  for (i = 0; i < length; i++) {
    l = 0;
    for (j = 0; j < length - i - 1; j++) {
      n = data[j];
      m = data[j + 1];
      if (n > m) {
        l++;
        data[j + 1] = n;
        data[j] = m;
      }
    }
    if (l == 0) break;
  }
  clock_t end = clock();
  
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