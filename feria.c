#include "feria.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "constantes.h"

/**
* pre condiciones:
* - amplitud debe ser un número entero positivo mayor que cero.
* pos condiciones:
* - devuelve un número entero aleatorio entre 0 y amplitud - 1.
*/
int generar_num_aleatorio(int amplitud){
    return (rand() % amplitud);
}


/**
* pre condiciones:
* - juego debe ser un puntero válido a un juego_t correctamente inicializado.
* - LIMITE_MAX_TERRENO debe ser un valor positivo y definido.
* pos condiciones:
* - devuelve una coordenada_t con valores de fila y columna aleatorios dentro del rango de 0 a LIMITE_MAX_TERRENO - 1.
*/
coordenada_t generar_coordenada(juego_t* juego){
    coordenada_t coordenada;
    coordenada.fil = generar_num_aleatorio(LIMITE_MAX_TERRENO);
    coordenada.col = generar_num_aleatorio(LIMITE_MAX_TERRENO);
    return coordenada;
}


/**
* pre condiciones:
* - juego debe ser un puntero válido a un juego_t correctamente inicializado.
* - terreno debe ser una matriz de caracteres de tamaño LIMITE_MAX_TERRENO x LIMITE_MAX_TERRENO.
* - LIMITE_MAX_TERRENO debe ser un valor positivo y definido.
* - VACIO debe ser un carácter que representa una posición vacía en el terreno.
* pos condiciones:
* - devuelve una coordenada_t que corresponde a una posición vacía en el terreno.
*/
coordenada_t generar_coordenada_vacia(juego_t* juego, char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]){
    coordenada_t coordenada;
    do {
        coordenada.fil = generar_num_aleatorio(LIMITE_MAX_TERRENO);
        coordenada.col = generar_num_aleatorio(LIMITE_MAX_TERRENO);
    } while (terreno[coordenada.fil][coordenada.col] != '.' );

    return coordenada;
}


/**
* pre condiciones:
* - juego->perry debe ser accesible y modificable
* pos condiciones:
* - juego->perry inicializado con:
* -- Vida igual a VIDA_INICIAL_PERRY
* -- Energia igual a ENERGIA_INICIAL_PERRY
* -- Posicion aleatoria dentro del terreno de 20x20
* -- camuflado establecido en false
*/
void inicializar_perry(juego_t* juego) {
    juego->perry.vida = VIDA_INICIAL_PERRY;
    juego->perry.energia = ENERGIA_INICIAL_PERRY;
    juego->perry.posicion = generar_coordenada(juego);
    juego->perry.camuflado = false;
}

/**
* pre condiciones:
* - "bombas[]" debe tener capacidad para "tope_bombas"
* - terreno[20][20] debe ser una matriz 20x20 ya inicializada
* pos condiciones:
* - cada bomba en bombas[] se inicializa con:
* -- Una posicion unica en terreno
* -- Un temporizador entre 50 y 300.
* -- La propiedad desactivada establecida en false.
*/
void inicializar_bombas(juego_t* juego, char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]) {
    for (int i = 0; i < juego->tope_bombas; i++) {
        juego->bombas[i].posicion = generar_coordenada_vacia(juego, terreno);
        juego->bombas[i].timer = rand() % 251 + 50;
        juego->bombas[i].desactivada = false;
        terreno[juego->bombas[i].posicion.fil][juego->bombas[i].posicion.col] = BOMBA;
    }
}


/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - terreno debe ser un arreglo de caracteres de tamaño LIMITE_MAX_TERRENO x LIMITE_MAX_TERRENO.
* - MAX_SOMBREROS debe estar definido y ser un valor válido.
* - La función generar_coordenada_vacia debe estar definida y ser funcional.
* pos condiciones:
* - Los primeros MAX_SOMBREROS elementos de juego->herramientas serán inicializados de la siguiente manera:
*   - tipo será igual a SOMBRERO.
*   - posicion será una coordenada vacía generada aleatoriamente dentro del terreno.
*/
void inicializar_sombreros(juego_t* juego, char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]){
    for (int i = 0; i < MAX_SOMBREROS; i++) {
        juego->herramientas[i].tipo = SOMBRERO;
        juego->herramientas[i].posicion = generar_coordenada_vacia(juego, terreno);
        terreno[juego->herramientas[i].posicion.fil][juego->herramientas[i].posicion.col] = SOMBRERO;
    }

}

