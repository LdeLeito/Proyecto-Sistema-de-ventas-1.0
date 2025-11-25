// funciones/Viajes.c (fragmento)
#include <stdio.h>
#include <string.h>
#include "../headers/Pasajes.h"
#include "../headers/Fecha.h"
#include "../headers/Pasajeros.h"
#include "../headers/Destinos.h"
#include "../headers/Utiles.h" // para LeerCadenaSeguro

int BuscarViajeCoincidente(struct Viaje *viajes, int cantidadViajes, const char *destino, const char *fecha, const char *horario)
{
    for (int i = 0; i < cantidadViajes; ++i)
    {
        if (strcmp(viajes[i].destino, destino) == 0 &&
            strcmp(viajes[i].fecha, fecha) == 0 &&
            strcmp(viajes[i].horario, horario) == 0)
        {
            return i; // índice del viaje
        }
    }
    return -1;
}

int CrearViaje(struct Viaje *viajes, int *cantidadViajes, const char *destino, const char *fecha, const char *horario)
{
    if (*cantidadViajes >= VIAJES_MAX)
        return -1;
    int idx = *cantidadViajes;
    viajes[idx].id_viaje = idx + 1;
    strncpy(viajes[idx].destino, destino, DESTINO_MAX - 1);
    viajes[idx].destino[DESTINO_MAX - 1] = '\0';
    strncpy(viajes[idx].fecha, fecha, FECHA_MAX - 1);
    viajes[idx].fecha[FECHA_MAX - 1] = '\0';
    strncpy(viajes[idx].horario, horario, HORARIO_MAX - 1);
    viajes[idx].horario[HORARIO_MAX - 1] = '\0';
    viajes[idx].cantidadPasajes = 0;
    (*cantidadViajes)++;
    return idx;
}

void RegistrarPasajeEnViaje(struct Viaje *viajes, int *cantidadViajes, struct Pasajero *pasajeros, int cantidadPasajeros)
{
    char destino[DESTINO_MAX];
    char fecha[FECHA_MAX];
    char horario[HORARIO_MAX];
    char idPasajero[IDPASAJERO_MAX];
    float costo;
    int idxViaje;

    printf("Ingrese destino: ");
    LeerCadenaSeguro(destino, DESTINO_MAX);
    if (!ValidarDestino(destino))
    {
        printf("Destino no disponible.\n");
        return;
    }

    printf("Ingrese fecha (dd/mm/yyyy): ");
    LeerCadenaSeguro(fecha, FECHA_MAX);
    printf("Ingrese horario (hh:mm): ");
    LeerCadenaSeguro(horario, HORARIO_MAX);

    idxViaje = BuscarViajeCoincidente(viajes, *cantidadViajes, destino, fecha, horario);
    if (idxViaje >= 0)
    {
        if (viajes[idxViaje].cantidadPasajes >= PASAJES_MAX)
        {
            printf("El viaje está completo. Desea asignarse a otro viaje con el mismo destino/hora? (s/n): ");
            char resp[4];
            LeerCadenaSeguro(resp, 4);
            if (resp[0] == 's' || resp[0] == 'S')
            {
                // buscar otro viaje con mismo destino pero distinto horario/fecha o crear nuevo
                // ejemplo simple: crear nuevo viaje con misma info pero nuevo id
                int nuevoIdx = CrearViaje(viajes, cantidadViajes, destino, fecha, horario);
                if (nuevoIdx >= 0)
                    idxViaje = nuevoIdx;
                else
                {
                    printf("No se pudo crear nuevo viaje.\n");
                    return;
                }
            }
            else
            {
                printf("Operación cancelada.\n");
                return;
            }
        }
    }
    else
    {
        // no existe viaje: crear uno nuevo
        idxViaje = CrearViaje(viajes, cantidadViajes, destino, fecha, horario);
        if (idxViaje < 0)
        {
            printf("No se pueden crear más viajes.\n");
            return;
        }
    }

    // ahora registrar pasaje en viajes[idxViaje]
    struct Pasaje *p = &viajes[idxViaje].pasajes[viajes[idxViaje].cantidadPasajes];
    p->id = viajes[idxViaje].cantidadPasajes + 1;
    // asignar butaca libre (ejemplo: secuencial)
    p->butaca = viajes[idxViaje].cantidadPasajes + 1;
    strncpy(p->destino, destino, DESTINO_MAX - 1);
    strncpy(p->fecha, fecha, FECHA_MAX - 1);
    strncpy(p->horario, horario, HORARIO_MAX - 1);
    printf("Ingrese costo: ");
    char costoStr[20];
    LeerCadenaSeguro(costoStr, 20);
    p->costo = strtof(costoStr, NULL);
    printf("Ingrese ID del pasajero: ");
    LeerCadenaSeguro(idPasajero, IDPASAJERO_MAX);
    strncpy(p->id_pasajero, idPasajero, IDPASAJERO_MAX - 1);

    viajes[idxViaje].cantidadPasajes++;
    printf("Pasaje registrado en viaje ID %d, butaca %d\n", viajes[idxViaje].id_viaje, p->butaca);
}