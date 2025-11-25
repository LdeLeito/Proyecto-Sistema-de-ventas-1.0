#include <stdio.h>
#include <stdlib.h>
#include "../headers/Pasajeros.h"
#include "../headers/Pasajes.h"

void GuardarPasajerosEnArchivo(const struct Pasajero *pasajeros, int cantidadPasajeros)
{
    FILE *archivo = fopen("pasajeros.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < cantidadPasajeros; i++)
    {
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%s\n",
                pasajeros[i].idpasajero,
                pasajeros[i].nombre,
                pasajeros[i].apellido,
                pasajeros[i].dni,
                pasajeros[i].email,
                pasajeros[i].telefono,
                pasajeros[i].direccion);
    }

    fclose(archivo);
    printf("Pasajeros guardados exitosamente en 'pasajeros.txt'.\n");
}