/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - terreno debe ser un arreglo de caracteres de tamaño LIMITE_MAX_TERRENO x LIMITE_MAX_TERRENO.
* - MAX_SOMBREROS y TOTAL_HERRAMIENTAS deben estar definidos y ser valores válidos.
* - La función generar_coordenada_vacia debe estar definida y ser funcional.
* pos condiciones:
* - Los elementos de juego->herramientas desde MAX_SOMBREROS hasta TOTAL_HERRAMIENTAS - 1 serán inicializados de la siguiente manera:
*   - tipo será igual a GOLOSINAS.
*   - posicion será una coordenada vacía generada aleatoriamente dentro del terreno.
*/
void inicializar_golosinas(juego_t* juego, char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]){
    for (int i = MAX_SOMBREROS; i < TOTAL_HERRAMIENTAS; i++) {
        juego->herramientas[i].tipo = GOLOSINAS;
        juego->herramientas[i].posicion = generar_coordenada_vacia(juego, terreno);
        terreno[juego->herramientas[i].posicion.fil][juego->herramientas[i].posicion.col] = GOLOSINAS;
    }

}


/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - terreno debe ser un arreglo de caracteres de tamaño LIMITE_MAX_TERRENO x LIMITE_MAX_TERRENO.
* - juego->tope_familiares debe ser un valor válido que indique el número de familiares a inicializar.
* - La función generar_coordenada_vacia debe estar definida y ser funcional.
* - PHINEAS_INDICE, FERB_INDICE, y CANDACE_INDICE deben estar definidos y ser índices válidos dentro del arreglo juego->familiares.
* - DERECHA_MAYUS, IZQUIERDA_MAYUS, y ARRIBA_MAYUS deben estar definidos y ser valores válidos para el campo sentido.
* pos condiciones:
* - Cada familiar en juego->familiares será inicializado de la siguiente manera:
*   - posicion será una coordenada vacía generada aleatoriamente dentro del terreno.
*   - inicial_nombre será asignado en orden de acuerdo a familiares_chars (PHINEAS, FERB, CANDACE).
* - El sentido de los familiares será establecido de la siguiente manera:
*   - PHINEAS tendrá el sentido DERECHA_MAYUS.
*   - FERB tendrá el sentido IZQUIERDA_MAYUS.
*   - CANDACE tendrá el sentido ARRIBA_MAYUS.
*/
void inicializar_familiares(juego_t *juego, char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]) {
    char familiares_chars[] = {PHINEAS, FERB, CANDACE};
    for (int i = 0; i < juego->tope_familiares; i++) {
        juego->familiares[i].posicion = generar_coordenada_vacia(juego, terreno);;
        juego->familiares[i].inicial_nombre = familiares_chars[i % 3];
        terreno[juego->familiares[i].posicion .fil][juego->familiares[i].posicion.col] = juego->familiares[i].inicial_nombre;
    }
    juego->familiares[PHINEAS_INDICE].sentido = DERECHA_MAYUS;
    juego->familiares[FERB_INDICE].sentido = IZQUIERDA_MAYUS;
    juego->familiares[CANDACE_INDICE].sentido = ARRIBA_MAYUS;
}


/**
* pre condiciones:
* - terreno debe ser una matriz de 20x20
* pos condiciones:
* - cada posicion de terreno se inicializa con '.'
*/
void inicializar_terreno(char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]) {
    for (int i = 0; i < LIMITE_MAX_TERRENO; i++) {
        for (int j = 0; j < LIMITE_MAX_TERRENO; j++) {
            terreno[i][j] = '.';
        }
    }
}


