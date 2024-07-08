//The following program look for an element in an unsorted vector
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <omp.h>

#define bool int
#define true 1
#define false 0

float **generateRandomMatrix(int M, int N);

float *generateRandomVector(int numberOfElements);
float *matrixTimesVectorSeq(float **myMatrix,float *myVec, int M, int N);
float *addArray(float *A,float *B, int numberOfElements);

int main(int argc, char *argv[]){
   float **myMatrix, *myVector, *resultingVector;
   int n,m;
   srand(time(NULL));
   printf("De cuantos filas es el arreglo\n");
   scanf("%d",&m);
   printf("De cualtas columnas es el arreglo\n");
   scanf("%d",&n);
   myMatrix=generateRandomMatrix(m,n);
   myVector=generateRandomVector(n);
   resultingVector=matrixTimesVectorSeq(myMatrix,myVector,m,n);
   free(myMatrix);
   free(myVector);
   free(resultingVector);
}

float **generateRandomMatrix(int M, int N){

  float **A;
  int j,i;
  A=(float**)malloc(M*sizeof (float *));
  for (i=0;i<N;i++){
    A[i]=(float *)malloc(N*sizeof(float));
  }
  for (i=0;i<M;i++){
    for (j=0;j<N;j++)
    {
      A[i][j]=((float)rand()/(float)RAND_MAX)*N*M;
    }
  }
  return A;
}

float *generateRandomVector(int numberOfElements){
   float *myArray;
   myArray=malloc(numberOfElements*sizeof(float));
   for (int i=0;i<numberOfElements;i++){
       myArray[i]=((float)rand()/(float)RAND_MAX)*numberOfElements ;
   }
   return myArray;
}

float *matrixTimesVectorSeq(float **myMatrix,float *myVec, int M, int N){
  float *vectorDotProduct;
  int i,j;
  vectorDotProduct=malloc(N*sizeof(float));
  for (i=1;i<M;i++){
    vectorDotProduct[i]=0;
    for (j=1;j<N;j++){
      vectorDotProduct[i]+=myMatrix[i][j]*myVec[j];
    }
  }
  return vectorDotProduct;
}

float *addArray(float *A, float *B, int numberOfElements){
   float *C;
   C=malloc(numberOfElements*sizeof(float));
   for (int i=0;i<numberOfElements;i++){
        C[i]=A[i]+B[i];
        printf("C[%d]=A[%d]+B[%d]--->%f = %f + %f\n", i,i,i,C[i],A[i],B[i]);
   }
   return C;
}
