#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "artemis.h"

CapsulaOrion inicializar_capsula(double gamma_deg) {
    CapsulaOrion c;
    c.masa = 10400.0;             // kg
    c.altitud_inicio = 120000.0;  // m (120 km)
    c.velocidad_inicio = 11000.0; // m/s
    c.altitud_parac = 2500.0;     // m (2.5 km)
    c.velocidad_parac = 25.0;     // m/s
    c.profund_agua = 1.5;         // m
    c.gamma_deg = gamma_deg;
    return c;
}

ResultadosSimulacion calcular_reingreso(const CapsulaOrion *c) {
    ResultadosSimulacion r;
    
    // 1. Trabajo de rozamiento (W_roz = Delta_K + Delta_U)
    double delta_K = 0.5 * c->masa * (pow(c->velocidad_parac, 2) - pow(c->velocidad_inicio, 2));
    double delta_U = c->masa * GRAVEDAD * (c->altitud_parac - c->altitud_inicio);
    r.trabajo_rozamiento = delta_K + delta_U;

    // 2. Desaceleracion media aerodinamica
    double distancia = c->altitud_inicio - c->altitud_parac;
    r.desaceleracion_m_s2 = fabs(pow(c->velocidad_parac, 2) - pow(c->velocidad_inicio, 2)) / (2.0 * distancia);
    r.desaceleracion_g = r.desaceleracion_m_s2 / GRAVEDAD;

    // 3. Fuerza media del agua en amerizaje
    double energia_impacto = 0.5 * c->masa * pow(c->velocidad_parac, 2) + (c->masa * GRAVEDAD * c->profund_agua);
    r.fuerza_agua = energia_impacto / c->profund_agua;

    // 4. Ventana de seguridad (5.5 <= gamma <= 7.0)
    if (c->gamma_deg >= 5.5 && c->gamma_deg <= 7.0) {
        r.es_seguro = 1;
    } else {
        r.es_seguro = 0;
    }

    return r;
}

void mostrar_analisis_sensibilidad(void) {
    printf("\n--- BARRIDO / ANALISIS DE SENSIBILIDAD ANGULAR ---\n");
    printf("%-12s | %-15s | %-12s | %-18s\n", "Gamma (deg)", "Desacel. (g)", "Trabajo (GJ)", "Estado");
    printf("---------------------------------------------------------------\n");
    for (double g = 4.0; g <= 8.5; g += 0.5) {
        CapsulaOrion c = inicializar_capsula(g);
        ResultadosSimulacion r = calcular_reingreso(&c);
        printf("%-12.2f | %-15.2f | %-12.2f | %-18s\n",
               g, r.desaceleracion_g, r.trabajo_rozamiento / 1e9,
               r.es_seguro ? "SEGURA" : (g < 5.5 ? "REBOTE ATMOSF." : "DESACEL. EXCESIVA"));
    }
}

void simular_telemetria_descenso(double gamma_deg) {
    printf("\n--- TELEMETRIA ESTRUCTURADA DE DESCENSO (gamma = %.2f deg) ---\n", gamma_deg);
    printf("%-12s | %-15s | %-15s\n", "Altitud (m)", "Velocidad (m/s)", "Etapa");
    printf("---------------------------------------------------\n");
    double alt = 120000.0;
    double vel = 11000.0;
    double pasoS = (120000.0 - 2500.0) / 5.0;
    double pasoV = (11000.0 - 25.0) / 5.0;

    for (int i = 0; i <= 5; i++) {
        printf("%-12.0f | %-15.2f | %-15s\n", alt, vel, i == 5 ? "Paracaidas" : "Reingreso");
        alt -= pasoS;
        vel -= pasoV;
    }
}

void exportar_reporte_txt(const CapsulaOrion *c, const ResultadosSimulacion *r, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("[ERROR] No se pudo crear el archivo %s\n", filename);
        return;
    }
    fprintf(f, "==================================================\n");
    fprintf(f, "      REPORTE DE SIMULACION - ARTEMIS IV\n");
    fprintf(f, "==================================================\n");
    fprintf(f, "Angulo de reingreso (gamma): %.2f deg\n", c->gamma_deg);
    fprintf(f, "Masa de la capsula: %.2f kg\n", c->masa);
    fprintf(f, "Trabajo de rozamiento: %.2f GJ\n", r->trabajo_rozamiento / 1e9);
    fprintf(f, "Desaceleracion media: %.2f m/s^2 (%.2f g)\n", r->desaceleracion_m_s2, r->desaceleracion_g);
    fprintf(f, "Fuerza impacto agua: %.2f kN\n", r->fuerza_agua / 1000.0);
    fprintf(f, "Estado de trayectoria: %s\n", r->es_seguro ? "TRAYECTORIA SEGURA" : "PELIGROSA / FUERA DE VENTANA");
    fprintf(f, "==================================================\n");
    fclose(f);
    printf("\n[EXITO] Reporte exportado correctamente a '%s'\n", filename);
}