void inicializar_juego(juego_t* juego) { 
    inicializar_perry(juego);
    juego->tope_bombas = BOMBAS_INICIALES;
    juego->tope_herramientas = TOTAL_HERRAMIENTAS;
    juego->tope_familiares = TOPE_FAMILIARES;
    juego->cantidad_robots = 0;
    juego->movimientos = 0;

    char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO];
    inicializar_terreno(terreno); 
    inicializar_bombas(juego, terreno);
    inicializar_sombreros(juego, terreno);
    inicializar_golosinas(juego, terreno);
    inicializar_familiares(juego, terreno);
    juego->robots = NULL;       
}


/**
* pre condiciones:
* - Las coordenadas a y b deben ser coordenadas válidas.
* pos condiciones:
* - Devuelve true si las coordenadas a y b son iguales (misma fila y columna).
* - Devuelve false en caso contrario.
*/
bool coordenadas_iguales(coordenada_t a, coordenada_t b) {
    return a.fil == b.fil && a.col == b.col;
}

/**
* pre condiciones:
* - Perry debe ser un personaje válido con una posición válida.
* - coordenada debe ser una coordenada válida.
* pos condiciones:
* - Devuelve true si la posición de Perry es igual a la coordenada dada.
* - Devuelve false en caso contrario.
*/
bool estaPerry(personaje_t Perry, coordenada_t coordenada) {
    return coordenadas_iguales(coordenada, Perry.posicion);
}

/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - coordenada debe ser una coordenada válida.
* pos condiciones:
* - Devuelve true si hay un familiar en la posición indicada por coordenada.
* - Devuelve false en caso contrario.
*/
bool hayUnFamiliar(juego_t* juego, coordenada_t coordenada) {
    for (int i = 0; i < juego->tope_familiares; i++) {
        if (coordenadas_iguales(coordenada, juego->familiares[i].posicion)) {
            return true;
        }
    }
    return false;
}

/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - coordenada debe ser una coordenada válida.
* pos condiciones:
* - Devuelve true si hay una bomba en la posición indicada por coordenada.
* - Devuelve false en caso contrario.
*/
bool hayBombas(juego_t* juego, coordenada_t coordenada) {
    for (int i = 0; i < juego->tope_bombas; i++) {
        if (coordenadas_iguales(coordenada, juego->bombas[i].posicion)) {
            return true;
        }
    }
    return false;
}

/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - coordenada debe ser una coordenada válida.
* pos condiciones:
* - Devuelve true si hay una herramienta en la posición indicada por coordenada.
* - Devuelve false en caso contrario.
*/
bool hayHerramientas(juego_t* juego, coordenada_t coordenada) {
    for (int i = 0; i < juego->tope_herramientas; i++) {
        if (coordenadas_iguales(coordenada, juego->herramientas[i].posicion)) {
            return true;
        }
    }
    return false;
}


/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - coordenada debe ser una coordenada válida.
* pos condiciones:
* - Devuelve true si hay un robot en la posición indicada por coordenada.
* - Devuelve false en caso contrario.
*/
bool hayRobots(juego_t* juego, coordenada_t coordenada) {
    for (int i = 0; i < juego->cantidad_robots; i++) {
        if (coordenadas_iguales(coordenada, juego->robots[i])) {
            return true;
        }
    }
    return false;
}

/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - coordenada debe ser una coordenada válida.
* pos condiciones:
* - Devuelve true si la coordenada no está ocupada por Perry, un familiar, una bomba o una herramienta.
* - Devuelve false en caso contrario.
*/
bool posicion_valida(juego_t* juego, coordenada_t coordenada) {
    return !estaPerry(juego->perry, coordenada) && !hayUnFamiliar(juego, coordenada) && !hayBombas(juego, coordenada) && !hayHerramientas(juego, coordenada) && !hayRobots(juego, coordenada);
}


