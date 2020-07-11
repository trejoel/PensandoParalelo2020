//The following program look for an element in an unsorted vector
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define bool int
#define true 1
#define false 0

double *generateRandomArray(int numberOfElements);
double addVectorElements(double *A, int numberOfElements);
double addVectorElementsPar(double *A, int numberOfElements);

int main(int argc, char *argv[]){
   double *A;
   double sum;
   int n;
   printf("De cuantos elementos son los arreglos\n");
   scanf("%d",&n);
   A=generateRandomArray(n);
   sum=addVectorElements(A,n);
   printf("El valor de la suma secuencial es %f:\n",sum);
   sum=addVectorElementsPar(A,n);
   printf("El valor de la suma paralela es %f:\n ",sum);
   free(A);
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

double addVectorElements(double *A, int numberOfElements){
   double wtime=0;
   double sum=0;
   wtime = omp_get_wtime ();
   for (int i=0;i<numberOfElements;i++){
        sum=sum+A[i];
   }
  wtime = omp_get_wtime ()-wtime;
  printf("Tiempo de respuesta secuencial:%f\n",wtime);
   return sum;
}


double addVectorElementsPar(double *A, int numberOfElements){
   double wtime=0;
   double sum=0;
   wtime = omp_get_wtime ();
   #pragma omp parallel for reduction (+:sum)
   for (int i=0;i<numberOfElements;i++){
        sum=sum+A[i];
   }
  wtime = omp_get_wtime ()-wtime;
  printf("Tiempo de respuesta paralelo:%f\n",wtime);
   return sum;
}

