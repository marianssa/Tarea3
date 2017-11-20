
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buscarpuntos(int tag1, int tag2, int tag3){
	//
}

float calculardistancia(){

	
}
int main(int argc, char **argv)
{
    int rank, tamano;
    FILE *triangulos =fopen("triangulos","r");

 
    MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs ); // devuelve el numero de procesos en este COMM_WORLD
    MPI_Comm_rank( MPI_COMM_WORLD, &myid );     // identificate por el myid asignado  
 
    if(rank == 0)
    {


    }