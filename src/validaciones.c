#include <stdio.h>
#include "../include/validaciones.h"

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

double leer_double_rango(const char *mensaje, double min, double max) {
    double valor;
    int resultado;

    while (1) {
        printf("%s", mensaje);
        resultado = scanf("%lf", &valor);

        if (resultado != 1) {
            printf("[ERROR] Entrada invalida. Debe ingresar un numero.\n");
            limpiar_buffer();
        } else if (valor < min || valor > max) {
            printf("[ERROR] Valor fuera de rango (%.2f - %.2f).\n", min, max);
            limpiar_buffer();
        } else {
            limpiar_buffer();
            return valor;
        }
    }
}

int leer_entero_rango(const char *mensaje, int min, int max) {
    int valor;
    int resultado;

    while (1) {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);

        if (resultado != 1) {
            printf("[ERROR] Entrada invalida. Ingrese un entero.\n");
            limpiar_buffer();
        } else if (valor < min || valor > max) {
            printf("[ERROR] Opcion fuera de rango (%d - %d).\n", min, max);
            limpiar_buffer();
        } else {
            limpiar_buffer();
            return valor;
        }
    }
}

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
