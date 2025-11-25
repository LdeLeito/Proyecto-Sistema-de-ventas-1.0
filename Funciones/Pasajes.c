#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/Pasajes.h"
#include "../headers/Viajes.h" // para la definición de struct Viaje en persistencia
#include "../headers/Utiles.h"
#include "../headers/Fecha.h"

void InicializarPasaje(struct Pasaje *p)
{
    if (!p)
        return;
    p->id = 0;
    p->butaca = 0;
    p->destino[0] = '\0';
    p->fecha[0] = '\0';
    p->horario[0] = '\0';
    p->costo = 0.0f;
    p->id_pasajero[0] = '\0';
}

int ValidarButaca(int butaca)
{
    return (butaca >= 1 && butaca <= BUTACA_MAX);
}

void MostrarPasaje(const struct Pasaje *p)
{
    if (!p)
        return;
    printf("ID:%d Butaca:%d Dest:%s Fecha:%s Hora:%s Costo:%.2f IDPasajero:%s\n",
           p->id, p->butaca, p->destino, p->fecha, p->horario, p->costo, p->id_pasajero);
}

// Guarda un pasaje en formato CSV con campo id_viaje al inicio.
// Retorna 1 en éxito, 0 en error
int GuardarPasajeEnArchivo(FILE *f, const struct Pasaje *p, int id_viaje)
{
    if (!f || !p)
        return 0;
    // Formato: id_viaje,id_pasaje,butaca,destino,fecha,horario,costo,id_pasajero\n
    if (fprintf(f, "%d,%d,%d,%s,%s,%s,%.2f,%s\n",
                id_viaje,
                p->id,
                p->butaca,
                p->destino,
                p->fecha,
                p->horario,
                p->costo,
                p->id_pasajero) < 0)
    {
        return 0;
    }
    return 1;
}

//Guarda todos los viajes y sus pasajes en un CSV (sobrescribe).
// Retorna 1 en éxito, 0 en error.
int GuardarTodosLosViajesCSV(const struct Viaje *viajes, int cantidadViajes, const char *filename)
{
    if (!viajes || !filename)
        return 0;
    FILE *f = fopen(filename, "w");
    if (!f)
        return 0;
    for (int i = 0; i < cantidadViajes; ++i)
    {
        const struct Viaje *v = &viajes[i];
        for (int j = 0; j < v->cantidadPasajes; ++j)
        {
            if (!GuardarPasajeEnArchivo(f, &v->pasajes[j], v->id_viaje))
            {
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 1;
}

// Carga viajes desde CSV con el formato usado en GuardarTodosLosViajesCSV.
// Si el archivo no existe, retorna 1 con cantidadViajes = 0.
// Retorna 1 en éxito, 0 en error de lectura/parsing
int CargarViajesDesdeCSV(struct Viaje *viajes, int *cantidadViajes, const char *filename)
{
    if (!viajes || !cantidadViajes || !filename)
        return 0;
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        // archivo no existe: no es error, simplemente no hay viajes guardados
        *cantidadViajes = 0;
        return 1;
    }

    char linea[512];
    int maxViajes = VIAJES_MAX;
    *cantidadViajes = 0;

    while (fgets(linea, sizeof(linea), f))
    {
        // parsear: id_viaje,id_pasaje,butaca,destino,fecha,horario,costo,id_pasajero
        int id_viaje, id_pasaje, butaca;
        char destino[DESTINO_MAX], fecha[FECHA_MAX], horario[HORARIO_MAX], id_pasajero[IDPASAJERO_MAX];
        float costo;
        // usar sscanf con protección
        int campos = sscanf(linea, "%d,%d,%d,%49[^,],%10[^,],%5[^,],%f,%5s",
                            &id_viaje, &id_pasaje, &butaca, destino, fecha, horario, &costo, id_pasajero);
        if (campos < 8)
        {
            // línea inválida: ignorar o tratar como error
            continue;
        }

        // buscar o crear viaje con id_viaje
        int idx = -1;
        for (int i = 0; i < *cantidadViajes; ++i)
        {
            if (viajes[i].id_viaje == id_viaje)
            {
                idx = i;
                break;
            }
        }
        if (idx == -1)
        {
            if (*cantidadViajes >= maxViajes)
            {
                fclose(f);
                // no hay espacio para más viajes 
                return 0;
            }
            idx = *cantidadViajes;
            viajes[idx].id_viaje = id_viaje;
            strncpy(viajes[idx].destino, destino, DESTINO_MAX - 1);
            viajes[idx].destino[DESTINO_MAX - 1] = '\0';
            strncpy(viajes[idx].fecha, fecha, FECHA_MAX - 1);
            viajes[idx].fecha[FECHA_MAX - 1] = '\0';
            strncpy(viajes[idx].horario, horario, HORARIO_MAX - 1);
            viajes[idx].horario[HORARIO_MAX - 1] = '\0';
            viajes[idx].cantidadPasajes = 0;
            for (int k = 0; k <= BUTACA_MAX; ++k)
                viajes[idx].asientos_ocupados[k] = 0;
            (*cantidadViajes)++;
        }

        // agregar pasaje al viaje idx si hay espacio
        if (viajes[idx].cantidadPasajes < PASAJES_MAX)
        {
            struct Pasaje *p = &viajes[idx].pasajes[viajes[idx].cantidadPasajes];
            p->id = id_pasaje;
            p->butaca = butaca;
            strncpy(p->destino, destino, DESTINO_MAX - 1);
            p->destino[DESTINO_MAX - 1] = '\0';
            strncpy(p->fecha, fecha, FECHA_MAX - 1);
            p->fecha[FECHA_MAX - 1] = '\0';
            strncpy(p->horario, horario, HORARIO_MAX - 1);
            p->horario[HORARIO_MAX - 1] = '\0';
            p->costo = costo;
            strncpy(p->id_pasajero, id_pasajero, IDPASAJERO_MAX - 1);
            p->id_pasajero[IDPASAJERO_MAX - 1] = '\0';

            if (butaca >= 1 && butaca <= BUTACA_MAX)
                viajes[idx].asientos_ocupados[butaca] = 1;
            viajes[idx].cantidadPasajes++;
        }
    }

    fclose(f);
    return 1;
}