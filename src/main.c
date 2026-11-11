#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"

int main(void) {
    int opcion = 0;

    do {
        printf("\n==================================================\n");
        printf("    SIMULADOR ARTEMIS IV - PROBLEMA 4: REINGRESO   \n");
        printf("==================================================\n");
        printf("1. Ejecutar Simulacion Estandar (gamma = 6.25 deg)\n");
        printf("2. Ingresar Angulo de Reingreso Personalizado\n");
        printf("3. Salir\n");
        printf("--------------------------------------------------\n");
        printf("Seleccione una opcion (1-3): ");

        if (!leer_entero_rango(&opcion, 1, 3)) {
            printf("[ERROR] Opcion invalida. Intente de nuevo.\n");
            continue;
        }

        switch (opcion) {
            case 1: {
                CapsulaOrion c = inicializar_capsula(6.25);
                ResultadosSimulacion r = calcular_reingreso(&c);
                printf("\n--- RESULTADOS REINGRESO ESTANDAR (gamma = 6.25 deg) ---\n");
                printf("Trabajo Rozamiento: %.2f GJ\n", r.trabajo_rozamiento / 1e9);
                printf("Desaceleracion Media: %.2f m/s^2 (%.2f g)\n", r.desaceleracion_m_s2, r.desaceleracion_g);
                printf("Fuerza Impacto Agua: %.2f kN\n", r.fuerza_agua / 1000.0);
                printf("Estado: %s\n", r.es_seguro ? "TRAYECTORIA SEGURA" : "PELIGROSA / FUERA DE VENTANA");
                break;
            }
            case 2: {
                double gamma;
                printf("Ingrese angulo de reingreso gamma (entre 0.0 y 90.0 deg): ");
                if (leer_double_rango(&gamma, 0.0, 90.0)) {
                    CapsulaOrion c = inicializar_capsula(gamma);
                    ResultadosSimulacion r = calcular_reingreso(&c);
                    printf("\n--- RESULTADOS ANGULO PERSONALIZADO (%.2f deg) ---\n", gamma);
                    printf("Trabajo Rozamiento: %.2f GJ\n", r.trabajo_rozamiento / 1e9);
                    printf("Desaceleracion Media: %.2f m/s^2 (%.2f g)\n", r.desaceleracion_m_s2, r.desaceleracion_g);
                    printf("Fuerza Impacto Agua: %.2f kN\n", r.fuerza_agua / 1000.0);
                    printf("Estado: %s\n", r.es_seguro ? "TRAYECTORIA SEGURA" : "PELIGROSA / FUERA DE VENTANA");
                } else {
                    printf("[ERROR] Angulo fuera de rango valido.\n");
                }
                break;
            }
            case 3:
                printf("\nSaliendo del simulador Artemis... ¡Hasta luego!\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}
