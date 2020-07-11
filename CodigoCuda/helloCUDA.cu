#include <stdio.h>
#include <cuda_runtime.h>

__global__ void helloCUDA(float e){
    printf("Soy el hilo %d del bloque %d con valor e=%f\n",threadIdx.x,blockIdx.x,e);
}

int main(void){
    printf("\nHello World\n");

    helloCUDA<<<3,4>>>(2.5f);

    return(0);
}
