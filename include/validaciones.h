#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Prototipos de funciones para el ingreso seguro y validación de datos
void limpiar_buffer(void);
double leer_double_rango(const char *mensaje, double min, double max);
int leer_entero_rango(const char *mensaje, int min, int max);

#endif