/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* pos condiciones:
* - Devuelve una coordenada válida y vacía dentro del terreno de juego.
* - La coordenada generada no estará ocupada por Perry, un familiar, una bomba o una herramienta.
*/
coordenada_t generar_coordenada_robots(juego_t* juego){
    coordenada_t coordenada;
    do {
        coordenada.fil = generar_num_aleatorio(LIMITE_MAX_TERRENO);
        coordenada.col = generar_num_aleatorio(LIMITE_MAX_TERRENO);
    } while (!posicion_valida(juego, coordenada));
    return coordenada;
}

/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t.
* pos condiciones:
* - Se reserva memoria para un nuevo robot y se inicializa su posicion
* - La cantidad de robots en el juego se incrementa
*/
void agregar_robot(juego_t* juego) {
    juego->robots = realloc(juego->robots, (size_t)(juego->cantidad_robots + 1) * sizeof(coordenada_t));    
    if (juego->robots == NULL) {
        printf("Error al reservar memoria para un nuevo robot");
        return;
    }
    juego->robots[juego->cantidad_robots].fil = 0;
    juego->robots[juego->cantidad_robots].col = 0;
    juego->cantidad_robots++;
    printf("Oh no! Aparecio un robot!");
    juego->robots[juego->cantidad_robots - 1] = generar_coordenada_robots(juego);
}



/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - Si el contador de movimientos de Perry alcanza o supera 10, se agrega un nuevo robot al juego y se actualiza el terreno.
* - El contador de movimientos de Perry se reinicia a 0 despues de agregar un robot
*/
void aparicion_robot(juego_t* juego) {
    if (juego->movimientos == CANT_MOVIMIENTOS_APARICION_ROBOT) {
        agregar_robot(juego);
        juego->movimientos = 0;
    }
}


/**
* Pre condiciones:
* - las bombas deben estar correctamente inicializadas, con "tope_bombas" bien definido
* - el tamanio del arreglo "bombas" debe ser suficiente para contener la cantidad de elementos definida por "tope_bombas"
*
* Pos condiciones:
* - devuelve el numero de bombas desactivadas en el juego
*/
int bombas_desactivadas(juego_t juego) {
    int contador_bombas_desactivadas = 0;
    for (int i = 0; i < juego.tope_bombas; i++) {
        if (juego.bombas[i].desactivada) {
            contador_bombas_desactivadas++;
        }
    }
    return contador_bombas_desactivadas;
}



/**
* pre condiciones:
* - terreno debe ser una matriz de 20x20 inicializada
* - juego debe ser una instancia valida de juego_t que contenga:
* --- las posiciones validas y no superpuestas de bombas, herramientas, y familiares
* ---  La posicion valida de Perry
* pos condiciones:
* - los elementos del juego se colocaran en las posiciones especificadas dentro del terreno, cada uno con su caracter especifico
*/
void colocar_elementos_en_terreno(juego_t juego, char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO]) {
    for (int i = 0; i < juego.tope_bombas; i++) {
        terreno[juego.bombas[i].posicion.fil][juego.bombas[i].posicion.col] = BOMBA;
    }
    for (int i = 0; i < juego.tope_herramientas; i++) {
        terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = juego.herramientas[i].tipo;
    }
    for (int i = 0; i < juego.tope_familiares; i++) {
        terreno[juego.familiares[i].posicion.fil][juego.familiares[i].posicion.col] = juego.familiares[i].inicial_nombre;
    }
    terreno[juego.perry.posicion.fil][juego.perry.posicion.col] = PERRY;

    for (int i = 0; i < juego.cantidad_robots; i++){
        terreno[juego.robots[i].fil][juego.robots[i].col] = ROBOTS;
    } 
}



