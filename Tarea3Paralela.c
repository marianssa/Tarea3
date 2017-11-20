#include <stdio.h>
#include <math.h>
#include "mpi.h"

/*
float Distancia(x1,x2,y1,y2){
	distancia=sqrt((pow((x1-x2),2))+(pow((y1-y2),2)));
	return distancia;
}*/

int main(int argc, char* argv[])
{
int lado1;
int lado2;
int lado3;

int lado;
float posicion1;
float posicion2;

float distancia1;
float distancia2;
float distancia3;

float x1;
float y1;
float x2;
float y2;
float x3;
float y3;

float perimetro;
float perimetro_total =0;

int rank, tamano;
int status;
MPI_Status rec_stat;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&tamano);


if(rank==0){
FILE *f = fopen("triangulos", "r");
if (f==NULL)
{
   perror ("Error al abrir fichero.txt");
   return -1;
}
while (!feof(f))
{
	fscanf (f, "%d %d %d\n", &lado1, &lado2, &lado3);

	status = MPI_Send(lado1,1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
	status = MPI_Send(lado2,1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
	status = MPI_Send(lado3,1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
	MPI_Reduce(&perimetro_total,&perimetro,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
}

fclose(f);
}

if(rank > 0){
	status = MPI_Recv(lado1,1, MPI_FLOAT, 0,MPI_ANY_TAG, MPI_COMM_WORLD, &rec_stat);
	status = MPI_Recv(lado2,1, MPI_FLOAT, 0,MPI_ANY_TAG, MPI_COMM_WORLD, &rec_stat);
	status = MPI_Recv(lado3,1, MPI_FLOAT, 0,MPI_ANY_TAG, MPI_COMM_WORLD, &rec_stat);

	FILE *f2 = fopen("puntos", "r");
	if (f2==NULL)
	{
   		perror ("Error al abrir fichero2.txt");
   		return -1;
	}

	fscanf (f2, "%d %f %f\n", &lado, &posicion1, &posicion2);
	if((lado==lado1)||(lado==lado2)||(lado==lado3))
	{
		if(lado==lado1)
		{
			x1=posicion1;
			y1=posicion2;
		}
		if(lado==lado2)
		{
			x2=posicion1;
			y2=posicion2;
		}
		if(lado==lado3)
		{
			x3=posicion1;
			y3=posicion2;
		}
	}

	fclose(f2);
	distancia1=sqrt((pow((x1-x2),2))+(pow((y1-y2),2)));
	distancia2=sqrt((pow((x2-x3),2))+(pow((y2-y3),2)));
	distancia3=sqrt((pow((x1-x3),2))+(pow((y1-y3),2)));
	perimetro=distancia1+distancia2+distancia3;
	MPI_Reduce(&perimetro_total,&perimetro,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	/*perimetro_total=perimetro_total+perimetro;*/
}

MPI_Finalize();

printf("La suma de todos los perimetros de los triangulos es %f\n",perimetro_total);
/* La suma de todos los perimetros de los triangulos es 37855.906250 ----- resultado que debiera dar*/

return 0;
}
