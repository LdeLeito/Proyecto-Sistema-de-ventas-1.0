#include <stdio.h>
#include <stdlib.h>
// Usar rutas relativas al directorio headers para que el indexador de VS Code
// (cpptools) y el compilador encuentren los archivos de cabecera. */
#include "../headers/Pasajeros.h"
#include "../headers/Fecha.h"
#include "../headers/Pasajes.h"
#include "../Headers/Utiles.h"

void RegistrarPasajero(struct Pasajero *pasajeros, int *cantidadPasajeros)
{
    if (*cantidadPasajeros >= 99999)
    {
        printf("No se pueden registrar más pasajeros (límite 99999).\n");
        return;
    }
    struct Pasajero nuevoPasajero;
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

    // Generar ID automático (ej: "00001", "00002", etc.)
    snprintf(nuevoPasajero.idpasajero, IDPASAJERO_MAX, "%05d", *cantidadPasajeros + 1);
    // Incrementar el contador de pasajeros
    pasajeros[*cantidadPasajeros] = nuevoPasajero;
    (*cantidadPasajeros)++;
    printf("Pasajero registrado exitosamente. ID asignado: %s\n", nuevoPasajero.idpasajero);
    printf("---------------------------------------\n");
    // Guardar automáticamente después de registrar
    GuardarPasajerosEnArchivo(pasajeros, *cantidadPasajeros);
}
