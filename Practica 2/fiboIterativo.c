/*

 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de Algoritmos
 Grupo: 3CM3
 Profesor: Benjamín Luna Benoso
 Alumnos: López Domínguez Daniel Efraín y Vite Valois Omar Abdiel
 Práctica No.1
 Determinacion experimental de la complejidad temporal del algoritmo de Fibonacci de manera iterativa

*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 100

void Fibonacci(int n, int *contador) {
    unsigned long long a = 0, b = 1, temp;
    (*contador) += 3;

    // Caso especial si n es 1 o 0
    if (n >= 1) {
        printf("%llu\t ", a);  // Primer número de la serie (Fibonacci(0))
        (*contador)++;
    }

    if (n >= 2) {
        printf("%llu\t ", b);  // Segundo número de la serie (Fibonacci(1))
        (*contador)++;
    }

    // Imprimir el resto de la serie
    (*contador)++;
    for (int i = 3; i <= n; i++) 
    {
        (*contador)++;
        temp = a + b;           (*contador)++;
        printf("%llu\t ", temp);  // Imprimir el siguiente número
        a = b;                  (*contador)++;
        b = temp;               (*contador)++;
        (*contador)++;
    }
    (*contador)++;
    printf("\n\n");  // Nueva línea al final de la serie
}

int casos() {
    FILE *fp = fopen("RegistroFibonacciIterativo.csv", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    fprintf(fp, "Longitud Fibonacci,Numero de pasos\n");  // Encabezado
    for (int iterador = 0; iterador < TAM; iterador++) {
        int contador = 0;
        Fibonacci(iterador, &contador);
        //printf("Numero de pasos para Fibonacci(%d): %d\n", iterador, contador);
        fprintf(fp, "%d,%d\n", iterador, contador);  // Nueva línea para cada entrada
    }

    fclose(fp);  // Asegurarse de cerrar el archivo
    return 0;
}

int main() {
    casos();
    return 0;
}
