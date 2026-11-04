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
