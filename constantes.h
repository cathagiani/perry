#ifndef __CONSTANTES_H__
#define __CONSTANTES_H__


const int MAX_GOLOSINAS = 5;
const int MAX_SOMBREROS = 3;
const int TOTAL_HERRAMIENTAS = (MAX_GOLOSINAS + MAX_SOMBREROS);
const int VIDA_INICIAL_PERRY = 3;
const int ENERGIA_INICIAL_PERRY = 100;
const int BOMBAS_INICIALES = 10;
const int LIMITE_MAX_TERRENO = 20;
const int DISTANCIA_PERRY_FAMILIARES_MAXIMA = 1;
const int DISTANCIA_PERRY_ROBOTS_MAXIMA = 2;
const int TOPE_FAMILIARES = 3;
const int ENERGIA_EXTRA = 20;
const int ENERGIA_QUITADA_POR_BOMBA = 10;
const int ENERGIA_QUITADA_POR_ROBOT = 5;
const int CANT_MOVIMIENTOS_APARICION_ROBOT = 10;
const int JUEGO_GANADO = 1;
const int JUEGO_PERDIDO = -1;
const int JUEGO_ACTIVO = 0;
const char PERRY = 'P';
const char SOMBRERO = 'S';
const char GOLOSINAS = 'G';
const char BOMBA = 'B';
const char ROBOTS = 'R';
const char VACIO = '.';
const int PHINEAS_INDICE = 0;
const int FERB_INDICE = 1;
const int CANDACE_INDICE = 2;
#define PHINEAS 'H'
#define FERB 'F'
#define CANDACE 'C'
#define ARRIBA_MAYUS 'W'
#define ARRIBA_MINUS 'w'
#define ABAJO_MAYUS 'S'
#define ABAJO_MINUS 's'
#define DERECHA_MAYUS 'D'
#define DERECHA_MINUS 'd'
#define IZQUIERDA_MAYUS 'A'
#define IZQUIERDA_MINUS 'a'
#define CAMUFLAJE_MAYUS 'Q'
#define CAMUFLAJE_MINUS 'q'



#endif /* __CONSTANTES_H__ */