/**
* pre condiciones:
* - juego debe ser una instancia valida de juego_t con datos de estado del juego inicializados y actualizados (vida, energia, estado de camuflaje y bombas activas)
* pos condiciones:
* - Se imprimiran en la consola los datos actuales del juego
*/
void imprimir_datos_del_juego(juego_t juego) {
    printf("Cantidad de vidas: %d\n", juego.perry.vida);
    printf("Cantidad de energia: %d\n", juego.perry.energia);
    printf("Camuflaje: %s\n", (juego.perry.camuflado) ? "Activado" : "Desactivado");
    printf("Bombas activas: %d\n", juego.tope_bombas - bombas_desactivadas(juego));
    printf("Robots activos: %d\n", juego.cantidad_robots);
}



void imprimir_terreno(juego_t juego) {
    char terreno[LIMITE_MAX_TERRENO][LIMITE_MAX_TERRENO];
    inicializar_terreno(terreno);
    colocar_elementos_en_terreno(juego, terreno);
    imprimir_datos_del_juego(juego);

    for (int fila = 0; fila < LIMITE_MAX_TERRENO; fila++) {
        for (int columna = 0; columna < LIMITE_MAX_TERRENO; columna++) {
            printf("%c ", terreno[fila][columna]);
        }
        printf("\n");
    }
}


/**
* pre condiciones:
* - posicion1 y posicion2 deben ser coordenadas validas
* pos condiciones:
* - devuelve la distancia de Manhattan entre las coordenadas posicion1 y posicion2
*/
int calcular_distancia_manhattan(coordenada_t posicion1, coordenada_t posicion2){
    return abs(posicion1.fil - posicion2.fil) + abs(posicion1.col - posicion2.col);
}



/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - se decrementa la vida de Perry si esta a una distancia de Manhattan <= 1 de algun familiar y no esta camuflado
*/
void alterar_vidas_segun_distancia_familiares(juego_t *juego){
    for (int i = 0; i < juego->tope_familiares;i++){
        familiar_t *familiar = &juego->familiares[i];
        int distancia = calcular_distancia_manhattan(juego->perry.posicion, familiar->posicion);
        if (distancia <= DISTANCIA_PERRY_FAMILIARES_MAXIMA && !juego->perry.camuflado){
            juego->perry.vida--;
            printf("perdiste una vida! :(");
        }
    }
}


/**
* pre condiciones:
* - juego debe ser un puntero no nulo a una estructura juego_t previamente inicializada.
* - juego->familiares debe estar inicializado con posiciones y sentidos válidos.
* pos condiciones:
* - Los familiares en el juego habrán cambiado sus posiciones según las reglas de movimiento establecidas:
*   - Candace se moverá hacia arriba o hacia abajo, cambiando de dirección al alcanzar los límites del terreno.
*   - Phineas y Ferb se moverán hacia la izquierda o hacia la derecha, cambiando de dirección al alcanzar los límites del terreno.
*/
void mover_familiares(juego_t *juego) {
    for (int i = 0; i < juego->tope_familiares; i++) {
        familiar_t *familiar = &juego->familiares[i];

        switch (familiar->inicial_nombre) {
            case CANDACE:
                if (familiar->sentido == ABAJO_MAYUS) {
                    familiar->posicion.fil++;
                    if (familiar->posicion.fil >= LIMITE_MAX_TERRENO - 1) {
                        familiar->sentido = ARRIBA_MAYUS;
                    }
                } else {
                    familiar->posicion.fil--;
                    if (familiar->posicion.fil <= 0) {
                        familiar->sentido = ABAJO_MAYUS;
                    }
                }
                break;

            case PHINEAS:
            case FERB:
                if (familiar->sentido == DERECHA_MAYUS) {
                    familiar->posicion.col++;
                    if (familiar->posicion.col >= LIMITE_MAX_TERRENO - 1) {
                        familiar->sentido = IZQUIERDA_MAYUS;
                    } 
                } else {
                    familiar->posicion.col--;
                    if (familiar->posicion.col <= 0) {
                        familiar->sentido = DERECHA_MAYUS;
                    }
                }
                break;
        }
    }
}

