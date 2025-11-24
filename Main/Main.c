#include <stdio.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
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
        printf("3. Generar reporte diario\n");
        printf("4. Listado de pasajeros\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 1:
            printf("Mostrando Destinos.....");
            // mostrarDestinos();
            break;
        case 2:
            printf("Registrando pasajero.....");
            // RegistrarPasajero(Pasajero, &cantidadPasajeros);
            break;
        case 3:
            printf("Reporte diario....");
            // reporteDiario();
            break;
        case 4:
            printf("Listado de pasajeros....");
            // listadoDePasajeros();
            break;
        case 0:
            printf("Saliendo del programa.");
            break;
        default:
            printf("Opcion invalida. Intente nuevamente\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}