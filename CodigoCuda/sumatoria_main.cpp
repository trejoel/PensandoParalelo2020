/*
Programa:       sumatoria_main.cpp
Descripción:    Dado un arreglo de elementos en punto flotante (double) de tamaño N
                calcular la sumatoria de todos los elementos del arreglo
Actualización:  07/Jul/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*CUDA*/
#include "kernel.h"

double* generateRandomArray(long int numberOfElements);
double sumOfArraySeq(double* A, long int numberOfElements);
void printArray(double* A, long int n);


int main(int argc, char* argv[]) {
    double t_ini, t_fin;
    double time_generateData,time_cpu_seconds,time_gpu_seconds;
    double *A;
    double sum_total_cpu,sum_total_gpu;
    long int n=500000000;

    printf("De cuantos elementos son los arreglos\n");
    scanf("%ld", &n);
    
    t_ini = clock();
    A = generateRandomArray(n);
    t_fin = clock();
    time_generateData = (t_fin - t_ini) / CLOCKS_PER_SEC;
    //printArray(A,n);
    //
    t_ini = clock();
    sum_total_cpu = sumOfArraySeq(A, n);
    t_fin = clock();
    time_cpu_seconds = (t_fin - t_ini) / CLOCKS_PER_SEC;

    t_ini = clock();
    sum_total_gpu = sumOfArrayGPU(A,n);
    t_fin = clock();
    time_gpu_seconds = (t_fin - t_ini) / CLOCKS_PER_SEC;

    printf("La suma del arreglo en CPU es: %lf \n", sum_total_cpu);
    printf("La suma del arreglo en GPU es: %lf \n", sum_total_gpu);
    printf("Tiempo para generar datos: %lf segundos.\n", time_generateData);
    printf("Tiempo de procesamiento en CPU: %lf segundos.\n",time_cpu_seconds);
    printf("Tiempo de procesamiento en GPU: %lf segundos.\n", time_gpu_seconds);
    
    free(A);
}

double* generateRandomArray(long int numberOfElements) {
    double* myArray;
    //srand(time(NULL));
    srand(1);
    myArray = (double *)malloc(numberOfElements * sizeof(double));
    for (long int i = 0; i < numberOfElements; i++) {
        myArray[i] = rand() % 100 + 1.0;
        //myArray[i] = 1.0;
    }
    return myArray;
}

void printArray(double* A, long int n) {

    printf("Arreglo=");
    for (long int i = 0; i < n; i++) {
        printf("%f  ", A[i]);
    }
    printf("\n");
}

double sumOfArraySeq(double* A, long int numberOfElements) {
    double resultSum = 0.0;
    for (long int i = 0; i < numberOfElements; i++) {
        resultSum = resultSum + A[i];
    }
    return resultSum;
}