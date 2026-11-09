#ifndef ARTEMIS_H
#define ARTEMIS_H

#define PI 3.14159265358979323846
#define GRAVEDAD 9.81

// Estructura principal de la cápsula
typedef struct {
    double masa;            // en kg
    double altitud_inicio;  // en m
    double velocidad_inicio;// en m/s
    double altitud_parac;   // en m
    double velocidad_parac; // en m/s
    double profund_agua;    // en m
    double gamma_deg;       // ángulo de entrada en grados
} CapsulaOrion;

// Estructura para almacenar resultados de física
typedef struct {
    double trabajo_rozamiento;
    double desaceleracion_m_s2;
    double desaceleracion_g;
    double fuerza_agua;
    int es_seguro;          // 1 si está en ventana (5.5° a 7.0°), 0 si no
} ResultadosSimulacion;

// Prototipos existentes
CapsulaOrion inicializar_capsula(double gamma_deg);
ResultadosSimulacion calcular_reingreso(const CapsulaOrion *c);

// NUEVAS FUNCIONES
void mostrar_analisis_sensibilidad(void);
void simular_telemetria_descenso(double gamma_deg);
void exportar_reporte_txt(const CapsulaOrion *c, const ResultadosSimulacion *r, const char *filename);

#endif
