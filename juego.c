#include "feria.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const char ARRIBA = 'W';
const char arriba = 'w';
const char ABAJO = 'S';
const char abajo = 's';
const char IZQUIERDA = 'A';
const char izquierda = 'a';
const char DERECHA = 'D';
const char derecha = 'd';
const char CAMUFLAJE = 'Q';
const char camuflaje = 'q';

const int GANADO = 1;
const int PERDIDO = -1;
const int ACTIVO = 0;

/**
* pre condiciones:
* - juego debe ser un puntero a una instancia valida de juego_t que no haya sido inicializada o que este lista para ser reinicializada
* pos condiciones:
* - la semilla del generador de numeros aleatorios ya esta establecida
* - la estructura de juego apuntada por juego esta inicializada  con sus componentes para empezar el juego
*/
void preparar_juego(juego_t* juego) {
  srand((unsigned int)time(NULL));
  inicializar_juego(juego);      
}

/**
* pre condiciones:
* - accion es un carácter que representa una acción válida en el juego
* pos condiciones:
* - devuelve true si accion es una acción válida (una de las constantes definidas para las acciones)
* - devuelve false si accion no es una acción válida
*/
bool es_accion_valida(char accion) {
  return (accion == ARRIBA || accion == arriba || accion == ABAJO || accion == abajo || accion == IZQUIERDA || accion == izquierda || accion == DERECHA || accion == derecha || accion == CAMUFLAJE || accion == camuflaje);
}

/**
* pre condiciones:
* - juego debe ser un puntero a una instancia de juego_t previamente inicializada
* - la instancia debe representar un juego que recien empieza o que esta en curso
* pos condiciones:
* - la funcion maneja el ciclo de juego completo hasta que como gane o pierda
* - es posible la interaccion con el usuario para recibir acciones que afectan el estado del juego
* - resultado devuelve 1 si el jugador gano, -1 si perdio
* - el estado del juego refleja el resultado final del juego despues de procesar todas las jugadas del usuario hasta que el juego termina
*/
int procesar_juego(juego_t* juego) {
    int resultado;
    char accion;
    do {
      imprimir_terreno(*juego);      
      do {
        printf("Ingrese una accion (W, A, S, D, Q): ");
        scanf(" %c", &accion);

        if (!es_accion_valida(accion)) {
          printf("Acción inválida. Intente nuevamente.\n");
        }
      } while (!es_accion_valida(accion));
      
      realizar_jugada(juego, accion);
      resultado = estado_juego(*juego);
      system("clear");

    } while (resultado == ACTIVO);

    return resultado;
}



/**
* pre condiciones:
* - resultado es un entero que indica el resultado del juego, 1 es que gano y -1 que perdio
* - juego es una instancia de juego_t que representa el estado final del juego justo despues de que ha terminado
* pos condiciones:
* - el terreno final del juego es impreso para mostrar el estado al final del juego
* - se muestra un mensaje al usuario que indica si ha ganado o perdido, basado en el valor de resultado
*/
void concluir_juego(int resultado, juego_t juego) {
  if (resultado == GANADO) {
    printf("Felicidades! ganaste!\n");
  } else if (resultado == PERDIDO) {
    printf("Oh no! perdiste!\n");
  }
}



int main() {
  juego_t juego;
  preparar_juego(&juego);
  int resultado = procesar_juego(&juego);
  concluir_juego(resultado, juego);
  return 0;
}