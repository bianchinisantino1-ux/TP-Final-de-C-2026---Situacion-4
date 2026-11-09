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
