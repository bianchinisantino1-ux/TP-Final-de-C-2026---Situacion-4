#ifndef ARTEMIS_H
#define ARTEMIS_H

#define GRAVEDAD 9.80

typedef struct {
    double masa_kg;             // 10400.0 kg
    double v_inicial_ms;        // 11000.0 m/s
    double h_inicial_m;         // 120000.0 m
    double v_paracaldas_ms;     // 25.0 m/s
    double h_paracaldas_m;      // 2500.0 m
    double v_impacto_ms;        // 8.0 m/s
    double duracion_fase_s;     // 400.0 s
    double hundimiento_m;       // 1.50 m
} CapsulaOrion;

typedef struct {
    double trabajo_rozamiento_J;
    double desaceleracion_ms2;
    double desaceleracion_g;
    double fuerza_impacto_N;
    double fuerza_impacto_g;
    int reingreso_exitoso;      // 1: Exito, 0: Fracaso
    char causa_fallo[120];
} ResultadoReingreso;

// Prototipos de funciones
ResultadoReingreso calcular_reingreso(const CapsulaOrion *capsula, double angulo_gamma);

#endif
