#include <stdio.h>
#include <stdlib.h>
// Usar rutas relativas al directorio headers para que el indexador de VS Code
// (cpptools) y el compilador encuentren los archivos de cabecera. */
#include "../Headers/Pasajeros.h"
#include "../Headers/Fecha.h"
#include "../Headers/Pasajes.h"

void RegistrarPasajero(struct Pasajero *pasajeros, int *cantidadPasajeros)
{
    if (*cantidadPasajeros >= IDPASAJERO_MAX)
    {
        printf("No se pueden registrar más pasajeros. Límite alcanzado.\n");
        return;
    }
    struct Pasajero nuevoPasajero;
    printf("---------------------------------------\n");
    printf("----- Registro de Nuevo Pasajero -----\n");
    printf("Ingrese el nombre del pasajero: ");
    scanf("%s", nuevoPasajero.nombre);
    printf("Ingrese el apellido del pasajero: ");
    scanf("%s", nuevoPasajero.apellido);
    printf("Ingrese el DNI del pasajero: ");
    scanf("%s", nuevoPasajero.dni);
    printf("Ingrese email del pasajero: ");
    scanf("%s", nuevoPasajero.email);
    printf("Ingrese el teléfono del pasajero: ");
    scanf("%s", nuevoPasajero.telefono);
    printf("Ingrese la dirección del pasajero: ");
    scanf("%s", nuevoPasajero.direccion);
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
