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
#define TAM 500

int **crearMatriz(int tam)
{
    int i;
    int **Matriz = (int **)malloc(sizeof(int *) * tam);
    if (Matriz == NULL)
    {
        exit(0);
    }
    for (i = 0; i < tam; i++)
    {
        Matriz[i] = (int *)malloc(sizeof(int) * tam);
        if (Matriz[i] == NULL)
        {
            exit(0);
        }
    }
    return Matriz;
}

void liberarMatriz(int **Matriz, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        free(Matriz[i]);
    }
    free(Matriz);
}

void llenarMatriz(int **Matriz, int tam)
{
    int i, j;
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            Matriz[i][j] = rand() % 99;
        }
    }
}

void llenarMatrizMejorCaso(int **Matriz, int tam)
{
    int i, j;
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            Matriz[i][j] = (tam - i);
        }
    }
}

void llenarMatrizPeorCaso(int **Matriz, int tam)
{
    int i, j;

    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            Matriz[i][j] = (tam - j) + i;
        }
    }
}

void imprimirMatriz(int **Matriz, int tam)
{
    int i, j;
    for (i = 0; i < tam; i++)
    {
        for (j = 0; j < tam; j++)
        {
            printf("%d\t ", Matriz[i][j]);
        }
        puts("");
    }
    puts("");
}

int **GeneradorMatriz(int tam, int opcion)
{
    if (opcion == 1)
    {
        int **Matriz = crearMatriz(tam);
        llenarMatrizMejorCaso(Matriz, tam);
        imprimirMatriz(Matriz, tam);
        return Matriz;
    }
    else if (opcion == 2)
    {
        int **Matriz = crearMatriz(tam);
        llenarMatrizPeorCaso(Matriz, tam);
        imprimirMatriz(Matriz, tam);
        return Matriz;
    }
    else
    {
        int **Matriz = crearMatriz(tam);
        llenarMatriz(Matriz, tam);
        imprimirMatriz(Matriz, tam);
        return Matriz;
    }
}

int encontrarMinimoFila(int **Matriz, int fila, int tam, int *contador)
{
    int i;
    (*contador)++;
    int aux = Matriz[fila][0];
    (*contador)++;

    for (i = 1; i < tam; i++)
    {
        (*contador)++;
        if (aux > Matriz[fila][i])
        {
            (*contador)++;
            aux = Matriz[fila][i];
        }
        (*contador)++;
    }
    return aux;
}

int encontrarMaximoColumna(int **Matriz, int columna, int tam, int *contador)
{
    int i;
    (*contador)++;
    int aux = Matriz[0][columna];
    (*contador)++;

    for (i = 1; i < tam; i++)
    {
        (*contador)++;
        if (aux < Matriz[i][columna])
        {
            (*contador)++;
            aux = Matriz[i][columna];
        }
        (*contador)++;
    }
    return aux;
}

int encontrarPuntoSilla(int **Matriz, int tam, int *contador)
{
    int i, j, minFila;
    (*contador) += 3;

    for (i = 0; i < tam; i++)
    {
        (*contador)++;
        minFila = encontrarMinimoFila(Matriz, i, tam, contador);

        for (j = 0; j < tam; j++)
        {
            (*contador)++;
            if (Matriz[i][j] == minFila)
            {
                (*contador)++;
                if (Matriz[i][j] == encontrarMaximoColumna(Matriz, j, tam, contador))
                {
                    (*contador)++;
                    printf("El punto silla se encuentra en la fila %d y la columna %d con valor %d\n", i, j, Matriz[i][j]);
                    return 0;
                }
            }
            (*contador)++;
        }
    }
    return -1;
}

void casos(FILE *fp)
{
    int tam = 2;
    int contador = 0;
    int i;
    int opcion;
    int **Matriz = NULL;
    printf("Oprima 1 para mejor caso, 2 para peor caso y 3 para generar una matriz aleatoria\n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        fp = fopen("RegistroA-MejorCaso.csv", "w");
        for (i = 2; i < TAM + 2; i++)
        {
            Matriz = GeneradorMatriz(tam, opcion);
            contador = 0;  // Reiniciar contador en cada iteración
            encontrarPuntoSilla(Matriz, tam, &contador);
            fprintf(fp, "%d,%d\n", tam, contador);
            liberarMatriz(Matriz, tam);  // Liberar memoria después de cada iteración
            tam++;
        }
        break;

    case 2:
        fp = fopen("RegistroA-PeorCaso.csv", "w");
        for (i = 2; i < TAM + 2; i++)
        {
            Matriz = GeneradorMatriz(tam, opcion);
            contador = 0;
            encontrarPuntoSilla(Matriz, tam, &contador);
            fprintf(fp, "%d,%d\n", tam, contador);
            liberarMatriz(Matriz, tam);
            tam++;
        }
        break;

    default:
        fp = fopen("RegistroA-Aleatorio.csv", "w");
        for (i = 2; i < TAM + 2; i++)
        {
            Matriz = GeneradorMatriz(tam, opcion);
            contador = 0;
            encontrarPuntoSilla(Matriz, tam, &contador);
            fprintf(fp, "%d,%d\n", tam, contador);
            liberarMatriz(Matriz, tam);
            tam++;
        }
        break;
    }

    fclose(fp);
}

int main()
{
    FILE *fp = NULL;
    srand(time(NULL));
    casos(fp);
    return 0;
}
