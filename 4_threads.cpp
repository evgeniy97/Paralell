#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

double a = 0.0, b = 1.0, H, h, *r;
int *nums, numt, n;

struct args {
    double x_1;
    double x_2;
    double y_1;
    double y_2;
    int N;
};

double f(double x, double y)
{
  return x*x + (y-2) * (y-2);
}

void* worker(void *input)
{

  double x_1 = ((struct args*)input)->x_1;
  double x_2 = ((struct args*)input)->x_2;
  double y_1 = ((struct args*)input)->y_1;
  double y_2 = ((struct args*)input)->y_2;
  int N = ((struct args*)input)->N;
  
  double min_f, new_f; 
  std::srand(unsigned(std::time(0)));

  min_f = f(x_1,y_1);
  double x,y;
  for(int i = 0; i < N; i += 1){
    x = x_1 + std::rand()/(float)RAND_MAX * (x_2 - x_1); 
    y = y_1 + std::rand()/(float)RAND_MAX * (y_2 - y_1);
    now_f = f(x,y);
    if (now_f < min_f){
      min_f = now_f;
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
  
  N = (b - a) / n;
  H = (b-a) / nummt;
  for(i = 0; i < numt; i ++) {
    struct args *arguments = (struct args *)malloc(sizeof(struct args));
    arguments->x_1 = i * H;
    arguments->x_2 = (i+1)* H;
    arguments->y_1 = a;
    arguments->y_2 = b;
    arguments->N = N;

    rc = pthread_create(threads + i, NULL, worker, arguments); // Тут надо другое
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

  double min_f = r[0];
  for(int i = 0; i < NUM_THREADS; i ++){
    if (r[i] < min_f){
      min_f = r[i];
      }
    }
  printf("%lf\n", min_f);
}