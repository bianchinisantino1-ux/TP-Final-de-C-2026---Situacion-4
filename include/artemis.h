#ifndef ARTEMIS_H
#define ARTEMIS_H

#define PI 3.14159265358979323846
#define GRAVEDAD 9.81

typedef struct {
    double masa;            // en kg (10400 kg)
    double altitud_inicio;  // en m (120000 m)
    double velocidad_inicio;// en m/s (11000 m/s)
    double altitud_parac;   // en m (2500 m)
    double velocidad_parac; // en m/s (25 m/s)
    double profund_agua;    // en m (1.5 m)
    double gamma_deg;       // ángulo de entrada en grados
} CapsulaOrion;

typedef struct {
    double trabajo_rozamiento;
    double desaceleracion_m_s2;
    double desaceleracion_g;
    double fuerza_agua;
    int es_seguro;
} ResultadosSimulacion;

CapsulaOrion inicializar_capsula(double gamma_deg);
ResultadosSimulacion calcular_reingreso(const CapsulaOrion *c);

#endif
