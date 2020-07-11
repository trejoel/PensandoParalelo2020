/*sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
!         PROGRAMA: Hello word                                  !
!                          PARALELO MPI                         !
!                    Miguel Angel Uh Zapata                     !
!                                                               !
!    HOW TO RUN :                                               !
!    $ mpicxx HelloMPI.cpp -o HelloMPI                          !
!    $ mpiexec -n 4 ./HelloMPI                                  !
!                                                               !
sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*/

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{    
   int numtasks, taskid;
   //-----------------------
   MPI_Init(&argc,&argv);                   /* Initializacion*/
   MPI_Comm_size(MPI_COMM_WORLD,&numtasks); /* Numero de procesos */
   MPI_Comm_rank(MPI_COMM_WORLD,&taskid);   /* Identificador de cada proceso */
   //-----------------------
   printf(" Yo soy el procesor %i de %i: \n",taskid,numtasks);
   //-----------------------
   MPI_Finalize();
   //-----------------------
   return 0;
}

/*ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss*/