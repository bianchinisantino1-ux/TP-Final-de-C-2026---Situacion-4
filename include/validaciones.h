#ifndef VALIDACIONES_H
#define VALIDACIONES_H

void limpiar_buffer(void);
int leer_entero(int *dest);
int leer_double(double *dest);
int leer_entero_rango(int *dest, int min, int max);
int leer_double_rango(double *dest, double min, double max);

#endif
