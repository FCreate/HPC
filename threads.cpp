#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    double *a, *b, *c;
    double *c_fork;
    const size_t N = 10e7;
    size_t myrank;
    time_t start, end;
    a = (double*)malloc(N* sizeof(double));
    b = (double*)malloc(N* sizeof(double));
    c = (double*)malloc(N* sizeof(double));
    start = clock();
    for (int n=0; n<N; n++){
        c[n] = a[n]+b[n];
    }
    end = clock();
    printf("Time serial = %f seconds\n", double(end-start)/CLOCKS_PER_SEC);
    pid_t a1 = fork();
    c_fork = (double *) malloc(N/2 *sizeof(double));
    if (a1==0){
        myrank = 1;
    }
    else{
        start = clock();
        myrank = 0;
    }
    for (int n = myrank*N/2; n<N/2+myrank*N/2; n++){
        c_fork[n-myrank*N/2] = a[n]+b[n];
    }
    if (a1!=0){
        end = clock();
        printf("Time fork = %f seconds\n", double(end-start)/CLOCKS_PER_SEC);
    }
    return 0;
}