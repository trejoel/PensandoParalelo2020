//The following program look for an element in an unsorted vector
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define bool int
#define true 1
#define false 0

typedef  unsigned long long bignum;


int *generateRandomArray(int numberOfElements, int k);
bignum dotProduct(int *A,int *B, int numberOfElements);
bignum dotProductPar(int *A,int *B, int numberOfElements);
void printArray(int *A, int n);

int main(int argc, char *argv[]){
   int *A, *B;
   bignum C;
   bignum D;
   int n;
   printf("De cuantos elementos son los arreglos\n");
   scanf("%d",&n);
   A=generateRandomArray(n,0);
   //printArray(A,n);
   B=generateRandomArray(n,1);
   //printArray(B,n);
   C=dotProduct(A,B,n);
   D=dotProductPar(A,B,n);
   free(A);
   free(B);
}

int *generateRandomArray(int numberOfElements, int primero){
   int *myArray;
   myArray=malloc(numberOfElements*sizeof(int));
   for (int i=0;i<numberOfElements;i++){
        if (primero<1){
            myArray[i]=i;
        }
        else{
            myArray[i]=1;
        }
   }
   return myArray;
}

void printArray(int *A, int n){
   
    printf("Arreglo=");
   for (int i=0;i<n;i++){
       printf("%d  ",A[i]);
   }
   printf("\n");
}

bignum dotProduct(int *A, int *B, int numberOfElements){
   bignum C=0;
   double wtime=0;
   wtime = omp_get_wtime ();
   for (int i=0;i<numberOfElements;i++){
        C+=A[i]*B[i];
   }
   printf("El producto punto es %d\n", C);
   wtime = omp_get_wtime ()-wtime;
  printf("Tiempo de respuesta:%f\n",wtime);
   return C;
}

bignum dotProductPar(int *A,int *B, int numberOfElements){
    bignum C=0;
   double wtime=0;
   wtime = omp_get_wtime ();
   #pragma omp parallel for reduction(+:C)
   for (int i=0;i<numberOfElements;i++){
        C+=A[i]*B[i];
   }
   printf("El producto punto calculado en paralelo es %d\n", C);
   wtime = omp_get_wtime ()-wtime;
  printf("Tiempo de respuesta en paralelo:%f\n",wtime);
   return C;
}
