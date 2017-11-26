
#include "mpi.h"
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

int main(int argc, char* argv[])
{
    int rank, tamano, status,status1;
    MPI_Status  rec_stat;
    int triangulo[3];
    int aux1;
    int aux2;
    int posicion=0;
    float perimetro;
    float perimetrototal,triangulos_faltantes;
    float triangulosporprocesador;
 
   int buffsize=atoi(argv[1]);
   MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &tamano ); // devuelve el numero de procesos en este COMM_WORLD
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );     // identificate por el rank asignado  


    if(rank == 0)
    {

        if(cantidad_triangulos%tamano==0)
        {
            triangulosporprocesador=cantidad_triangulos/tamano;
            aux1=(int)triangulosporprocesador;
        }
        else
        {
            triangulosporprocesador=cantidad_triangulos/tamano;
            aux1=(int)triangulosporprocesador;
            triangulos_faltantes=(cantidad_triangulos%tamano);
            aux2=(int)triangulos_faltantes;
        }

    
        for(int i=1;i<=triangulosporprocesador+aux2;i++)
        {
            perimetro=buscartriangulo("triangulo",i,triangulo,perimetro);
            MPI_Reduce(&perimetro,&perimetrototal,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
        }
        for(int fuente=1;fuente<tamano;fuente++)
            {  
                status = MPI_Send(&aux1,5, MPI_INT,fuente,0, MPI_COMM_WORLD);
                status1 = MPI_Send(&aux2,4, MPI_INT,fuente,0, MPI_COMM_WORLD);
            }
       
        printf("%f\n",perimetrototal);
}  
    

    if (rank > 0) 
    {
     
         status = MPI_Recv(&aux1,5, MPI_INT,0,MPI_ANY_TAG, MPI_COMM_WORLD,&rec_stat);
         status1=MPI_Recv(&aux2,4,MPI_INT,0,MPI_ANY_TAG, MPI_COMM_WORLD,&rec_stat);
         for(int i =aux1*rank+aux2+1;i<=aux1*rank+aux1+aux2;i++)
            {
                    
                perimetro=buscartriangulo("triangulo",i,triangulo,perimetro);
                MPI_Reduce(&perimetro,&perimetrototal,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
            }
                
    }


    MPI_Finalize();


    return 0;
}