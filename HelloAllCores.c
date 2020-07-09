#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]){

	int numero_hilos, id_hilo;
	#pragma omp parallel private(numero_hilos, id_hilo)
	{
	  numero_hilos=omp_get_num_threads(); 
	  id_hilo=omp_get_thread_num();
	  if (id_hilo==0){
	  	  printf("Este computador utiliza %d cores\n",numero_hilos);
	  }
      printf("Soy el core n\'umero %d\n",id_hilo);
	}

}