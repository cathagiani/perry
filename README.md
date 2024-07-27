# Proyecto: Desactivación de Bombas con Perry el Ornitorrinco

# Descripcion
Este proyecto es un juego en C en el que Perry el Ornitorrinco debe desactivar bombas, recoger herramientas y enfrentarse a robots y otros personajes en un terreno. El juego tiene como objetivo desactivar todas las bombas para ganar, mientras se evita perder todas las vidas de Perry.

# Estructuras principales
Estructuras de Datos
coordenada_t: Representa una posición en el terreno.
personaje_t: Representa a Perry con sus atributos de vida, energía, estado de camuflaje y posición.
bomba_t: Representa una bomba con su posición, temporizador y estado de desactivación.
herramienta_t: Representa una herramienta con su posición y tipo.
familiar_t: Representa a un familiar con su posición, sentido de movimiento y nombre.
juego_t: Estructura principal que contiene todos los elementos del juego: Perry, bombas, herramientas, familiares, robots, y la cantidad de movimientos realizados.

# Funcionalidades
# 1. inicializacion
-   void inicializar_juego(juego_t* juego);
Inicializa el juego cargando toda la información inicial de Perry, los obstáculos, las herramientas y la familia Flynn.
# 2. Realizar jugada
-  void realizar_jugada(juego_t* juego, char accion);
Realiza la acción indicada (mover a Perry o camuflarlo) y actualiza el estado del juego.
# 3. Imprimir terreno
-  void imprimir_terreno(juego_t juego);
Imprime el estado actual del terreno de juego.
# 4. Estado del juego
-  int estado_juego(juego_t juego);
Determina si el juego está ganado, perdido o sigue activo.
# 5. Desactivar bombas
-  void desactivar_bomba_si_perry_encima(juego_t *juego);
Desactiva una bomba si Perry está sobre ella y no está camuflado.
# 6. Destruir Robot
-  void destruir_robot(juego_t* juego, int indice);
Destruye el robot en la posición dada y libera su memoria.
# 7. Interaccion con robots
-  void interactuar_con_robots(juego_t* juego);
Verifica y maneja las interacciones entre Perry y los robots, incluyendo la destrucción de robots y la pérdida de vida o energía de Perry.
# 8. Movimiento General
-  void movimiento_general(juego_t* juego);
Mueve los familiares, verifica interacciones de Perry con sombreros, golosinas, bombas, familiares y robots.

# Como ejecutar el juego
1. compilar el codigo : gcc -o juego juego.c
2. ejecutar el juego: ./juego

# Controles del juego
W o w: Mover arriba
A o a: Mover izquierda
S o s: Mover abajo
D o d: Mover derecha
Q o q: Camuflaje (activar/desactivar)

# Estado del juego
1: Juego ganado (todas las bombas desactivadas)
-1: Juego perdido (Perry se queda sin vidas)
0: Juego activo
