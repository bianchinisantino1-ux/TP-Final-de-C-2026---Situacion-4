#include <stdio.h>
#include "validaciones.h"

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leer_entero_rango(int *dest, int min, int max) {
    int val;
    if (scanf("%d", &val) != 1) {
        limpiar_buffer();
        return 0;
    }
    limpiar_buffer();
    if (val < min || val > max) return 0;
    *dest = val;
    return 1;
}

int leer_double_rango(double *dest, double min, double max) {
    double val;
    if (scanf("%lf", &val) != 1) {
        limpiar_buffer();
        return 0;
    }
    limpiar_buffer();
    if (val < min || val > max) return 0;
    *dest = val;
    return 1;
}
