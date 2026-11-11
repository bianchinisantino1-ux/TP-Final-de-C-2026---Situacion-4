#include <stdio.h>
#include "validaciones.h"

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leer_entero(int *dest) {
    int val;
    if (scanf("%d", &val) != 1) {
        limpiar_buffer();
        return 0;
    }
    limpiar_buffer();
    *dest = val;
    return 1;
}

int leer_double(double *dest) {
    double val;
    if (scanf("%lf", &val) != 1) {
        limpiar_buffer();
        return 0;
    }
    limpiar_buffer();
    *dest = val;
    return 1;
}
