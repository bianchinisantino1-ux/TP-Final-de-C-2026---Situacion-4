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

        if (opcion == 1 || opcion == 2) {
            double gamma = (opcion == 1) ? 6.25 : leer_double_rango("Ingrese el angulo de reingreso gamma en grados (0 - 90): ", 0.0, 90.0);
            ResultadoReingreso res = calcular_reingreso(&orion, gamma);

            if (!res.reingreso_exitoso) {
                printf("\n[FALLO DE MISION]: %s\n", res.causa_fallo);
            } else {
                printf("\n--------------------------------------------------\n");
                printf("         REPORTE DE REINGRESO Y AMERIZAJE         \n");
                printf("--------------------------------------------------\n");
                printf("Trabajo de rozamiento (W_roz): %.2e J (%.2f GJ)\n", res.trabajo_rozamiento_J, res.trabajo_rozamiento_J / 1e9);
                printf("Desaceleracion media:         %.2f m/s2 (%.2f g)\n", res.desaceleracion_ms2, res.desaceleracion_g);
                printf("Fuerza media del agua:         %.2f N (%.2f veces el peso)\n", res.fuerza_impacto_N, res.fuerza_impacto_g);
                printf("--------------------------------------------------\n");
            }
        }
    } while (opcion != 3);

    printf("\nSimulacion finalizada. Gracias por usar el Simulador Artemis.\n");
    return 0;
}