/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - si Perry se encuentra sobre un sombrero, se incrementa la vida de Perry y se elimina el sombrero del juego
*/
void incrementar_vida_si_perry_sobre_sombrero(juego_t *juego){
    for (int i = 0; i < juego->tope_herramientas; i++){
        herramienta_t *herramienta = &juego->herramientas[i];
        if (herramienta->tipo == SOMBRERO && herramienta->posicion.fil == juego->perry.posicion.fil && herramienta->posicion.col == juego->perry.posicion.col){
            juego->perry.vida++;
            printf("agarraste un sombrero! +1 vida !");
            for (int j = i; j < juego->tope_herramientas - 1; j++){
                juego->herramientas[j] = juego->herramientas[j+1];
            }
            juego->tope_herramientas--;
            i--;
        }
    }
}



/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - si Perry se encuentra sobre una golosina, se incrementa la energia de Perry y se elimina la golosina del juego
*/
void incrementar_energia_si_perry_sobre_golosina(juego_t *juego){
    for (int i = 0; i < juego->tope_herramientas; i++){
        herramienta_t *herramienta = &juego->herramientas[i];
        if (herramienta->tipo == GOLOSINAS && herramienta->posicion.fil == juego->perry.posicion.fil && herramienta->posicion.col == juego->perry.posicion.col){
            juego->perry.energia += ENERGIA_EXTRA;
            printf("agarraste una golosina! +20 de energia !");
            for (int j = i; j < juego->tope_herramientas - 1; j++){
                juego->herramientas[j] = juego->herramientas[j+1];
            }
            juego->tope_herramientas--;
            i--;
        }
    }
}





/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - se decrementa el temporizador de las bombas activas en el juego
* - si alguna bomba llega a cero, Perry pierde una vida
*/
void actualizar_timers_y_verificar_explosion_bombas(juego_t *juego){
    for (int i = 0; i < juego->tope_bombas; i++){
        if (!juego->bombas[i].desactivada){
            juego->bombas[i].timer--;
            if (juego->bombas[i].timer == 0){
                juego->perry.vida--;
                printf("perdiste una vida por la explosion de una bomba! :(");
                juego->bombas[i].desactivada = true;
            }
        }
    }
}




/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - si Perry se encuentra sobre una bomba y no esta camuflado, la bomba se desactiva, Perry pierde energia
* - se elimina la bomba del juego
*/
void desactivar_bomba_si_perry_encima(juego_t *juego){
    for (int i = 0; i < juego->tope_bombas; i++){
        if (!juego->bombas[i].desactivada && juego->bombas[i].posicion.fil == juego->perry.posicion.fil && juego->bombas[i].posicion.col == juego->perry.posicion.col && !juego->perry.camuflado && juego->perry.energia >= ENERGIA_QUITADA_POR_BOMBA){
            juego->bombas[i].desactivada = true;
            printf("muy bien agente P! desactivaste una bomba!");
            juego->perry.energia -=ENERGIA_QUITADA_POR_BOMBA;
            for (int j = i; j < juego->tope_bombas - 1; j++){
                juego->bombas[j] = juego->bombas[j+1];
            }
            juego->tope_bombas--;
            i--;
        }
    }
}



/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t.
* - indice debe ser un indice valido de un robot en el arreglo.
* pos condiciones:
* - El robot en la posicion dada se destruye y su memoria se libera.
* - La cantidad de robots en el juego se decrementa.
*/
void destruir_robot(juego_t* juego, int indice) {
    if (indice < 0 || indice >= juego->cantidad_robots) {
        return;
    }
    for (int i = indice; i < juego->cantidad_robots - 1; ++i) {
        juego->robots[i] = juego->robots[i + 1];
    }
    size_t new_size = (size_t)(juego->cantidad_robots - 1) * sizeof(coordenada_t);
    juego->robots = realloc(juego->robots, new_size);
    if (juego->robots == NULL && juego->cantidad_robots > 1) {
        printf("Error al liberar memoria para el arreglo de robots");
        return;
    }

    juego->cantidad_robots--;
}


