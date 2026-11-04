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
