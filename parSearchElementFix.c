//The following program look for an element in an unsorted vector
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define bool int
#define true 1
#define false 0

int *generateRandomArray(int numberOfElements);
int seqlookElement(int *myArray, int numberOfElements, int x);
int lookElement(int *myArray,int numberOfElements, int x);
 void printMyArray(int *myArray, int numberOfElements);

int main(int argc, char *argv[]){
   int *myArray,n,y,position;
   printf("De cuantos elementos\n");
   scanf("%d",&n);
   myArray=generateRandomArray(n);
  // printMyArray(myArray,n);
   printf("A buscar?\n");
   scanf("%d",&y);
   position=seqlookElement(myArray,n,y);
   position=lookElement(myArray,n,y);
   if (position>=0){
   	 printf("Elemento %d se encuentra %d veces\n\n\n\n",y,position); 
   }
   else{
   	 printf("Elemento no encontrado\n\n\n\n"); 
   }
   free(myArray);
  // printMyArray(myArray,n);
}

int *generateRandomArray(int numberOfElements){
   int *myArray;
   int tid, nthreads, begin, end, i,delta;
   //variables auxiliares
   int x,z,last_begin, last_end=0;
   myArray=malloc(numberOfElements*sizeof(int));
   srand(time(NULL));
   #pragma omp parallel private (i, tid, nthreads, begin, end, delta)
   {
     nthreads=omp_get_num_threads();
     tid=omp_get_thread_num();
     delta=numberOfElements/nthreads;
     begin=tid*delta;
     end=begin+delta;
     for ( i=begin;i<end;i++){
        myArray[i]=rand()%numberOfElements;
     }
     if (tid==0){
        x=delta*nthreads;
        z=numberOfElements % x;
        last_begin=x;
        last_end=x+z;
        for ( i=last_begin;i<last_end;i++){
          myArray[i]=rand()%numberOfElements;
        }
     }    
   }
   return myArray;
}

int seqlookElement(int *myArray, int numberOfElements, int x){
  int isIt=0;
  double wtime=0;
  wtime = omp_get_wtime ( );
   for (int i=0;i<numberOfElements;i++){
      if (myArray[i]==x){
          //printf("Encontrado %d\n",myArray[i]);
          isIt=isIt+1;
      }
   }
    wtime = omp_get_wtime ( ) - wtime;
   printf("El secuencial tardo %f en encontrar\n", wtime);  
   return isIt;
  }

int lookElement(int *myArray, int numberOfElements, int x){
	int isIt=0;
  double wtime=0;
  int tid, nthreads, begin, end, i,delta;   
  //variables auxiliares
  int x2,z,last_begin, last_end=0; 
	bool found=false;
  wtime = omp_get_wtime ( );
   #pragma omp parallel private (i, tid, nthreads, begin, end, delta) shared (found)
   {
     nthreads=omp_get_num_threads();
     tid=omp_get_thread_num();
     delta=numberOfElements/nthreads;
     begin=tid*delta;
     end=begin+delta;  
     for (i=begin;(i<end && !found);i++){
   	    if (myArray[i]==x){
            isIt++;
            found=true;
            //printf("Elemento encontrado en posicion %d\n",i);
   	    }
     if (tid==0){
        x2=delta*nthreads;
        z=numberOfElements % x2;
        last_begin=x2;
        last_end=x2+z;
        for ( i=last_begin;(i<last_end && !found);i++){
          if (myArray[i]==x){
            isIt++;
            found=true;
            //printf("Elemento encontrado en posicion %d\n",i);
          }
        }
     }        
        //#pragma omp flush(found)
     }

             //printf("Soy el Core %d y encontre %d ocurrencias\n",tid,isIt);
   }
   wtime = omp_get_wtime ( ) - wtime;
   printf("El paralelo tardo %f en encontrar\n", wtime);
   return isIt;
  }

  void printMyArray(int *myArray, int numberOfElements){
   for (int i=0;i<numberOfElements;i++){
   	  printf("%d ", myArray[i]);
   }
   printf("\n\n\n");
}