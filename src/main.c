#include <stdio.h>
#include "../include/artemis.h"
#include "../include/validaciones.h"

int main(void) {
    CapsulaOrion orion = {
        .masa_kg = 10400.0,
        .v_inicial_ms = 11000.0,
        .h_inicial_m = 120000.0,
        .v_paracaldas_ms = 25.0,
        .h_paracaldas_m = 2500.0,
        .v_impacto_ms = 8.0,
        .duracion_fase_s = 400.0,
        .hundimiento_m = 1.50
    };

    int opcion;
    do {
        printf("\n==================================================\n");
        printf("   SIMULADOR ARTEMIS - PROBLEMA 4: REINGRESO      \n");
        printf("==================================================\n");
        printf("1. Ejecutar Simulacion Analitica Estandar (gamma = 6.25 deg)\n");
        printf("2. Simular Reingreso con Angulo Personalizado\n");
        printf("3. Salir\n");

        opcion = leer_entero_rango("Seleccione una opcion (1-3): ", 1, 3);

