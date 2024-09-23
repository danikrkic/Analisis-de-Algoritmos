/*

 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de Algoritmos
 Grupo: 3CM3
 Profesor: Benjamín Luna Benoso
 Alumnos: López Domínguez Daniel Efraín y Vite Valois Omar Abdiel
 Práctica No.1
 Determinacion experimental de la complejidad temporal del algoritmo Punto Silla

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Pruebas 1000


/*En esta funcion creamos un arreglo dinamico que tenga el tamaño TAM, 
regresa un apuntador a ese arreglo*/

int *CrearArreglo(int tam)
{
    int *Arreglo = (int*)malloc(sizeof(int)*tam);
    if(Arreglo ==  NULL)
    {
        exit(0);
    }
    return Arreglo;
}


/*En esta funcion modificamos el arreglo creado para llenarlo de numero aleatorios,
estos numeros dependeran de TAM*/

void llenarArreglo(int *Arreglo, int tam)
{
    int i;
    for(i = 0; i < tam; i++)
    {
        Arreglo[i] = rand() % tam;
    }
}

/*Esta funcion sera para llenar el arreglo de manera que podamos observar el mejor y el peor caso*/

void llenarArregloAscendente(int *Arreglo, int tam)
{
    int i;
    for( i = 0; i < tam; i++)
    {
        Arreglo[i] = i;
    }
}

void llenarArregloDescendente(int *Arreglo, int tam)
{
    int i;
    for( i = 0; i < tam; i++)
    {
        Arreglo[i] = tam - i;
    }
}

/*Funcion para imprimir el arreglo, solo recorre el arreglo linealmente*/

void imprimirArreglo(int *Arreglo, int tam)
{
    int i; 
    for(i = 0; i < tam; i++)
    {
        printf("%d\t", Arreglo[i]);
    }
    puts("");
}

/*Funcion que recopila la manera en la que se creara, llenara e imprimira el arreglo */

int *GenerarArreglo(int tam, int opcion)
{
    int *Arreglo = NULL;
    switch (opcion)
    {
    case 1:
    {
    Arreglo = CrearArreglo(tam);
    llenarArregloAscendente(Arreglo, tam);
    imprimirArreglo(Arreglo, tam);
    return Arreglo;
    }
    break;
    
    case 2:
    {
    Arreglo = CrearArreglo(tam);
    llenarArregloDescendente(Arreglo, tam);
    imprimirArreglo(Arreglo, tam);
    return Arreglo;
    }
    break;

    default:
        {
        Arreglo = CrearArreglo(tam);
        llenarArreglo(Arreglo, tam);
        imprimirArreglo(Arreglo, tam);
        return Arreglo;
        }
        break;
    }
    
}


int encontrarPrimerMaximoLocal(int *A, int tam, int *cont) {
    int i; (*cont)++;                           //Declaracion i;
    (*cont)++;                                  //Asignacion i
    for (i = 1; i < tam - 1; i++)               // Inicia en 1 y termina en tam-2 para evitar desbordamiento
    {   
        (*cont)++;                              //Comparacion i < tam
        (*cont)+2;                              //Comparacion maximos
        if (A[i-1] < A[i] && A[i] < A[i+1]) {   // Condición de máximo local
            printf("El primer maximo local se encuentra en la posicion %d, valor: %d\n", (i+1), A[i]);
            (*cont)++;                          //Retorno
            return i;                           // Retorna el índice del primer máximo local encontrado
        }
        (*cont)++;                              //incremento de i
    }
    (*cont)++;                                  //Final del for
    printf("No se encontro ningun maximo local.\n");
    (*cont)++;                                  //retorno
    return -1;                                  // Si no se encuentra un máximo local
}

void casos(FILE *fp)
{
    int tam = 5;
    int i, cont, opcion;

    printf("Oprima 1 para mejor caso, 2 para peor caso y 3 para generar una matriz aleatoria\n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
    {
        fp = fopen("MejorCasoPrimerMaximoLocal.csv","w");
        for(i = 0; i < Pruebas; i++)
        {
            cont = 0;
            int *Arreglo = GenerarArreglo(tam,opcion);
            encontrarPrimerMaximoLocal(Arreglo, tam, &cont);
            fprintf(fp, "%d,%d\n", tam, cont);
            tam++;
        }
    }
        break;
    case 2:
    {
        fp = fopen("PeorCasoPrimerMaximoLocal.csv","w");
        for(i = 0; i < Pruebas; i++)
        {
            cont = 0;
            int *Arreglo = GenerarArreglo(tam,opcion);
            encontrarPrimerMaximoLocal(Arreglo, tam, &cont);
            fprintf(fp, "%d,%d\n", tam, cont);
            tam++;
        }   
    }
    default:
    {
        fp = fopen("CasosAleatoriosPrimerMaximoLocal.csv","w");
        for(i = 0; i < Pruebas; i++)
        {
            cont = 0;
            int *Arreglo = GenerarArreglo(tam,opcion);
            encontrarPrimerMaximoLocal(Arreglo, tam, &cont);
            fprintf(fp, "%d,%d\n", tam, cont);
            tam++;
        }
    }
        break;
    }
    fclose(fp);
}

/*Funcion principal, se creo un archivo donde se contaron los pasos*/

int main() {

    FILE *fp = NULL;
    srand(time(NULL));

    casos(fp);

    return 0;
}