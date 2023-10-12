#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1
#define TAM 1000000


bool* crearArreglo(int tam)
{
	bool* nuevoArreglo = (bool*)calloc(tam,sizeof(bool));

	if(nuevoArreglo == NULL)
	{
		puts("Error al iniciar el arreglo");
		exit(0);
	}

	return nuevoArreglo;
}


void llenarArregloAleatorio(bool* arreglo, int tam)
{
	if(arreglo == NULL)
	{
		puts("Arreglo nulo, error");
		exit(0);
	}

	srand(time(NULL));
	int iterador;
	for(iterador = 0; iterador < tam; iterador++)
	{
		*(arreglo+ iterador) = rand()%2;
	}
}

void imprimirArreglo(bool* arreglo, int tam)
{
	int iterador;
	puts("");
	for(iterador = 0; iterador < tam; iterador++)
	{
		printf("%d ",*(arreglo + iterador));
	}
}

bool* InicializarArreglo(bool* inicio)
{
	bool* arr = crearArreglo(TAM);
	llenarArregloAleatorio(arr, TAM);
	imprimirArreglo(arr, TAM);

	inicio = arr;
}


// primer parte, crear celdas, llenarlas e imprimirlas

bool analizarTernas(bool inicio, bool medio, bool final) 		//si nos fijamos, la regla 110 es un or cuando el
{																//primer elemento es 0, y un or exclusivo cuando
	if(inicio == FALSE)											//el primer elemento es 1
	{
		return (medio || final);
	}
	else 
	{
		return ((medio || final) && !(medio && final));
	}
}


void llenarArregloporValor(bool* arreglo, int posicion, bool valor)
{
	*(arreglo + posicion) = valor;
}


void analizarArreglo(bool* arr1, bool* arr2, int tam)
{
	bool* arreglo1 = arr1;
	bool* arreglo2 = arr2;
	if( arreglo1 == NULL && arreglo2 == NULL )
	{
		puts("Error al analizar");
		exit(0);
	}

	int iterador;

	for(iterador = 0; iterador < tam; iterador++)
	{
		if(iterador == 0)
		{
			*(arreglo2 + iterador) = analizarTernas(*(arreglo1+ tam -1),*(arreglo1), *(arreglo1 + 1));
		}
		else if(iterador == tam-1)
		{
			*(arreglo2 + tam-1) = analizarTernas(*(arreglo1+ tam -2),*(arreglo1 + tam -1), *(arreglo1));
		}
		else{
		*(arreglo2 + iterador) = analizarTernas(*(arreglo1 + iterador -1), *(arreglo1+ iterador ), *(arreglo1 + iterador +1));
	
		}
	}
	puts("");
}

void engrane()
{
	bool* arreglo1 = InicializarArreglo(arreglo1);

	puts("");

	
	bool* arreglo2 = crearArreglo(TAM);
	analizarArreglo(arreglo1, arreglo2, TAM);
	imprimirArreglo(arreglo2,TAM);
	arreglo1 = arreglo2;
	free(arreglo2);
	arreglo2 = NULL;

}

int main()
{
	engrane();
}