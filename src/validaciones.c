#include <stdio.h>
#include "../include/validaciones.h"

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

double leer_double_rango(const char *mensaje, double min, double max) {
    double valor;
    int resultado;
