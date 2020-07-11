#include "kernel.h"

#define TPB 1024
#define ATOMIC 1 // 0 para no usar el atomicAdd

__global__ void sumOfArrayKernel(double *d_sum_total, double *d_A, long int n) {
	const long int idx = threadIdx.x + blockDim.x * blockIdx.x;
	const int s_idx = threadIdx.x;
	__shared__ double s_data[TPB];

	s_data[s_idx] = (idx<n) ? d_A[idx] : 0.0;
	__syncthreads();

	if (s_idx==0) {
		double blockSum = 0.0;
		for (int j = 0; j < blockDim.x; j++) {
			blockSum += s_data[j];
		}
		//printf("Block_%d, blockSum = %lf\n", blockIdx.x, blockSum);
		if (ATOMIC) {
			atomicAdd(d_sum_total, blockSum);
		}
		else {
			*d_sum_total += blockSum; //Resultados no esperados
		}
	}
}

double sumOfArrayGPU(double *A, long int n){
	double *d_A;
	double *d_sum_total;
	double sum_total;
	
	//1. Crear memoria en la GPU
	cudaMalloc(&d_sum_total, sizeof(double));
	cudaMalloc(&d_A, n * sizeof(double));

	//Inicializamos en cero
	cudaMemset(d_sum_total, 0, sizeof(double));

	//2. Copiar memoria (CPU-->GPU)
	cudaMemcpy(d_A, A, n * sizeof(double), cudaMemcpyHostToDevice);

	//3. Ejecutar función Kernel
	sumOfArrayKernel <<<(n+TPB-1)/TPB,TPB >>> (d_sum_total,d_A,n);
	//sumOfArrayKernel_V2 << <(n + TPB - 1) / TPB, TPB >> > (d_sum_total, d_A, n);

	//4. Copiar memoria (GPU-->CPU)
	cudaMemcpy(&sum_total, d_sum_total, sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(d_sum_total);
	cudaFree(d_A);
	cudaDeviceReset();
	return(sum_total);
}