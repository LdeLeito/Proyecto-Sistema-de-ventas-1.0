#include <stdio.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/pasajes.h"

void RegistrarPasaje(struct Pasaje *pasajes, int *cantidadpasajes)
{
    printf("---------------------------------------\n");
    printf("----- Registro de Nuevo Pasaje -----\n");
    if (*cantidadpasajes >= ID_MAX)
    {
        printf("No se pueden registrar más pasajes. Límite alcanzado.\n");
        return;
    }
    printf("---------------------------------------\n");

    struct FechaHora fechaHoraActual;
    ObtenerFechaActual(&fechaHoraActual);
    ObtenerHoraActual(&fechaHoraActual);
    printf("Fecha y hora actual: ");
    MostrarFechaHora(&fechaHoraActual);
    printf("---------------------------------------\n");
    struct Pasaje nuevoPasaje;

    nuevoPasaje.id = (*cantidadpasajes) + 1;
    
    printf("Ingrese el número de butaca (1-%d): ", BUTACA_MAX);
    scanf("%d", &nuevoPasaje.butaca);

    printf("Ingrese el destino: ");
    scanf("%s", nuevoPasaje.destino);

    FormatearFechaHora(&fechaHoraActual, nuevoPasaje.fecha, NULL);
    FormatearFechaHora(&fechaHoraActual, NULL, nuevoPasaje.horario);

    printf("Ingrese el costo del pasaje: ");
    scanf("%f", &nuevoPasaje.costo);

    printf("Ingrese el ID del pasajero asociado: ");
    scanf("%s", nuevoPasaje.id_pasajero);

    pasajes[*cantidadpasajes] = nuevoPasaje;
    (*cantidadpasajes)++;

    printf("Pasaje registrado exitosamente.\n");
    printf("---------------------------------------\n");
    // Guardar automáticamente después de registrar
    GuardarPasajesEnArchivo(pasajes, *cantidadpasajes);
}