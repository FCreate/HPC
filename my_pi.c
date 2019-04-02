//
// Created by Иван Матвиенко on 2019-04-02.
//
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    omp_set_dynamic(0);
    omp_set_num_threads(2);
    srand(0);
    int N = 1000000000;
    double x, y;
    int count = 0;
    double begin = omp_get_wtime(), end;
    #pragma omp parallel private(x,y)
    {
        #pragma omp for reduction(+: count)
        for(int i = 0; i < N; i++)
        {
            x = (double)random()/RAND_MAX;
            y = (double)random()/RAND_MAX;
            if(x*x + y*y <= 1)
                count += 1;
        }
    }
    end = omp_get_wtime();
//    printf("%d\n", count);
    printf("Pi parallel = %f\n", 4*(double)count/N);
    printf("Time parallel: %f\n\n", end - begin);

    time_t begin_c = clock();
    int count_seq = 0;
    {
        for(int i = 0; i < N; i++)
        {
            x = (double)random()/RAND_MAX;
            y = (double)random()/RAND_MAX;
            if(x*x + y*y <= 1)
                count_seq += 1;
        }
    }
    time_t end_c = clock();
    printf("Pi sequential = %f\n", 4*(double)count/N);
    printf("Time sequential: %f\n", (double)(end_c - begin_c)/CLOCKS_PER_SEC);
}

