
//#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buscarpuntos(int triangulo, char fichero[], float puntos[2]){
    int lado;
    float x, y;
    FILE *datos=fopen(fichero,"r");
    while(!feof(datos)){
        fscanf(datos,"%d %f %f", &lado,&x,&y);
        if(lado==triangulo)
        {
            puntos[0]=x;
            puntos[1]=y;
            break;
        }
    }

}

float calculardistancia(){}

    
void buscartriangulo(char fichero[], int posicion, int triangulo[3])
{

    FILE *datos = fopen(fichero,"r");
    fseek(datos,posicion,0);//se ubica en la posicion dada dentro del archivo.
    fscanf(datos,"%d %d %d\n",&triangulo[0],&triangulo[1],&triangulo[2]);
    posicion=ftell(datos);//guarda la ultima ubicacion leida del archivo bytes
}
int main(int argc, char **argv)
{
    int rank, tamano;
    FILE *triangulos =fopen("triangulos","r");

 
   /* MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs ); // devuelve el numero de procesos en este COMM_WORLD
    MPI_Comm_rank( MPI_COMM_WORLD, &myid );     // identificate por el myid asignado  
 
    if(rank == 0)
    {


    }
    */
}
