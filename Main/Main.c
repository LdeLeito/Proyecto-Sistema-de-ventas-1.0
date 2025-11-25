// main.c
#include <stdio.h>
#include <stdlib.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/Destinos.h"
#include "../headers/Pasajes.h"
#include "../headers/Viajes.h"
#include "../headers/Utiles.h"

/* Arrays globales del programa */
#define MAX_PASAJEROS 1000

static struct Pasajero pasajeros[MAX_PASAJEROS];
static int cantidadPasajeros = 0;

static struct Viaje viajes[VIAJES_MAX];
static int cantidadViajes = 0;

int main(void)
{
    // Cargar viajes/pasajes guardados (si existe el CSV)
    if (!CargarViajesDesdeCSV(viajes, &cantidadViajes, "viajes_pasajes.csv"))
    {
        printf("Advertencia: no se pudieron cargar viajes desde archivo.\n");
    }

    int opcion = -1;
    char optStr[8];

    do
    {
        printf("\n-------------------------------\n");
        printf("Bienvenido al sistema de gestión de pasajes\n");
        printf("-------------------------------\n");
        printf("1. Mostrar destinos disponibles\n");
        printf("2. Registrar nuevo pasajero\n");
        printf("3. Registrar pasaje en viaje\n");
        printf("4. Generar reporte diario (pendiente)\n");
        printf("5. Listado de pasajeros\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        LeerCadenaSeguro(optStr, sizeof(optStr));
        opcion = atoi(optStr);
        printf("\n");

        switch (opcion)
        {
        case 1:
            MostrarDestinosDisponibles();
            break;
        case 2:
            RegistrarPasajero(pasajeros, &cantidadPasajeros);
            break;
        case 3:
            RegistrarPasajeEnViaje(viajes, &cantidadViajes, pasajeros, cantidadPasajeros);
            break;
        case 4:
            printf("Funcionalidad de reporte diario aún no implementada.\n");
            break;
        case 5:
            ListarPasajeros(pasajeros, cantidadPasajeros);
            break;
        case 0:
            printf("Saliendo del programa.\n");
            // Antes de salir, opcional: guardar viajes/pasajes
            if (!GuardarTodosLosViajesCSV(viajes, cantidadViajes, "viajes_pasajes.csv"))
            {
                printf("Advertencia: no se pudo guardar el archivo de viajes al salir.\n");
            }
            break;
        default:
            printf("Opcion invalida. Intente nuevamente\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}