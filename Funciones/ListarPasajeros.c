#include <stdio.h>
#include <stdlib.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/pasajes.h"

void listarPasajeros(struct Pasajero *pasajero ,struct Pasaje *pasaje, struct FechaHora *Fecha ,int cantidadPasajeros) 
{
    printf("+----+--------+------------+--------+------------------------------+\n");
    printf("| ID | Butaca |   Fecha    |  Hora  |         Pasajero             |\n");
    printf("+----+--------+------------+--------+------------------------------+\n");

    for (int i = 0; i < cantidadPasajeros; i++) {
        printf("| %-2d | %-6d | %-10i | %-6i | %-28s |\n",
            pasaje[i].id,
            pasaje[i].butaca,
            Fecha[i].dia,
            Fecha[i].hora,
            pasajero[i].nombre, pasajero[i].apellido
        );
    }

    printf("+----+--------+------------+--------+------------------------------+\n");
}
