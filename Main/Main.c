#include <stdio.h>

#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"

int main () {
    int opcion;

    do {
        
        printf("\n--- MENU ---\n");
        printf("1. Destinos\n");
        printf("2. Registrar Pasajeros\n");
        printf("3. Reporte Diario\n");
        printf("4. Listado de pasajeros\n");
        printf("0. Salir del programa\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("Mostrando Destinos.....");
                //mostrarDestinos();
                break;
            case 2:
                printf("Registrando pasajero.....");
                //RegistrarPasajero(Pasajero, &cantidadPasajeros);
                break;
            case 3:
                printf("Reporte diario....");
                //reporteDiario();
                break;
            case 4:
                printf("Listado de pasajeros....");
                //listadoDePasajeros();
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