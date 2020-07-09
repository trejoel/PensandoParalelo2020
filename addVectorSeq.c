//The following program look for an element in an unsorted vector
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define bool int
#define true 1
#define false 0

double *generateRandomArray(int numberOfElements);
double *addArraySeq(double *A,double *B, int numberOfElements);
void printArray(double *C, int numberOfElements);

int main(int argc, char *argv[]){
   double *A, *B, *C, *D;
   int n;
   printf("De cuantos elementos son los arreglos\n");
   scanf("%d",&n);
   A=generateRandomArray(n);
   B=generateRandomArray(n);
   C=addArraySeq(A,B,n);
   printArray(C,n);
   free(A);
   free(B);
   free(C);
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
   for (int i=0;i<numberOfElements;i++){
        C[i]=A[i]+B[i];
   }
   return C;
}

void printArray(double *C, int numberOfElements){
   for (int i=0; i<numberOfElements; i++){
    printf("Resultado:%f\n",C[i]);
   }
}

