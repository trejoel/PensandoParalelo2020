/*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
!                PROGRAMA: Suma de dos vectores                 !
!                            SERIE                              !
!                    Miguel Angel Uh Zapata                     !
!                                                               !
!    HOW TO RUN :                                               !
!    $ gcc SumaVectores.cpp -o SumaVectores                     !
!    $ ./SumaVectores                                           !
!                                                               !
sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double *generateRandomArray(int numberOfElements);
double *generateSinArray(int numberOfElements);

int main()
{
   int N = 100000000;
   int i,iIni,iFin;
   double cpu_time_used;
   double *A,*B,*C;     

   //__________________________________________
   // Vector de N elementos
   A = generateRandomArray(N);
   B = generateRandomArray(N);
   C = (double *)malloc(N*sizeof(double));

   iIni = 0;
   iFin = N;
    
   //__________________________________________
   // Operaciones: sumar dos vectores
   clock_t start, end;
   start = clock();
   //----------------------- 
   for (i = iIni; i < iFin; i++) {
        C[i] = A[i] + B[i];
        //printf("%f + %f = % f\n",A[i],B[i],C[i]);
   }
   //-----------------------
   end = clock();
   cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;

   //__________________________________________
   // Imprimir
   printf(" \n N = %i, time = %lf \n \n",N,cpu_time_used);

   //__________________________________________
   // Liberar memoria
   free(A);
   free(B);
   free(C);

   return 0;
}

//sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
// Vector de numeros aleatorios entre 0 y 100 

double *generateRandomArray(int N){
   double *x;
   srand(time(NULL));
   x = (double *)malloc(N*sizeof(double));
   for (int i = 0; i < N; i++){
       x[i] = rand() % 100 + 1;
       //printf("%f\n",x[i]);
   }
   return x;
}

//sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
// Integral del seno
 
double *generateSinArray(int N){
   double *x;
   double xx,Dx;
   x = (double *)malloc(N*sizeof(double));
   Dx = 1.0/(N-1);   
   for (int i = 0; i < N; i++){
        xx = i*Dx;
        x[i] = sin(xx)/N;
        //printf("%f\n",x[i]);
   }
   return x;
}

//sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss