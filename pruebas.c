
//#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define cantidad_triangulos 9665


//el perimetro segun el codigo secuencial debiese ser 37855.906250

float calcularperimetro (float puntos1[2],float puntos2[2],float puntos3[2])
{
    float lado1,lado2,lado3;

    lado1= sqrt((pow((puntos1[0]-puntos2[0]),2))+(pow((puntos1[1]-puntos2[1]),2)));
    lado2=sqrt((pow((puntos2[0]-puntos3[0]),2))+(pow((puntos2[1]-puntos3[1]),2)));
    lado3=sqrt((pow((puntos1[0]-puntos3[0]),2))+(pow((puntos1[1]-puntos3[1]),2)));

    return lado1+lado2+lado3;
}
int buscarlinea(char fichero[], int linea_buscada)
{
    int posicion;
    FILE *datos=fopen(fichero,"r");
     int contar=linea_buscada-1;
    fseek(datos, 0, SEEK_SET);
    prueba:     
    if (contar>0)  
    { 
    while (fgetc (datos) != '\n');
        contar--;
        goto prueba;
    }
    posicion=ftell(datos);

    fclose(datos);
    return posicion;


}
void buscarpuntos(int triangulo, char fichero[], float puntos[2]){
    int lado;
    float x, y;
    FILE *datos=fopen(fichero,"r");
    int posicion;
    posicion=buscarlinea("puntos",triangulo);
    fseek(datos,posicion,SEEK_SET);
    fscanf(datos,"%d %f %f", &lado,&x,&y);
     if (lado==triangulo){
    puntos[0]=x;
    puntos[1]=y;
            }
    fclose(datos);

}


    
float buscartriangulo(char fichero[],int linea, int triangulo[3], float perimetro)
{

    float puntos1[2];
    float puntos2[2];
    float puntos3[2];
    FILE *datos = fopen(fichero,"r");
    int posicion;
    posicion=buscarlinea("triangulos",linea); 
    // aqui yo me ubico en la linea que deseo del fichero.
    fseek(datos,posicion,SEEK_SET);
    fscanf(datos,"%d %d %d\n",&triangulo[0],&triangulo[1],&triangulo[2]);
    buscarpuntos(triangulo[0],"puntos",puntos1);
    buscarpuntos(triangulo[1],"puntos",puntos2);
    buscarpuntos(triangulo[2],"puntos",puntos3);
    perimetro=calcularperimetro(puntos1,puntos2,puntos3);        

    fclose(datos);

    return perimetro;
}
int main(int argc, char **argv)
{
    int rank, tamano;
    int triangulo[3]={0,0,0};
    float puntos1[2];
    float puntos2[2];
    float puntos3[2];
    int posicion=0;
    int n=1;
    float total=0;
    float triangulosporprocesador=10/4;

    float perimetro;

    int aux=sizeof(triangulosporprocesador);
    while(n<=cantidad_triangulos)
    {
 	perimetro=buscartriangulo("triangulos",n,triangulo,perimetro);
    n++;
 
    total=total+perimetro;
    }
printf("%f\n",total);



   /* MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs ); // devuelve el numero de procesos en este COMM_WORLD
    MPI_Comm_rank( MPI_COMM_WORLD, &myid );     // identificate por el myid asignado  
 
    if(rank == 0)
    {


    }
    */
   
}
