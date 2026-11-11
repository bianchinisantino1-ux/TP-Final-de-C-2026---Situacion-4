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
