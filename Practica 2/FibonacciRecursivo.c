/*

 Instituto Politécnico Nacional
 Escuela Superior de Cómputo
 Analisis de Algoritmos
 Grupo: 3CM3
 Profesor: Benjamín Luna Benoso
 Alumnos: López Domínguez Daniel Efraín y Vite Valois Omar Abdiel
 Práctica No.2
 Determinacion experimental de la complejidad temporal del algoritmo de Fibonacci Recursivo

*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 50

// Función recursiva para calcular Fibonacci
unsigned long long Fibonacci(int n, unsigned long long *contador) {

    if (n == 0) {
        (*contador)++;
        return 0;  // Caso base: Fibonacci(0) = 0
    } else if (n == 1) {
        (*contador)++;
        return 1;  // Caso base: Fibonacci(1) = 1
    } else {
        (*contador)++;
        return Fibonacci(n - 1, contador) + Fibonacci(n - 2, contador);  // Llamadas recursivas
    }
}

int casos() {
    FILE *fp = fopen("RegistroFibonacciRecursivo.csv", "w");
    if (fp == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }
    unsigned long long contador = 0;

    fprintf(fp, "Longitud Fibonacci,Numero de pasos\n");  // Encabezado
    for (int iterador = 0; iterador < TAM; iterador++) {
        contador = 0;
        unsigned long long resultado = Fibonacci(iterador, &contador);
        printf("Fibonacci(%d) = %llu, Numero de pasos: %llu\n", iterador, resultado, contador);
        fprintf(fp, "%d,%llu\n", iterador, contador);  // Guardar en el archivo
    }

    fclose(fp);  // Asegurarse de cerrar el archivo
    return 0;
}

int main() {
    casos();
    return 0;
}
