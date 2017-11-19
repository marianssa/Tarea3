#include <stdio.h>

int main(int argc, char* argv[])
{
FILE *f = fopen("triangulos", "r");

int lado1;
int lado2;
int lado3;

int lado;
float posicion1;
float posicion2;

float distancia1;
float distancia2;
float distancia3;

float perimetro;
float perimetro_total =0;

if (f==NULL)
{
   perror ("Error al abrir archivo triangulos");
   return -1;
}
while (!feof(f))
{
	
	fscanf (f, "%d %d %d\n", &lado1, &lado2, &lado3);
	FILE *f2 = fopen("puntos", "r");
	if (f2==NULL)
	{
   		perror ("Error al abrir archivo puntos");
   		return -1;
	}
	while (!feof(f2))
	{
		fscanf (f2, "%d %f %f\n", &lado, &posicion1, &posicion2);
		if((lado==lado1)||(lado==lado2)||(lado==lado3))
		{
			if(lado==lado1)
			{
				if(posicion1<posicion2)
				{
					distancia1=posicion2-posicion1;
				}
				else
				{
					distancia1=posicion1-posicion2;
				}
			}

			if(lado==lado2)
			{
				if(posicion1<posicion2)
				{
					distancia2=posicion2-posicion1;
				}
				else
				{
					distancia2=posicion1-posicion2;
				}
			}
			if(lado==lado3)
			{

				if(posicion1<posicion2)
				{
					distancia3=posicion2-posicion1;
				}
				else
				{
					distancia3=posicion1-posicion2;;
				}
			}
		}
			
	}
	fclose(f2);
	perimetro=distancia1+distancia2+distancia3;
	perimetro_total=perimetro_total+perimetro;
}
fclose(f);
printf("La suma de todos los perimetros de los triangulos es %f\n",perimetro_total);
return 0;
}
