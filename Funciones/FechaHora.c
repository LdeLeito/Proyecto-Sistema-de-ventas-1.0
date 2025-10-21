#include <stdio.h>
#include <time.h>
#include "../Headers/Fecha.h"

// Obtiene la fecha actual del sistema
void ObtenerFechaActual(struct FechaHora *f)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    f->dia = tm_info->tm_mday;
    f->mes = tm_info->tm_mon + 1; // Los meses van de 0 a 11
    f->anio = tm_info->tm_year + 1900;
}

// Obtiene la hora actual del sistema
void ObtenerHoraActual(struct FechaHora *f)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    f->hora = tm_info->tm_hour;
    f->minuto = tm_info->tm_min;
}

// Muestra fecha y hora en pantalla
void MostrarFechaHora(const struct FechaHora *f)
{
    printf("Fecha: %02d/%02d/%04d - Hora: %02d:%02d\n",
           f->dia, f->mes, f->anio, f->hora, f->minuto);
}

// Genera cadenas formateadas de fecha y hora (por ejemplo para guardar en structs o archivos)
void FormatearFechaHora(const struct FechaHora *f, char *fechaStr, char *horaStr)
{
    sprintf(fechaStr, "%02d/%02d/%04d", f->dia, f->mes, f->anio);
    sprintf(horaStr, "%02d:%02d", f->hora, f->minuto);
}