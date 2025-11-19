#include <stdio.h>
#include <stdlib.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/pasajes.h"

void GuardarPasajesEnArchivo(const struct Pasaje *pasajes, int cantidadPasajes)
{
    FILE *archivo = fopen("pasajes.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < cantidadPasajes; i++)
    {
        fprintf(archivo, "%d,%d,%s,%s,%s,%.2f,%s\n",
                pasajes[i].id,
                pasajes[i].butaca,
                pasajes[i].destino,
                pasajes[i].fecha,
                pasajes[i].horario,
                pasajes[i].costo,
                pasajes[i].id_pasajero);
    }

    fclose(archivo);
    printf("Pasajes guardados exitosamente en 'pasajes.txt'.\n");
}