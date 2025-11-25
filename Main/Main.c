#include <stdio.h>
#include "../Headers/Pasajeros.h"
#include "../Headers/Fecha.h"
#include "../Headers/Destinos.h"
#include "../Headers/Pasajes.h"
#include "../Headers/Pasajeros.h"
#include "../Headers/Utiles.h"

struct Pasajero pasajero[100];
struct Viaje viaje[VIAJES_MAX];
int cantidadPasajeros = 0;
int cantidadViajes = 0;
int main(void)
{
    int opcion;

    do
    {
        printf("-------------------------------\n");
        printf("Bienvenido al sistema de gestión de pasajes\n");
        printf("-------------------------------\n");
        printf("1. Mostrar destinos disponibles\n");
        printf("2. Registrar nuevo pasajero\n");
        printf("3. Registrar pasaje en viaje\n");
        printf("4. Generar reporte diario\n");
        printf("5. Listado de pasajeros\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 1:
            printf("Mostrando Destinos.....\n");
            // LLamamos a la funcion de mostrar destinos
            MostrarDestinosDisponibles();
            break;
        case 2:
            printf("Registrando pasajero.....\n");
            RegistrarPasajero(pasajero, &cantidadPasajeros);
            break;
        case 3:
            printf("Registrando pasaje en viaje....\n");
            RegistrarPasajeEnViaje(viaje, &cantidadViajes, pasajero, cantidadPasajeros);
            break;
        case 4:
            printf("Reporte diario....\n");
            // reporteDiario();
            break;
        case 5:
            printf("Listado de pasajeros....\n");
            ListarPasajeros(pasajero, cantidadPasajeros);
            break;
        case 0:
            printf("Saliendo del programa.\n");
            break;
        default:
            printf("Opcion invalida. Intente nuevamente\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}