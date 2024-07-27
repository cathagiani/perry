#ifndef __FERIA_H__
#define __FERIA_H__

#include <stdbool.h>

#define MAX_BOMBAS 20
#define MAX_HERRAMIENTAS 100
#define MAX_FAMILIARES 10

typedef struct coordenada {
    int fil;
    int col;
} coordenada_t;

typedef struct personaje {
    int vida;
    int energia;
    bool camuflado;
    coordenada_t posicion;
} personaje_t;

typedef struct bomba {
    coordenada_t posicion;
    int timer;
    bool desactivada;
} bomba_t;

typedef struct herramienta {
    coordenada_t posicion;
    char tipo;
} herramienta_t;

typedef struct familiar {
    coordenada_t posicion;
    char sentido; // 'A', 'S', 'D' o 'W'
    char inicial_nombre;
} familiar_t;

typedef struct juego {
    personaje_t perry;
    bomba_t bombas[MAX_BOMBAS];
    int tope_bombas;
    herramienta_t herramientas[MAX_HERRAMIENTAS];
    int tope_herramientas;
    familiar_t familiares[MAX_FAMILIARES];
    int tope_familiares;
    int movimientos;
    coordenada_t* robots;
    int cantidad_robots;
} juego_t;

/*
 * Inicializará el juego, cargando toda la información inicial de Perry, los obstáculos, las herramientas y la familia Flynn.
 */
void inicializar_juego(juego_t* juego);

/*
 * Realizará la acción recibida por parámetro. 
 * La acción recibida deberá ser válida.
 * Solo se podrá mover a Perry y camuflarlo.
 */
void realizar_jugada(juego_t* juego, char accion);

/*
 * Imprime el juego por pantalla
 */
void imprimir_terreno(juego_t juego);

/*
 * El juego se dará por ganado cuando estén todas las bombas desactivadas.
 * Si el personaje se queda sin vidas, el juego se dará por perdido.
 * Devuelve:
 * --> 1 si es ganado
 * --> -1 si es perdido
 * --> 0 si se sigue jugando
 */
int estado_juego(juego_t juego);

#endif /* __FERIA_H__ */