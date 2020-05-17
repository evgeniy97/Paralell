#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

double a = 0.0, b = 1.0, h, *r;
int *nums, numt, n;

double f(double x)
{
  return 4 / (1 + x * x);
}

void* worker(void* p)
{
    // REWRITE HERE
  int my, i;
  double s; 

  my = *(int*)p;
  s = 0.0;
  for(i = my; i < n; i += numt)
    //s += f(i * h + 0.5 * h);
    s += f(i*h);
  r[my] = s; 
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

    rc = pthread_create(threads + i, NULL, worker, nums + i);
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