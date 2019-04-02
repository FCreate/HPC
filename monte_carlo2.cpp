#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <random>
int main(){
    omp_set_dynamic(0);
    omp_set_num_threads(8);
    const long int size = 1000000000;
    double pi = 0.0;
    srand(time(NULL));
    //default_random_engine generator(0);
    //uniform_real_distribution<
    //printf("%f", double(rand())/RAND_MAX);
    long int true_numbers = 0;
    clock_t start, end;
    start  = omp_get_wtime();
    double x=0.0, y=0.0;
    #pragma omp parallel for private(x,y) reduction(+:true_numbers)
    for (int i=0; i< size; i++){

        x = double(rand_r(&i))/RAND_MAX;
        y = double(rand_r(&i))/RAND_MAX;
        if (x*x +y*y<1.0){
            //#pragma omp atomic
            true_numbers++;
        }
    }
    printf("%f\n", omp_get_wtime()-start);
    pi = 4*double(true_numbers)/size;
    //printf("%f\n", pi);
    pi = 0.0;
    true_numbers = 0;
    start = clock();
    for (int i=0; i< size; i++){
        x = double(rand())/RAND_MAX;
        y = double(rand())/RAND_MAX;
        if (x*x +y*y<1.0){
            true_numbers++;
        }
    }
    pi = 4*double(true_numbers)/size;
    //printf("%f\n", pi);
    printf("%f\n", double(clock()-start)/CLOCKS_PER_SEC);
}