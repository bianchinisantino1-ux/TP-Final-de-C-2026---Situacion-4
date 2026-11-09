#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"

int main(void) {
    int opcion = 0;
    int simulaciones_realizadas = 0;

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

        if (!leer_entero(&opcion) || opcion < 1 || opcion > 6) {
            printf("[ERROR] Opción inválida. Intente de nuevo.\n");
            continue;
        }

        switch (opcion) {
            case 1: {
                CapsulaOrion c = inicializar_capsula(6.25);
                ResultadosSimulacion r = calcular_reingreso(&c);
                printf("\n--- RESULTADOS REINGRESO ESTANDAR ---\n");
                printf("Trabajo Rozamiento: %.2f GJ\n", r.trabajo_rozamiento / 1e9);
                printf("Desaceleracion Media: %.2f m/s^2 (%.2f g)\n", r.desaceleracion_m_s2, r.desaceleracion_g);
                printf("Fuerza Impacto Agua: %.2f kN\n", r.fuerza_agua / 1000.0);
                simulaciones_realizadas++;
                break;
            }
            case 2: {
                double gamma;
                printf("Ingrese angulo de reingreso gamma (deg): ");
                if (leer_double(&gamma)) {
                    CapsulaOrion c = inicializar_capsula(gamma);
                    ResultadosSimulacion r = calcular_reingreso(&c);
                    printf("\n--- RESULTADOS ANGULO PERSONALIZADO (%.2f deg) ---\n", gamma);
                    printf("Desaceleracion: %.2f g | Estado: %s\n", 
                           r.desaceleracion_g, r.es_seguro ? "SEGURA" : "PELIGROSA");
                    simulaciones_realizadas++;
                }
                break;
            }
            case 3:
                mostrar_analisis_sensibilidad();
                break;
            case 4:
                simular_telemetria_descenso(6.25);
                break;
            case 5: {
                CapsulaOrion c = inicializar_capsula(6.25);
                ResultadosSimulacion r = calcular_reingreso(&c);
                exportar_reporte_txt(&c, &r, "reporte_reingreso.txt");
                break;
            }
            case 6:
                printf("\nSaliendo del simulador Artemis... ¡Hasta luego!\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}

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
