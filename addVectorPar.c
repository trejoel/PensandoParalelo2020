//The following program look for an element in an unsorted vector
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define bool int
#define true 1
#define false 0

double *generateRandomArray(int numberOfElements);
double *addArraySeq(double *A,double *B, int numberOfElements);
double *addArrayPar(double *A,double *B, int numberOfElements);

int main(int argc, char *argv[]){
   double *A, *B, *C, *D;
   int n;
   printf("De cuantos elementos son los arreglos\n");
   scanf("%d",&n);
   A=generateRandomArray(n);
   B=generateRandomArray(n);
   C=addArraySeq(A,B,n);
   free(C);
   D=addArrayPar(A,B,n);
   free(A);
   free(B);
   free(D);
}

double *generateRandomArray(int numberOfElements){
   double *myArray;
   srand(time(NULL));
   myArray=malloc(numberOfElements*sizeof(double));
   for (int i=0;i<numberOfElements;i++){
       myArray[i]=rand() % 100 + 1;
   }
   return myArray;
}

double *addArraySeq(double *A, double *B, int numberOfElements){
   double *C;
   C=malloc(numberOfElements*sizeof(double));
   double wtime=0;
   wtime = omp_get_wtime ();

   for (int i=0;i<numberOfElements;i++){
        C[i]=A[i]+B[i];
   }
  wtime = omp_get_wtime ()-wtime;
  printf("Tiempo de respuesta secuencial:%f\n",wtime);
   return C;
}

double *addArrayPar(double *A, double *B, int numberOfElements){
   double *C;
   C=malloc(numberOfElements*sizeof(double));
   double wtime=0;
   wtime = omp_get_wtime();
   //#pragma omp parallel for num_threads(3)
   #pragma omp parallel for
   for (int i=0;i<numberOfElements;i++){
        C[i]=A[i]+B[i];
   }
  wtime = omp_get_wtime ()-wtime;
  printf("Tiempo de respuesta paralelo:%f\n",wtime);
   return C;
}
