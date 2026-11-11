#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"

int main(void) {
    int opcion = 0;
    int simulaciones_realizadas = 0;
    CapsulaOrion ultima_c;
    ResultadosSimulacion ultima_r;
    int hay_ultima = 0;

    do {
        printf("\n==================================================\n");
        printf("    SIMULADOR ARTEMIS IV - PROBLEMA 4: REINGRESO   \n");
        printf("==================================================\n");
        printf("1. Ejecutar Simulacion Analitica Estandar (gamma = 6.25 deg)\n");
        printf("2. Simular Reingreso con Angulo Personalizado\n");
        printf("3. Generar Barrido / Analisis de Sensibilidad Angular\n");
        printf("4. Ver Telemetria Estructurada de Descenso\n");
        printf("5. Exportar ULTIMA Simulacion a Reporte (.txt)\n");
        printf("6. Salir\n");
        printf("--------------------------------------------------\n");
        printf("Simulaciones ejecutadas en la sesion: %d\n", simulaciones_realizadas);
        printf("Seleccione una opcion (1-6): ");

        if (!leer_entero_rango(&opcion, 1, 6)) {
            printf("[ERROR] Opción inválida. Intente de nuevo.\n");
            continue;
        }

        switch (opcion) {
            case 1: {
                ultima_c = inicializar_capsula(6.25);
                ultima_r = calcular_reingreso(&ultima_c);
                hay_ultima = 1;
                printf("\n--- RESULTADOS REINGRESO ESTANDAR (gamma = 6.25 deg) ---\n");
                printf("Trabajo Rozamiento: %.2f GJ\n", ultima_r.trabajo_rozamiento / 1e9);
                printf("Desaceleracion Media: %.2f m/s^2 (%.2f g)\n", ultima_r.desaceleracion_m_s2, ultima_r.desaceleracion_g);
                printf("Fuerza Impacto Agua: %.2f kN\n", ultima_r.fuerza_agua / 1000.0);
                printf("Estado: %s\n", ultima_r.es_seguro ? "TRAYECTORIA SEGURA" : "PELIGROSA / FUERA DE VENTANA");
                simulaciones_realizadas++;
                break;
            }
            case 2: {
                double gamma;
                printf("Ingrese angulo de reingreso gamma (entre 0.0 y 90.0 deg): ");
                if (leer_double_rango(&gamma, 0.0, 90.0)) {
                    ultima_c = inicializar_capsula(gamma);
                    ultima_r = calcular_reingreso(&ultima_c);
                    hay_ultima = 1;
                    printf("\n--- RESULTADOS ANGULO PERSONALIZADO (%.2f deg) ---\n", gamma);
                    printf("Trabajo Rozamiento: %.2f GJ\n", ultima_r.trabajo_rozamiento / 1e9);
                    printf("Desaceleracion Media: %.2f m/s^2 (%.2f g)\n", ultima_r.desaceleracion_m_s2, ultima_r.desaceleracion_g);
                    printf("Fuerza Impacto Agua: %.2f kN\n", ultima_r.fuerza_agua / 1000.0);
                    printf("Estado: %s\n", ultima_r.es_seguro ? "TRAYECTORIA SEGURA" : "PELIGROSA / FUERA DE VENTANA");
                    simulaciones_realizadas++;
                } else {
                    printf("[ERROR] Angulo fuera de rango valido.\n");
                }
                break;
            }
            case 3:
                mostrar_analisis_sensibilidad();
                simulaciones_realizadas++;
                break;
            case 4:
                simular_telemetria_descenso(6.25);
                simulaciones_realizadas++;
                break;
            case 5: {
                if (hay_ultima) {
                    exportar_reporte_txt(&ultima_c, &ultima_r, "reporte_reingreso.txt");
                } else {
                    CapsulaOrion c = inicializar_capsula(6.25);
                    ResultadosSimulacion r = calcular_reingreso(&c);
                    exportar_reporte_txt(&c, &r, "reporte_reingreso.txt");
                }
                break;
            }
            case 6:
                printf("\nSaliendo del simulador Artemis... ¡Hasta luego!\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}