/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t.
* pos condiciones:
* - Se verifican las distancias ;
*   - Si Perry esta a una distancia de Manhattan de 2 de un robot y esta camuflado, pierde una vida.
*   - Si Perry no esta camuflado, destruye al robot, pierde 5 de energia o una vida si no tiene suficiente energia.
*/
void interactuar_con_robots(juego_t* juego) {
    for (int i = 0; i < juego->cantidad_robots; i++) {
        int distancia = calcular_distancia_manhattan(juego->perry.posicion, juego->robots[i]);
        if (distancia <= DISTANCIA_PERRY_ROBOTS_MAXIMA) {
            if (juego->perry.camuflado) {
                juego->perry.vida--;
                printf("Perry perdio una vida debido a un robot estando camuflado.");
            } else {
                if (juego->perry.energia >= ENERGIA_QUITADA_POR_ROBOT){
                    juego->perry.energia -= ENERGIA_QUITADA_POR_ROBOT;
                } else {
                    juego->perry.vida--;
                    printf("Perry perdio una vida debido a un robot y falta de energia.");
                }
                destruir_robot(juego, i);
                printf("Perry destruyo un robot");
                i--;
            }
        }
    }
}



/**
* pre condiciones:
* - juego debe ser un puntero valido a una instancia de juego_t
* pos condiciones:
* - se mueven los familiares en el terreno segun su logica de movimiento
* - se verifican las interacciones de Perry con sombreros, golosinas, bombas, familiares y robots
*/
void movimiento_general(juego_t* juego){
    mover_familiares(juego);
    incrementar_vida_si_perry_sobre_sombrero(juego);
    incrementar_energia_si_perry_sobre_golosina(juego);
    actualizar_timers_y_verificar_explosion_bombas(juego);
    desactivar_bomba_si_perry_encima(juego);
    juego->movimientos++;
    alterar_vidas_segun_distancia_familiares(juego);
    interactuar_con_robots(juego);
}



void realizar_jugada(juego_t* juego, char accion){
    bool perry_se_movio = false;
    switch(accion) {
        case ARRIBA_MAYUS:
        case ARRIBA_MINUS:
        if (juego->perry.posicion.fil > 0){
            juego->perry.posicion.fil--;
            perry_se_movio = true;
            }   
            break;
            case ABAJO_MAYUS:
            case ABAJO_MINUS:
            if (juego->perry.posicion.fil < LIMITE_MAX_TERRENO - 1){
                juego->perry.posicion.fil++;
                perry_se_movio = true;
                }    
            break;
            case IZQUIERDA_MAYUS:
            case IZQUIERDA_MINUS:
            if (juego->perry.posicion.col > 0){
                juego->perry.posicion.col--;
                perry_se_movio = true;
                }
            break;
            case DERECHA_MAYUS:
            case DERECHA_MINUS:
            if (juego->perry.posicion.col < LIMITE_MAX_TERRENO - 1){
                juego->perry.posicion.col++;
                perry_se_movio = true;
                }
            break;
            case CAMUFLAJE_MAYUS:
            case CAMUFLAJE_MINUS:
                juego->perry.camuflado = !juego->perry.camuflado;
            break;
            default:
            printf("Accion no valida");
            break;
        }

    if (perry_se_movio){
        movimiento_general(juego);
        aparicion_robot(juego);
    }
}


int estado_juego(juego_t juego){
    bool todas_desactivadas = true;
    for (int i = 0; i < juego.tope_bombas; i++) {
        if (!juego.bombas[i].desactivada) {
            todas_desactivadas = false;
        }
    }
    if (todas_desactivadas && juego.perry.vida > 0) {
        free(juego.robots);
        return JUEGO_GANADO;
    } else if (juego.perry.vida <= 0) {
        free(juego.robots);
        return JUEGO_PERDIDO;
    }
    return JUEGO_ACTIVO;
}