#include <stdio.h>
#include <string.h>
#include "../headers/Pasajeros.h"
#include "../headers/Pasajes.h"

void ListarPasajesConPasajeros(struct Pasaje *pasajes, int cantidadPasajes, struct Pasajero *pasajeros, int cantidadPasajeros)
{
    printf("+----+--------+------------+--------+------------------------------+\n");
    printf("| ID | Butaca |   Fecha    |  Hora  |        Pasajero             |\n");
    printf("+----+--------+------------+--------+------------------------------+\n");

    for (int i = 0; i < cantidadPasajes; i++)
    {
        // Buscar el pasajero asociado al pasaje
        char nombreCompleto[61] = "Desconocido";
        for (int j = 0; j < cantidadPasajeros; j++)
        {
            if (strcmp(pasajes[i].id_pasajero, pasajeros[j].idpasajero) == 0)
            {
                snprintf(nombreCompleto, sizeof(nombreCompleto), "%s %s", pasajeros[j].nombre, pasajeros[j].apellido);
                break;
            }
        }

        printf("| %-2d | %-6d | %-10s | %-6s | %-28s |\n",
               pasajes[i].id,
               pasajes[i].butaca,
               pasajes[i].fecha,
               pasajes[i].horario,
               nombreCompleto);
    }

    printf("+----+--------+------------+--------+------------------------------+\n");
}