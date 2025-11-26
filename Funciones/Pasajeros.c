#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/Pasajes.h"
#include "../headers/Utiles.h"

void RegistrarPasajero(struct Pasajero *pasajeros, int *cantidadPasajeros)
{
    if (!pasajeros || !cantidadPasajeros)
        return;

    if (*cantidadPasajeros >= 99999)
    {
        printf("No se pueden registrar más pasajeros (límite 99999).\n");
        return;
    }

    struct Pasajero nuevoPasajero;
    memset(&nuevoPasajero, 0, sizeof(nuevoPasajero));

    printf("---------------------------------------\n");
    printf("----- Registro de Nuevo Pasajero -----\n");

    printf("Ingrese el nombre del pasajero: ");
    LeerCadenaSeguro(nuevoPasajero.nombre, NOMBRE_MAX);

    printf("Ingrese el apellido del pasajero: ");
    LeerCadenaSeguro(nuevoPasajero.apellido, APELLIDO_MAX);

    printf("Ingrese el DNI del pasajero: ");
    LeerCadenaSeguro(nuevoPasajero.dni, DNI_MAX);

    printf("Ingrese email del pasajero: ");
    LeerCadenaSeguro(nuevoPasajero.email, EMAIL_MAX);

    printf("Ingrese el teléfono del pasajero: ");
    LeerCadenaSeguro(nuevoPasajero.telefono, TELEFONO_MAX);

    printf("Ingrese la dirección del pasajero: ");
    LeerCadenaSeguro(nuevoPasajero.direccion, DIR_MAX);

    printf("---------------------------------------\n");

    // Generar ID seguro y comprobar resultado
    int nextId = *cantidadPasajeros + 1;
    int written = snprintf(nuevoPasajero.idpasajero, IDPASAJERO_MAX, "%05d", nextId);
    if (written < 0 || written >= IDPASAJERO_MAX)
    {
        printf("Error al generar ID del pasajero. Operación cancelada.\n");
        return;
    }

    // Guardar en el arreglo y actualizar contador
    pasajeros[*cantidadPasajeros] = nuevoPasajero;
    (*cantidadPasajeros)++;

    printf("Pasajero registrado exitosamente. ID asignado: %s\n", nuevoPasajero.idpasajero);
    printf("---------------------------------------\n");

    // Persistir en archivo
    GuardarPasajerosEnArchivo(pasajeros, *cantidadPasajeros);
}