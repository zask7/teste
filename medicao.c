#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sequential_search(int x, int arr[], int n) {
  if (n == 0)
    return 0;

  int i = 0;
  while (i < n && arr[i] < x)
    i++;

  if (i == n || arr[i] > x)
    return 0;

  return 1;
}


// arr= 0,  2,  10,  20,  50
// pos  0,  1,   2,   3,   4
// n = 5
// meio = 2
//
//arr[meio] = 10 / 2
// arr + 3
// n - (meio + 1)

int binary_search(int x, int arr[], int n) {
  if (n == 0)
    return 0;

  int meio = n / 2;

  if (x < arr[meio])
    return binary_search(x, arr, meio);

  if (x > arr[meio])
    return binary_search(x, arr + meio + 1, n - (meio + 1));

  return 1;
}

// funçoes para extrair o tempo atual no windows ou linux
#ifdef WIN32

#include <windows.h>
double get_time() {
  LARGE_INTEGER t, f;
  QueryPerformanceCounter(&t);
  QueryPerformanceFrequency(&f);
  return (double)t.QuadPart / (double)f.QuadPart;
}

#else

#include <sys/resource.h>
#include <sys/time.h>

double get_time() {
  struct timeval t;
  struct timezone tzp;
  gettimeofday(&t, &tzp);
  return t.tv_sec + t.tv_usec * 1e-6;
}

#endif

int main() {

  // array com capacidade para 100 mil inteiros
  int arr[100000];

  // le inteiros armazenando no array
  // base de teste tem 100.000 inteiros ordenados entre 0 e 1.000.000
  int n = 0;
  int elem;
  while (scanf("%d", &elem) != EOF) {
    arr[n] = elem;
    n++;
  }

  // imprime cabeçalho
  printf("x\t | sequential search | is in array? | binary search | is in "
         "array? |\n");

  // executa as buscas 100 vezes mantendo o tempo total gasto
  srand(time(NULL));
  double seq_total = 0, bin_total = 0;
  for (int i = 0; i < 100; i++) {

    // numero aleatorio entre 0 e 1.000.000
    int x = rand() % 1000000;

    // executa busta sequencial e calcula a diferença de tempos
    double seq_begin = get_time();
    int seq_is_in_array =
        sequential_search(x, arr, n); // chamada da busca sequencial
    double seq_time_spent = get_time() - seq_begin;

    // executa busca binária e calcula a diferença de tempos
    double bin_begin = get_time();
    int bin_is_in_array = binary_search(x, arr, n); // chamada da busca binária
    double bin_time_spent = get_time() - bin_begin;

    // imprime linha com resultados e soma tempos
    printf("%d\t | %-17lf | %-12d | %-13lf | %-12d |\n", x, seq_time_spent,
           seq_is_in_array, bin_time_spent, bin_is_in_array);
    seq_total += seq_time_spent;
    bin_total += bin_time_spent;
  }

  // imprime tempo total e media
  printf("---------------------------------------------------------------------"
         "-------\n");
  printf("\t   %-17lf\t\t      %-13lf\t\t     TOTAL TIME\n", seq_total,
         bin_total);
  printf("\t   %-17lf\t\t      %-13lf\t\t       AVG TIME\n", seq_total / 100,
         bin_total / 100);

  return 0;
}
