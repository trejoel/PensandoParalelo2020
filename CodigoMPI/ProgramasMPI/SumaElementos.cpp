/*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
!         PROGRAMA: Suma de los elementos de un vector          !
!                            SERIE                              !
!                    Miguel Angel Uh Zapata                     !
!                                                               !
!    HOW TO RUN :                                               !
!    $ gcc SumaElementos.cpp -o SumaElementos                   !
!    $ ./SumaElementos                                          !
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
   int N = 100000005;
   int i,iIni,iFin;  
   double suma;
   double cpu_time_used;
   double *x;
   
   //__________________________________________
   // Vector de N elementos
   //x = generateRandomArray(N); /* Opcion 1: Arbitrario */
   x = generateSinArray(N);      /* Opcion 2: Integral del seno */
   iIni = 0;
   iFin = N;
   
   //__________________________________________
   // Operaciones: sumar sus componentes
   clock_t start, end;
   start = clock();
   //-----------------------
   suma = 0.0;
   for (i = iIni; i < iFin; i++) {
         suma = suma + x[i];   
   }
   //-----------------------
   //Tiempo final
   end = clock();
   cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;

   //__________________________________________
   // Imprimir
   printf("\n");    
   printf(" N = %i\n",N);
   printf(" Suma = %f\n",suma);
   printf(" Tiempo: %lf \n\n",cpu_time_used);

   //__________________________________________
   // Liberar memoria
   free(x);
 
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
