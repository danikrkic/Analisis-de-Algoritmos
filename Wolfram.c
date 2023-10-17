#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAM 100
#define TAM2 100

bool* crearArreglo(int tam) {
    bool* nuevoArreglo = (bool*)calloc(tam, sizeof(bool));

    if (nuevoArreglo == NULL) {
        puts("Error al iniciar el arreglo");
        exit(1);
    }

    return nuevoArreglo;
}

void llenarArregloAleatorio(bool* arreglo, int tam) {
    if (arreglo == NULL) {
        puts("Arreglo nulo, error");
        exit(1);
    }

    srand(time(NULL));
    int iterador;
    for (iterador = 0; iterador < tam; iterador++) {
        *(arreglo + iterador) = rand() % 2;
    }
}

void imprimirArreglo(bool* arreglo, int tam) {
    int iterador;
    char c[][6] = { " ", "\u25A0" };
    for (iterador = 0; iterador < tam; iterador++) {
        printf("%s", c[*(arreglo + iterador)]);
    }
}

void copiarArregloBool(bool* Destino, bool* Origen, int tam) {
    if (Destino == NULL || Origen == NULL) {
        puts("Error al copiar las celdas");
        exit(1);
    }
    int iterador;
    for (iterador = 0; iterador < tam; iterador++) {
        *(Destino + iterador) = *(Origen + iterador);
    }
}

bool* InicializarArreglo(int tam) {
    bool* arr = crearArreglo(tam);
    llenarArregloAleatorio(arr, tam);
    imprimirArreglo(arr, tam);
    return arr;
}

bool analizarTernas(int regla, bool inicio, bool medio, bool final) {
    switch (regla) {
        case 110:
            if (inicio == false) {
                return (medio || final);
            } else {
                return ((medio || final) && !(medio && final));
            }
            break;

        case 150:
            return ((inicio && !medio) || (!medio && final));
            break;

        case 54:
            if (inicio == true) {
                return (medio && !final);
            } else {
                return (final);
            }
            break;

        case 30:
            if (inicio == false) {
                return (medio || final);
            } else {
                return (!medio || final);
            }
            break;

        default:
            return false;
    }
}

void analizarArreglo(bool* arr1, bool* arr2, int tam, int regla) {
    if (arr1 == NULL || arr2 == NULL) {
        puts("Error al analizar");
        exit(1);
    }

    for (int iterador = 0; iterador < tam; iterador++) {
        if (iterador == 0) {
            *(arr2 + iterador) = analizarTernas(regla, *(arr1 + tam - 1), *(arr1), *(arr1 + 1));
        } else if (iterador == tam - 1) {
            *(arr2 + tam - 1) = analizarTernas(regla, *(arr1 + tam - 2), *(arr1 + tam - 1), *(arr1));
        } else {
            *(arr2 + iterador) = analizarTernas(regla, *(arr1 + iterador - 1), *(arr1 + iterador), *(arr1 + iterador + 1));
        }
    }
    puts("");
}

void engrane(int regla) {
    bool* arreglo1 = InicializarArreglo(TAM);
    int iteraciones = TAM2;

    do {
        bool* arreglo2 = crearArreglo(TAM);
        analizarArreglo(arreglo1, arreglo2, TAM, regla);
        imprimirArreglo(arreglo2, TAM);
        copiarArregloBool(arreglo1, arreglo2, TAM);
        free(arreglo2);
        arreglo2 = NULL;
        iteraciones--;
    } while (iteraciones != 0);
    free(arreglo1);  // Liberar memoria del arreglo1 al final
}

int main() {
    int regla;
    printf("Elija una regla (110, 150, 54 o 30): ");
    scanf("%d", &regla);
    if (regla != 110 && regla != 150 && regla != 54 && regla != 30) {
        printf("Regla no válida. Elija una de las reglas disponibles.\n");
        return 1;
    }

    engrane(regla);
    return 0;
}
