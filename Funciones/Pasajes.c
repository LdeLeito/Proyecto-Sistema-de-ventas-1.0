#include <stdio.h>
#include "../Headers/Pasajeros.h"
#include "../Headers/Fecha.h"
#include "../Headers/Pasajes.h"

void RegistrarPasaje(struct Pasaje *pasajes, int *cantidadpasajes)
{
    printf("---------------------------------------\n");
    printf("----- Registro de Nuevo Pasaje -----\n");

    if (*cantidadpasajes >= PASAJES_MAX)
    {
        printf("El viaje está completo (máximo %d pasajeros). Debe crear otro viaje.\n", PASAJES_MAX);
        return;
    }

    struct FechaHora fechaHoraActual;
    ObtenerFechaActual(&fechaHoraActual);
    ObtenerHoraActual(&fechaHoraActual);

    printf("Fecha y hora actual: ");
    MostrarFechaHora(&fechaHoraActual);
    printf("---------------------------------------\n");

    struct Pasaje nuevoPasaje;
    nuevoPasaje.id = (*cantidadpasajes) + 1;

    // Validar butaca
    do
    {
        printf("Ingrese el número de butaca (1-%d): ", BUTACA_MAX);
        LeerCadenaSeguro(nuevoPasaje.butaca, sizeof(nuevoPasaje.butaca));
        sscanf(nuevoPasaje.butaca, "%d", &nuevoPasaje.butaca);
        if (nuevoPasaje.butaca < 1 || nuevoPasaje.butaca > BUTACA_MAX)
        {
            printf("Número de butaca inválido. Intente nuevamente.\n");
        }
    } while (nuevoPasaje.butaca < 1 || nuevoPasaje.butaca > BUTACA_MAX);

    printf("Ingrese el destino: ");
    scanf("%s", nuevoPasaje.destino);

    // Formatear fecha y hora
    char fechaStr[FECHA_MAX], horaStr[HORARIO_MAX];
    FormatearFechaHora(&fechaHoraActual, fechaStr, horaStr);
    strcpy(nuevoPasaje.fecha, fechaStr);
    strcpy(nuevoPasaje.horario, horaStr);

    printf("Ingrese el costo del pasaje: ");
    scanf("%f", &nuevoPasaje.costo);

    printf("Ingrese el ID del pasajero asociado: ");
    scanf("%s", nuevoPasaje.id_pasajero);

    pasajes[*cantidadpasajes] = nuevoPasaje;
    (*cantidadpasajes)++;

    printf("Pasaje registrado exitosamente. ID asignado: %d\n", nuevoPasaje.id);
    printf("---------------------------------------\n");

    // Guardar automáticamente después de registrar
    GuardarPasajesEnArchivo(pasajes, *cantidadpasajes);
}