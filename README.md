# Simulador de Reingreso Atmosférico - Misión Artemis (Problema 4)

**Universidad Tecnológica Nacional – Facultad Regional Resistencia**  
**Cátedra:** Algoritmos y Estructuras de Datos  
**Año:** 2026  

## Integrantes del Grupo 4
* **Basterra**, Joaquín Nicolás
* **Bianchini**, Santino
* **Mañanes Amarilla**, Lautaro Facundo
* **Ponce**, Marcos Lautaro
* **San Vicente**, María Juliana

---

## Descripción del Problema
Este proyecto implementa una simulación computacional modular en C para modelar la fase final de reingreso atmosférico y amerizaje de la cápsula Orión de la misión Artemis IV.

El programa evalúa:
1. **Trabajo total realizado por la fuerza de rozamiento atmosférico ($W_{roz}$):** Aplicando el principio de conservación de la energía entre el inicio de la reentrada (120 km, 11 000 m/s) y la apertura de paracaídas (2.5 km, 25 m/s).
2. **Desaceleración media:** Calculada durante la fase aerodinámica activa y expresada tanto en m/s² como en múltiplos de la gravedad terrestre (g).
3. **Fuerza media de desaceleración del agua:** Dinámica del impacto final en el océano hasta el reposo tras hundirse 1.50 m.
4. **Ventana de Seguridad de Reingreso:** Validación del ángulo de entrada gamma ($5.5^\circ \le \gamma \le 7.0^\circ$) para evitar rebotes atmosféricos o fallos estructurales por exceso de desaceleración.

---

## Estructura del Proyecto

text
artemis_simulador/
├── include/
│   ├── artemis.h         # Estructuras de la cápsula y prototipos físicos
│   └── validaciones.h    # Prototipos de ingreso seguro y control de buffer
├── src/
│   ├── artemis.c         # Lógica y ecuaciones físicas del reingreso
│   ├── validaciones.c    # Implementación de validaciones de entrada
│   └── main.c            # Interfaz CLI y menú principal interactivo
├── .gitignore            # Filtro de archivos binarios y temporales
├── Makefile              # Script de automatización de compilación
└── README.md             # Documentación del proyecto
