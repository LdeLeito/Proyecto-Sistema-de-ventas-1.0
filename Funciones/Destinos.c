// funciones/Destinos.c
#include <stdio.h>
#include <string.h>
#include "../headers/Destinos.h"

const char *destinosDisponibles[] = {
    "Esquel",
    "Trevelin",
    "Comodoro Rivadavia",
    "Bariloche",
    "Puerto Madryn"
};
const int destinosCount = sizeof(destinosDisponibles) / sizeof(destinosDisponibles[0]);

void MostrarDestinosDisponibles(void) {
    printf("Destinos disponibles:\n");
    for (int i = 0; i < destinosCount; ++i) {
        printf("%d. %s\n", i + 1, destinosDisponibles[i]);
    }
}

int ValidarDestino(const char *destino) {
    for (int i = 0; i < destinosCount; ++i) {
        if (strcmp(destino, destinosDisponibles[i]) == 0) return 1;
    }
    return 0;
}