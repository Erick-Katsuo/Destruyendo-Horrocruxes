#ifndef __HORROCRUX_H__
#define __HORROCRUX_H__

#include <stdbool.h>

#define MAX_OBJETOS 50
#define MAX_ITEMS 50
#define CANTIDAD_NIVELES 4
#define MAX_FILAS 10
#define MAX_COLUMNAS 10

typedef struct coordenadas {
	unsigned int fila;
	unsigned int columna;
} coordenadas_t;

typedef struct elemento {
	coordenadas_t posicion;
	char codigo;
} elemento_t;

typedef struct nivel {
	unsigned int numero;
	elemento_t horrocrux;
	bool horrocrux_destruido;
	bool tiene_guardian;
	bool basilisco_destruido;
	char direccion_duende; // 'd': si se mueve hacia la derecha - 'i': si se mueve hacia la izquierda.
	elemento_t guardian;
	coordenadas_t entrada;
	coordenadas_t salida;
	unsigned int filas;
	unsigned int columnas;
	elemento_t objetos[MAX_OBJETOS];
	unsigned int cantidad_objetos;
} nivel_t;

typedef struct jugador {
	coordenadas_t posicion;
	elemento_t items[MAX_ITEMS];
	unsigned int cantidad_items;
	bool envenenado;
	unsigned int turnos_envenenado;
	unsigned int turnos_restantes;
} jugador_t;

typedef struct juego {
	jugador_t jugador;
	nivel_t niveles[CANTIDAD_NIVELES];
	unsigned int nivel_actual;
	int estado;
} juego_t;

/*
 * Inicializa el estado de todo el juego, cargando todos los valores necesarios como
 * la cantidad de movimientos, el estado del juego, las coordenadas de todos los 
 * objetos, las dimensiones de los niveles, etc.
 * Precondiciones: -.
 * Postcondiciones: El juego queda en un estado válido y correcto para ser jugado.
 * Todos los elementos están dentro de los límites de su nivel.
 * El jugador se inicializa no envenenado y sin items.
 */
void inicializar_juego(juego_t *juego);

/*
 * Actualiza la matriz que representa visualmente el estado del juego en el nivel actual.
 * Precondiciones: El juego está en un estado válido.
 * Postcondiciones: Se posicionarán en la matriz aquellos elementos pertenecientes al 
 * nivel actual y el jugador, los casilleros sin elementos quedan con
 * un espacio vacío.
 */
void actualizar_escenario(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS]);

/*
 * Actualiza la posición del jugador, así como todos los valores que deban ser modificados
 * producto de moverse a la nueva posición (estado del juego, cantidad de movimientos 
 * restantes, nivel actual, etc).
 * Precondiciones: La dirección a la que de mueve es válida y está dentro de los límites 
 * del campo.
 * Postcondiciones: Se devuelve el juego actualizado y válido.
 */
void mover_jugador(juego_t *juego, char direccion);

/*
 * Dependiendo del nivel actual, se moverá el guardián del Horrocrux, si lo hay.
 * Precondiciones: El estado del juego es válido.
 * Postcondiciones: Se devuelve el juego actualizado y válido.
 */
void mover_guardian(juego_t *juego);

/*
 * Muestra por pantalla la matriz correspondiente al nivel actual.
 * Precondiciones: -.
 * Postcondiciones: -.
 */
void mostrar_escenario(char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int filas, unsigned int columnas);

/*
 * Devuelve un entero que representa el estado del juego.
 * Precondiciones: El estado del juego es válido.
 * Postcondiciones: 0 si está jugando, 1 si el jugador ganó, -1 si perdió.
 */
int estado_juego(juego_t juego);

/*
 * Devuelve una posición aleatoria.
 * Precondiciones: -.
 * Postcondiciones: Coordenada válida dentro de los límites definidos.
 */
coordenadas_t posicion_aleatoria(unsigned int filas, unsigned int columnas);

/*
 * Valida si el movimiento solicitado puede realizarse.
 * Precondiciones: -.
 * Postcondiciones: Devuelve verdadero si el jugador puede moverse en la direccion indicada en 'movimiento' y 
 * falso en caso de que no pueda moverse, ya sea porque la letra es inválida o que pretende
 * moverse fuera del campo.
 */
bool puede_moverse_jugador(char movimiento, juego_t juego);

#endif /* __HORROCRUX_H__ */