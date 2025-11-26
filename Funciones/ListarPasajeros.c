#include <stdio.h>
#include <string.h>
#include "../headers/Pasajeros.h"
#include "../headers/Pasajes.h"


void ListarPasajeros(const struct Pasajero *pasajeros, int cantidadPasajeros) {
    printf("+--------+----------------------+----------------------+--------------+\n");
    printf("|   ID   |        Nombre        |       Apellido       |     DNI      |\n");
    printf("+--------+----------------------+----------------------+--------------+\n");
    for (int i = 0; i < cantidadPasajeros; ++i) {
        printf("| %-6s | %-20s | %-20s | %-12s |\n",
               pasajeros[i].idpasajero,
               pasajeros[i].nombre,
               pasajeros[i].apellido,
               pasajeros[i].dni);
    }
    printf("+--------+----------------------+----------------------+--------------+\n");
}
