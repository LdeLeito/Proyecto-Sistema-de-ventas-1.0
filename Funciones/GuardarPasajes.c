#include <stdio.h>
#include <stdlib.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/Pasajes.h"


void GuardarPasajesEnArchivo(const struct Pasaje *pasajes, int cantidadPasajes)
{
    // Para no sobrescribir
    FILE *archivo = fopen("pasajes.txt", "a");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    // Guardar solo el último pasaje registrado
    const struct Pasaje *ultimo = &pasajes[cantidadPasajes - 1];
    fprintf(archivo, "%d,%d,%s,%s,%s,%.2f,%s\n",
            ultimo->id,
            ultimo->butaca,
            ultimo->destino,
            ultimo->fecha,
            ultimo->horario,
            ultimo->costo,
            ultimo->id_pasajero);

    fclose(archivo);
    printf("Pasaje guardado exitosamente en 'pasajes.txt'.\n");
}
