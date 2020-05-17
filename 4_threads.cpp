#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

double a = 0.0, b = 1.0, h, *r;
int *nums, numt, n;

double f(double x)
{
  return x*x + (y-2) * (y-2);
}

void* worker(void* p, void* q)
{
    // REWRITE HERE
  int x, y, i;
  double min_f; 

  x = *(double*)p;
  y = *(double*)p;
  min_f = f(x,y);
  for(i = x; i < n; i += numt){
      for(j = y; j < n; i += numt)
      {
          now_f = f(i, j);
          if (now_f < min_f){
              min_f = now_f;
          }
      }
  }
  r[my] = min_f; 
  return NULL;
}

int main(int arc, char* argv[])
{
  double S;
  pthread_t *threads;
  int i, rc;

  numt = atoi(argv[1]);
  n = atoi(argv[2]);
  threads = (pthread_t*)malloc(numt * sizeof(pthread_t));
  nums = (int*)malloc(numt * sizeof(int));
  r = (double*)malloc(numt * sizeof(double));
  h = (b - a) / n;

  for(i = 0; i < numt; i ++) {
    nums[i] = i;

    rc = pthread_create(threads + i, NULL, worker, nums + i); // Тут надо другое
    if(rc != 0) {
      fprintf(stderr, "pthread_create: error code %d\n", rc);
      exit(-1);
    }
  }
  for(i = 0; i < numt; i ++) { 
    rc = pthread_join(threads[i], NULL);
    if(rc != 0) {
      fprintf(stderr, "pthread_join: error code %d\n", rc);
      exit(-1);
    }
  }

  S = 0;
  for(i = 0; i < numt; i ++) 
    S += r[i];
  printf("Answer = %lf\n", S * h);
}