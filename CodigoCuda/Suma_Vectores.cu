/*
Programa:      Suma_Vectores.cu
Descripción:   Dados dos vectores de tamaño N, sumarlos en paralelo y guardar el resultado en un tercer vector.
Actualización: 09/Jul/2020
*/


#include <stdio.h>
#include <stdlib.h> 
#include <cuda_runtime.h>

// Función Kernel que se ejecuta en el Device.
__global__ void Suma_vectores(float *c_d,float *a_d,float *b_d, int N)
{
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  if (idx<N){
	  c_d[idx] = a_d[idx] + b_d[idx];
  }	
}

// Código principal que se ejecuta en el Host
int main(void){
	float *a_h,*b_h,*c_h; //Punteros a arreglos en el Host 
	float *a_d,*b_d,*c_d;  //Punteros a arreglos en el Device
	const int N = 24;  //Número de elementos en los arreglos  (probar 1000000)
	
	size_t size=N * sizeof(float);

	a_h = (float *)malloc(size); // Pedimos memoria en el Host
	b_h = (float *)malloc(size);
	c_h = (float *)malloc(size);//También se puede con cudaMallocHost
	
	//Inicializamos los arreglos a,b en el Host
	srand(time(NULL));
	for (int i=0; i<N; i++){
		//a_h[i] = (float)i;b_h[i] = (float)(i+1);
		a_h[i] = rand() % 100 + 1.0;
		b_h[i] = rand() % 100 + 1.0;
	}

	printf("\nArreglo a:\n");
	for (int i=0; i<N; i++) printf("%f ", a_h[i]);
	printf("\n\nArreglo b:\n");
	for (int i=0; i<N; i++) printf("%f ", b_h[i]);
	
	cudaMalloc((void **) &a_d,size);   // Pedimos memoria en el Device
	cudaMalloc((void **) &b_d,size);
	cudaMalloc((void **) &c_d,size);
	
	//Pasamos los arreglos a y b del Host al Device
	cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
	cudaMemcpy(b_d, b_h, size, cudaMemcpyHostToDevice);
	
	//Realizamos el cálculo en el Device
	int block_size =8;
	int n_blocks = N/block_size + (N%block_size == 0 ? 0:1);
	
	Suma_vectores <<< n_blocks, block_size >>> (c_d,a_d,b_d,N);
		
	//Pasamos el resultado del Device al Host
	cudaMemcpy(c_h, c_d, size,cudaMemcpyDeviceToHost);
	
	//Resultado
	printf("\n\nArreglo c:\n");
	for (int i=0; i<N; i++) printf("%f ", c_h[i]);
	
	printf("\n\nFin del programa...\n");
	//system("pause");
	
	// Liberamos la memoria del Host
	free(a_h); 
	free(b_h); 
	free(c_h); 

	// Liberamos la memoria del Device
	cudaFree(a_d); 
	cudaFree(b_d); 
	cudaFree(c_d); 
	return(0);
}
