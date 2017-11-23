
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define cantidad_triangulos 9665

void buscarpuntos(int triangulo, char fichero[], float puntos[2]){
     int lado;
    float x, y;
    FILE *datos=fopen(fichero,"r");
    int contar=triangulo-1;
    fseek(datos, 0, SEEK_SET);
    prueba:     
    if (contar>0)  
    { 
    while (fgetc (datos) != '\n');
        contar--;
        goto prueba;
    }
    fscanf(datos,"%d %f %f", &lado,&x,&y);
        if(lado==triangulo)
        {
            puntos[0]=x;
            puntos[1]=y;
            
        }
    fclose(datos);

}


    
void buscartriangulo(char fichero[],int posicion, int triangulo[3])
{

    FILE *datos = fopen(fichero,"r");
    fseek(datos,posicion,SEEK_CUR);//se ubica en la posicion dada dentro del archivo.
     if(!feof(datos)){
    fscanf(datos,"%d %d %d\n",&triangulo[0],&triangulo[1],&triangulo[2]);
    posicion=ftell(datos);//guarda la ultima ubicacion leida del archivo bytes
}
    fclose(datos);
}

float calcularperimetro (float puntos1[2],float puntos2[2],float puntos3[2])
{
    float lado1,lado2,lado3;

    lado1= sqrt((pow((puntos1[0]-puntos2[0]),2))+(pow((puntos1[1]-puntos2[1]),2)));
    lado2=sqrt((pow((puntos2[0]-puntos3[0]),2))+(pow((puntos2[1]-puntos3[1]),2)));
    lado3=sqrt((pow((puntos1[0]-puntos3[0]),2))+(pow((puntos1[1]-puntos3[1]),2)));

    return lado1+lado2+lado3;

}
int main(int argc, char* argv[])
{
    int rank, tamano, status;
    MPI_Status  rec_stat;
    int triangulo[3]={0,0,0};
    float puntos1[2];
    float puntos2[2];
    float puntos3[2];
    int posicion=0;
    float perimetro;
    float perimetrototal;
    int n=0;
   
   MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &tamano ); // devuelve el numero de procesos en este COMM_WORLD
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );     // identificate por el myid asignado  
 
    if(rank == 0)
    {
        while(n<9665)
        {
           for(int fuente=1;fuente<tamano;fuente++)
            {
                buscartriangulo("triangulos",posicion,triangulo);
                n++;
                status = MPI_Send(triangulo,3, MPI_INT,fuente,0, MPI_COMM_WORLD);
            }
        }

    }

    if (rank > 0) 
    {
     
         status = MPI_Recv(&triangulo, 3, MPI_INT,0,MPI_ANY_TAG, MPI_COMM_WORLD,&rec_stat);
         for(int i =0 ;i<3;i++)
                {
                    if(i==0)
                    buscarpuntos(triangulo[i],"puntos",puntos1);
                    if(i==1)
                    buscarpuntos(triangulo[i],"puntos",puntos2);
                    if(i==2)
                    buscarpuntos(triangulo[i],"puntos",puntos3);
                }
                perimetro=calcularperimetro(puntos1,puntos2,puntos3);
                printf("%f\n",perimetro );
                MPI_Reduce(&perimetro,&perimetrototal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    }
    

    MPI_Finalize();
    return 0;
}