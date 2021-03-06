#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <omp.h>

double func(double x)
{
    return 4 / (1 + x * x);
}

double integr(double a, double b, int n, double (*g)(double))
{
  int i;
  double s, h;

  s = 0.;
  h = (b - a) / n;
  #pragma omp parallel for reduction(+:s)
  for(i = 0; i < n; i ++){
    s += (g(a + i * h) + g(a + (i+1)*h))/2 ;
  }
  return s * h;
}

int main()
{
  double A, B, v;
  int N;

  A = 0.0;
  B = 1.0;
  N = 10000000; 
  v = integr(A, B, N, func);
  printf("%lf\n", v);
}