#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    omp_set_dynamic(0);
    omp_set_num_threads(8);
    const int size = 10000000;
    double pi = 0.0;
    srand(time(NULL));
    //printf("%f", double(rand())/RAND_MAX);
    int true_numbers = 0;
    clock_t start, end;
    start  = clock();
    double x=0.0, y=0.0;
    #pragma  omp parallel private(x, y){
        #pragma omp parallel for reduction(+:true_numbers)
        for (int i=0; i< size; i++){
            x = double(rand())/RAND_MAX;
            y = double(rand())/RAND_MAX;
            if (x*x +y*y<1.0){
                //#pragma omp atomic
                true_numbers++;
            }
        }
    }
    printf("%f\n", double(clock()-start)/CLOCKS_PER_SEC);
    pi = 4*double(true_numbers)/size;
    printf("%f\n", pi);
    pi = 0.0;
    true_numbers = 0;
    start = clock();
    for (int i=0; i< size; i++){
        double x = double(rand())/RAND_MAX;
        double y = double(rand())/RAND_MAX;
        if (x*x +y*y<1.0){
            true_numbers++;
        }
    }
    pi = 4*double(true_numbers)/size;
    printf("%f\n", pi);
    printf("%f\n", double(clock()-start)/CLOCKS_PER_SEC);
}