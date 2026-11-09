#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../include/artemis.h"

ResultadoReingreso calcular_reingreso(const CapsulaOrion *capsula, double angulo_gamma) {
    ResultadoReingreso res;
    memset(&res, 0, sizeof(ResultadoReingreso));

    // Validar ventana de seguridad del angulo de reingreso (5.5° <= gamma <= 7.0°)
    if (angulo_gamma < 5.5) {
        res.reingreso_exitoso = 0;
        strcpy(res.causa_fallo, "Rebote Atmosferico (gamma < 5.5 deg). La nave salio despedida al espacio sin frenar.");
        return res;
    } else if (angulo_gamma > 7.0) {
        res.reingreso_exitoso = 0;
        strcpy(res.causa_fallo, "Desaceleracion Excesiva (gamma > 7.0 deg). Destruccion por exceso de calor y carga g.");
        return res;
    }

res.reingreso_exitoso = 1;

    // a. Trabajo total de rozamiento (W_roz = Delta K + Delta U)
    double delta_K = 0.5 * capsula->masa_kg * (pow(capsula->v_paracaldas_ms, 2) - pow(capsula->v_inicial_ms, 2));
    double delta_U = capsula->masa_kg * GRAVEDAD * (capsula->h_paracaldas_m - capsula->h_inicial_m);
    res.trabajo_rozamiento_J = delta_K + delta_U;

    // b. Desaceleracion media
    res.desaceleracion_ms2 = (capsula->v_paracaldas_ms - capsula->v_inicial_ms) / capsula->duracion_fase_s;
    res.desaceleracion_g = fabs(res.desaceleracion_ms2) / GRAVEDAD;

    // c. Fuerza promedio durante amerizaje (impacto en agua)
    double delta_K_impacto = 0.5 * capsula->masa_kg * pow(capsula->v_impacto_ms, 2);
    double f_neta = delta_K_impacto / capsula->hundimiento_m;
    double peso = capsula->masa_kg * GRAVEDAD;

    res.fuerza_impacto_N = f_neta + peso;
    res.fuerza_impacto_g = res.fuerza_impacto_N / peso;

    return res;
}

#include <stdio.h>
#include <math.h>
#include "artemis.h"

// ... (se mantienen inicializar_capsula y calcular_reingreso) ...

void mostrar_analisis_sensibilidad(void) {
    printf("\n=====================================================================\n");
    printf("         BARRIDO DE SENSIBILIDAD: VENTANA DE REINGRESO             \n");
    printf("=====================================================================\n");
    printf(" Angulo (deg) | Desacel. (g) | Trab. Rozamiento (GJ) | Estado        \n");
    printf("---------------------------------------------------------------------\n");

    for (double g = 5.0; g <= 7.5; g += 0.25) {
        CapsulaOrion c = inicializar_capsula(g);
        ResultadosSimulacion r = calcular_reingreso(&c);

        const char *estado;
        if (g < 5.5) {
            estado = "REBOTE ATMOSFERICO";
        } else if (g > 7.0) {
            estado = "EXCESO CARGA G (PELIGRO)";
        } else {
            estado = "TRAYECTORIA SEGURA";
        }

        printf("   %5.2f deg   |   %6.2f g   |    %9.2f GJ   | %s\n",
               g, r.desaceleracion_g, r.trabajo_rozamiento / 1e9, estado);
    }
    printf("=====================================================================\n");
}

void simular_telemetria_descenso(double gamma_deg) {
    printf("\n--- TELEMETRIA PASO A PASO EN TIEMPO DE DESCENSO (gamma = %.2f deg) ---\n", gamma_deg);
    printf(" Altitud (km) | Velocidad (m/s) | Carga g Aprox. | Fase de Mision\n");
    printf("------------------------------------------------------------------------\n");

    double altitudes[] = {120.0, 90.0, 60.0, 30.0, 2.5, 0.0};
    double velocidades[] = {11000.0, 8500.0, 4200.0, 1100.0, 25.0, 0.0};
    const char *fases[] = {
        "EI (Entry Interface)",
        "Pico de Calentamiento",
        "Fase Aerodinámica Máxima",
        "Subsónico / Desaceleración",
        "Despliegue de Paracaídas",
        "Amerizaje / Reposo Final"
    };

    for (int i = 0; i < 6; i++) {
        double g_aprox = (i == 0 || i == 5) ? 1.0 : (2.0 + (i * 1.5));
        printf("   %6.1f km  |   %7.1f m/s  |   %5.1f g      | %s\n",
               altitudes[i], velocidades[i], g_aprox, fases[i]);
    }
    printf("------------------------------------------------------------------------\n");
}

void exportar_reporte_txt(const CapsulaOrion *c, const ResultadosSimulacion *r, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("[ERROR] No se pudo crear el archivo de reporte.\n");
        return;
    }

    fprintf(f, "====================================================\n");
    fprintf(f, "       REPORTE DE SIMULACION DE REINGRESO ARTEMIS   \n");
    fprintf(f, "====================================================\n");
    fprintf(f, "Angulo de Reingreso (gamma): %.2f deg\n", c->gamma_deg);
    fprintf(f, "Estado de Trayectoria: %s\n\n", r->es_seguro ? "SEGURA (DENTRO DE VENTANA)" : "FUERA DE VENTANA SEGURA");
    fprintf(f, "--- RESULTADOS FISICOS ---\n");
    fprintf(f, "Trabajo Rozamiento ($W_roz$): %.4e Joules (%.2f GJ)\n", r->trabajo_rozamiento, r->trabajo_rozamiento / 1e9);
    fprintf(f, "Desaceleracion Media: %.2f m/s^2 (%.2f g)\n", r->desaceleracion_m_s2, r->desaceleracion_g);
    fprintf(f, "Fuerza Media del Agua: %.4e N\n", r->fuerza_agua);
    fprintf(f, "====================================================\n");

    fclose(f);
    printf("\n[OK] Reporte exportado exitosamente a '%s'\n", filename);
}
