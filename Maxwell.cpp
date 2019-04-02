//
// Created by micheal on 29.03.19.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <fstream>

#define PI 3.14159265
using namespace std;
int main()
{
    printf("fldjflk");
    omp_set_dynamic(0);
    omp_set_num_threads(8);

    clock_t start, end;

    float delta_t = PI*2/10;
    float delta_x = PI*2/10;
    float L = 2*PI*40;
    float T = 2*PI*10;
    const int size_i = 2000;
    const int size_j = 2000;

    float ** F = (float **)malloc(size_i * sizeof(float *));

    for (int i = 0; i < size_i; ++i)
    {
        F[i] = (float *)malloc(size_j * sizeof(float));
    }


    printf("fldjflk");
    for (int i = 0; i < size_i; i++)
    {
        for (int j = 0; j < size_j; j++)
        {
            F[i][j] = 0.0;
        }
    }
    printf("fldjflk");

    //Periodic conditions
    for (int j = 0; j<1000; j++){
        F[0][j] = sin(delta_t*size_j);
    }

    for(int i=0; i<size_i; i++){
        F[i][0] = 0;
    }
    printf("fldjflk");

    //#pragma omp parallel for
    for (int i=1; i<size_i; i++){
        for (int j=1; j<size_j; j++){
            F[i][j] = F[i-1][j-1];
        }
    }
    printf("dfjlkd");
    ofstream myfile ("ex1.csv", std::ofstream::out);
    for (int i = 0; i < size_i; i++) {
        for (int j = 0; j < size_j; j++) {
            myfile << F[i][j] << ",";
        }
        myfile<<std::endl;
    }
    myfile.close();
    for (int i = 0; i < size_i; i++)
    {
        free(F[i]);
    }

    free(F);
    return 0;
}