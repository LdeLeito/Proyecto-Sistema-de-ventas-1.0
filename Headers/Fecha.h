#ifndef FECHA_H
#define FECHA_H

// Estructura para almacenar fecha y hora
struct FechaHora {
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;
};

// Prototipos de funciones
void ObtenerFechaActual(struct FechaHora *f);
void ObtenerHoraActual(struct FechaHora *f);
void MostrarFechaHora(const struct FechaHora *f);
void FormatearFechaHora(const struct FechaHora *f, char *fechaStr, char *horaStr);

#endif