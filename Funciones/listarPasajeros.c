#include <stdio.h>
#include <stdlib.h>
#include "../cabeceras_h/Pasajeros.h"
#include "../cabeceras_h/Fecha.h"
#include "../cabeceras_h/Pasajes.h"

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
            pasajero[i].nombreCompleto
        );
    }

    printf("+----+--------+------------+--------+------------------------------+\n");
}
