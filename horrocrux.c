#include "horrocrux.h"

#include <stdio.h>
#include <stdlib.h>

#define JUGANDO 0
#define JUGADOR_GANO 1
#define JUGADOR_PERDIO -1

#define JUGADOR 'J'
#define ANILLO 'A'
#define DIARIO 'D'
#define COPA 'C'
#define GUARDAPELOS 'L'
#define CURA 'P'
#define COLMILLOS 'F'
#define BASILISCO 'B'
#define DOLORES 'U'
#define DUENDE 'G'
#define ESPADA_GODRIC_GRYFFINDOR 'E'
#define SALIDA 'S'
#define ARRIBA 'w'
#define IZQUIERDA 'a'
#define ABAJO 's'
#define DERECHA 'd'

#define MAX_COMPROBAR 20

const unsigned int PERDIDA_TOTAL_TURNOS = 0;
const unsigned int SIN_TURNOS = 0;

const unsigned int CANTIDAD_TURNOS = 75;
const unsigned int TURNOS_ENVENENADO = 10;

const unsigned int TOPE_INICIAL_MOCHILA = 0;

const bool HORROCRUX_ESTADO_INICIAL = false;
const bool NO_EXISTE_GUARDIAN = false;
const bool EXISTE_GUARDIAN = true;

const unsigned int COLUMNA_MOCHILA = 0;
const unsigned int MOCHILA = 0;

#define ORDEN_NIVEL_UNO 0
#define NIVEL_UNO 1

#define ORDEN_NIVEL_DOS 1
#define NIVEL_DOS 2

#define ORDEN_NIVEL_TRES 2
#define NIVEL_TRES 3

#define ORDEN_NIVEL_CUATRO 3
#define NIVEL_CUATRO 4

#define MOCHILA_VACIA 0

const bool ENVENENADO = false;
// ---------------------
#define FILAS_NIVEL_UNO 5
#define COLUMNAS_NIVEL_UNO 5
const unsigned int OBJETOS_NIVEL_UNO = 3;
//-------------------------
#define FILAS_NIVEL_DOS 7
#define COLUMNAS_NIVEL_DOS 7
const bool BASILISCO_ESTADO_INICIAL = false;
const bool BASILISCO_ESTADO_DESTRUIDO = true;
#define OBJETOS_NIVEL_DOS 7

const unsigned int RANGO_COLUMNAS_HORROCRUX_NIVEL_DOS = 3;
const unsigned int FILA_DESIGNADA_HORROCRUX_NIVEL_DOS = 3;

const unsigned int FILA_INICIAL_BASILISCO = 3;
const unsigned int COLUMNA_INICIAL_BASILISCO = 5;

const unsigned int RANGO_FILA_GUARDIAN_BASILISCO = 3;
const unsigned int RANGO_COLUMNA_GUARDIAN_BASILISCO = 5;

const unsigned int BORDE_DERECHO_BASILISCO = 5;
const unsigned int BORDE_INFERIOR_BASILISCO = 4;
const unsigned int BORDE_IZQUIERDO_BASILISCO = 1;
const unsigned int BORDE_SUPERIOR_BASILISCO = 2;
// -------------------------
#define FILAS_NIVEL_TRES 5
#define COLUMNAS_NIVEL_TRES 5

#define DIRECCION_DUENDE_DERECHA 'd'
#define DIRECCION_DUENDE_IZQUIERDA 'i'
const unsigned int COLMILLOS_NECESARIOS_DESTRUIR_COPA = 2;

const unsigned int TURNOS_PERDIDOS_DUENDE = 7;

const unsigned int BORDE_DERECHO_DUENDE = 4;
const unsigned int BORDE_IZQUIERDO_DUENDE = 0;

const unsigned int OBJETOS_NIVEL_TRES = 0;

const unsigned int FILA_INICIAL_DUENDE = 2;
const unsigned int COLUMNA_INICIAL_DUENDE = 2;

const unsigned int FILA_RECORRIDO_DUENDE = 2;
//------------------------
#define FILAS_NIVEL_CUATRO 7
#define COLUMNAS_NIVEL_CUATRO 7

#define OBJETOS_NIVEL_CUATRO 0

const unsigned int TURNOS_PERDIDOS_DOLORES = 10;

const unsigned int FILA_RANGO_ACEPTABLE_HORROCRUX_NIVEL_CUATRO =6; 
const unsigned int COLUMNA_RANGO_ACEPTABLE_HORROCRUX_NIVEL_CUATRO =6;

const unsigned int RANGO_FILA_GUARDIAN_DOLORES = 3;
const unsigned int RANGO_COLUMNA_GUARDIAN_DOLORES = 3;

const unsigned int DISTANCIA_DOLORES_HORROCRUX = 1;
//--------------------
const unsigned int FILA_INICIAL_UNO = 4;
const unsigned int COLUMNA_INICIAL_UNO = 2;

const unsigned int FILA_INICIAL_DOS = 6;
const unsigned int COLUMNA_INICIAL_DOS = 3;

const unsigned int FILA_INICIAL_TRES = 4; 
const unsigned int COLUMNA_INICIAL_TRES = 2;

const unsigned int FILA_INICIAL_CUATRO = 6; 
const unsigned int COLUMNA_INICIAL_CUATRO = 3;

const unsigned int FILA_SALIDA_UNO = 0;
const unsigned int COLUMNA_SALIDA_UNO = 2;

const unsigned int FILA_SALIDA_DOS = 0; 
const unsigned int COLUMNA_SALIDA_DOS = 3;

const unsigned int FILA_SALIDA_TRES = 0;
const unsigned int COLUMNA_SALIDA_TRES = 2;

const unsigned int FILA_SALIDA_CUATRO = 0; 
const unsigned int COLUMNA_SALIDA_CUATRO = 3; 

typedef struct coordenadas_int {
	int fila;
	int columna;
} coordenadas_int_t;

typedef struct borde {
	unsigned int derecho_dolores;
	unsigned int inferior_dolores;
	unsigned int izquierdo_dolores;
	unsigned int superior_dolores;
} borde_t;




int estado_juego(juego_t juego){
	return juego.estado;
}

/*
 * La coordeanada columna del guardian cambia en el lado derecho del recorrido manteniendo la fila, teniendo en cuenta el sentido horario.
 * Precondiciones: Los valores del struct "borde" deben estar bien definidos.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada fila del mismo en el borde del recorrido superior.
 */
void mover_dolores_lado_superior(juego_t *juego, coordenadas_t posicion_dolores, borde_t borde){
	if(posicion_dolores.columna>=borde.izquierdo_dolores && posicion_dolores.columna<borde.derecho_dolores){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna)++;
	}
}

/*
 * La coordeanada fila del guardian cambia en el lado derecho del recorrido manteniendo la columna, teniendo en cuenta el sentido horario.
 * Precondiciones: Los valores del struct "borde" deben estar bien definidos.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada columna del mismo en el borde del recorrido izquierdo.
 */
void mover_dolores_lado_izquierdo(juego_t *juego, coordenadas_t posicion_dolores, borde_t borde){
	if((posicion_dolores.fila<=borde.inferior_dolores) && (posicion_dolores.fila>borde.superior_dolores)){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila)--;
	}
}

/*
 * La coordeanada columna del guardian cambia en el lado derecho del recorrido manteniendo la fila, teniendo en cuenta el sentido horario.
 * Precondiciones: Los valores del struct "borde" deben estar bien definidos.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada fila del mismo en el borde del recorrido inferior.
 */
void mover_dolores_lado_inferior(juego_t *juego, coordenadas_t posicion_dolores, borde_t borde){
	if((posicion_dolores.columna>borde.izquierdo_dolores )&& (posicion_dolores.columna<=borde.derecho_dolores )){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna)--;
	}
}


/*
 * La coordeanada fila del guardian cambia en el lado derecho del recorrido manteniendo la columna, teniendo en cuenta el sentido horario.
 * Precondiciones: Los valores del struct "borde" deben estar bien definidos.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada columna del mismo en el borde del recorrido derecho.
 */
void mover_dolores_lado_derecho(juego_t *juego, coordenadas_t posicion_dolores, borde_t borde){
	if((posicion_dolores.fila>=borde.superior_dolores) && (posicion_dolores.fila<borde.inferior_dolores)){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila)++;
	}
}

/*
 * Asigna las condiciones en los que se movera determinado "borde" dependiendo de la posicion actual del guardian del nivel, las 
 * condiciones son tales que el guardian se movera en sentido horario.
 * Precondiciones:-.
 * Postcondiciones: Quedan definidos los elementos siendo estos los bordes del recorrido del guardian "Dolores Umbridge".
 */
void mover_bordes_dolores_umbridge(juego_t *juego, coordenadas_t posicion_dolores, borde_t borde){
	if((posicion_dolores.columna == borde.derecho_dolores) && (posicion_dolores.fila != borde.inferior_dolores)){
		mover_dolores_lado_derecho(juego, posicion_dolores, borde);
	}else if((posicion_dolores.fila == borde.inferior_dolores) && (posicion_dolores.columna != borde.izquierdo_dolores)){
		mover_dolores_lado_inferior(juego, posicion_dolores, borde);
	}else if((posicion_dolores.columna == borde.izquierdo_dolores) && (posicion_dolores.fila != borde.superior_dolores)){
		mover_dolores_lado_izquierdo(juego, posicion_dolores, borde);
	}else if((posicion_dolores.fila == borde.superior_dolores) && (posicion_dolores.columna != borde.derecho_dolores)){
		mover_dolores_lado_superior(juego, posicion_dolores, borde);
	}
}

/*
 * Asigna los valores correspondientes al struct "borde".
 * Precondiciones:-.
 * Postcondiciones: Quedan definidos los elementos siendo estos los bordes del recorrido del guardian "Dolores Umbridge".
 */
void asignar_bordes_recorrido_dolores(borde_t *borde, coordenadas_t posicion_horrocrux){
	(borde->derecho_dolores) = posicion_horrocrux.columna+DISTANCIA_DOLORES_HORROCRUX;
	(borde->inferior_dolores) = posicion_horrocrux.fila+DISTANCIA_DOLORES_HORROCRUX;
	(borde->izquierdo_dolores) = posicion_horrocrux.columna-DISTANCIA_DOLORES_HORROCRUX;
	(borde->superior_dolores) = posicion_horrocrux.fila-DISTANCIA_DOLORES_HORROCRUX;
}

/*
 * Asigna valores a los elementos para poder comenzar a mover al guardian "Dolores Umbridge".
 * Precondiciones:-.
 * Postcondiciones: Quedan definidos los elementos necesarios para comenzar a mover al guardian.
 */
void mover_dolores_umbridge(juego_t *juego){
	coordenadas_t posicion_dolores=(juego->niveles[(juego->nivel_actual)-1].guardian.posicion);
	coordenadas_t posicion_horrocrux=(juego->niveles[juego->nivel_actual-1].horrocrux.posicion);
	borde_t borde;
	asignar_bordes_recorrido_dolores(&borde,posicion_horrocrux);
	mover_bordes_dolores_umbridge(juego, posicion_dolores, borde);	
}

/*
 * Dependiendo del valor de la variable "columna_duende" la direccion del guardian cambia.
 * Precondiciones:-.
 * Postcondiciones: La direccion del guardian cambia de derecha a izquierda dependiendo a que borde del escenario llegue el mismo.
 */
void cambiar_movimiento_duende(juego_t *juego){
	unsigned int columna_duende=(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna);
	if(columna_duende==BORDE_IZQUIERDO_DUENDE){
		juego->niveles[ORDEN_NIVEL_TRES].direccion_duende=DIRECCION_DUENDE_DERECHA;
	}else if(columna_duende==BORDE_DERECHO_DUENDE){
		juego->niveles[ORDEN_NIVEL_TRES].direccion_duende=DIRECCION_DUENDE_IZQUIERDA;
	}
}
/*
 * Se resta o suma la posicion de la columna actual del guardian dependiendo de su direccion actual.
 * Precondiciones:-.
 * Postcondiciones: El valor de la coordenada columna del guardian varia restando o sumando 1(uno) dependiendo de su direccion.
 */
void mover_columna_duende(juego_t *juego){
	if(juego->niveles[ORDEN_NIVEL_TRES].direccion_duende==DIRECCION_DUENDE_IZQUIERDA){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna)--;
	}else if(juego->niveles[ORDEN_NIVEL_TRES].direccion_duende==DIRECCION_DUENDE_DERECHA){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna)++;
	}
}

/*
 * Se mueve al guardian "Duende" dentro del rango designado en el enunciado.
 * Precondiciones:-.
 * Postcondiciones: El guardian se mueve de derecha a izquierda en la fila asignada "FILA_INICIAL_DUENDE".
 */
void mover_duende(juego_t *juego){
	mover_columna_duende(juego );
	cambiar_movimiento_duende(juego );
}

/*
 * La coordeanada columna del guardian cambia en el lado derecho del recorrido manteniendo la fila, teniendo en cuenta el sentido horario.
 * Precondiciones:-.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada fila del mismo en el borde del recorrido superior.
 */
void mover_basilisco_lado_superior(juego_t *juego, coordenadas_t posicion_basilisco){
	if(posicion_basilisco.columna>=BORDE_IZQUIERDO_BASILISCO && posicion_basilisco.columna<BORDE_DERECHO_BASILISCO){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna)++;
	}
}

/*
 * La coordeanada fila del guardian cambia en el lado derecho del recorrido manteniendo la columna, teniendo en cuenta el sentido horario.
 * Precondiciones:-.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada columna del mismo en el borde del recorrido izquierdo.
 */
void mover_basilisco_lado_izquierdo(juego_t *juego, coordenadas_t posicion_basilisco){
	if((posicion_basilisco.fila<=BORDE_INFERIOR_BASILISCO) && (posicion_basilisco.fila>BORDE_SUPERIOR_BASILISCO)){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila)--;
	}
}

/*
 * La coordeanada columna del guardian cambia en el lado derecho del recorrido manteniendo la fila, teniendo en cuenta el sentido horario.
 * Precondiciones:-.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada fila del mismo en el borde del recorrido inferior.
 */
void mover_basilisco_lado_inferior(juego_t *juego, coordenadas_t posicion_basilisco){
	if((posicion_basilisco.columna>BORDE_IZQUIERDO_BASILISCO )&& (posicion_basilisco.columna<=BORDE_DERECHO_BASILISCO )){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna)--;
	}
}


/*
 * La coordeanada fila del guardian cambia en el lado derecho del recorrido manteniendo la columna, teniendo en cuenta el sentido horario.
 * Precondiciones:-.
 * Postcondiciones: El guardian se mueve menteniendo el valor de la coordenada columna del mismo en el borde del recorrido derecho.
 */
void mover_basilisco_lado_derecho(juego_t *juego, coordenadas_t posicion_basilisco){
	if((posicion_basilisco.fila>=BORDE_SUPERIOR_BASILISCO) && (posicion_basilisco.fila<BORDE_INFERIOR_BASILISCO)){
		(juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila)++;
	}
}

/*
 * Se mueve al guardian "Basilisco" dentro del rango designado en el enunciado.
 * Precondiciones:-.
 * Postcondiciones: El guardian se mueve de forma horaria en los bordes de su rango.
 */
void mover_basilisco(juego_t *juego){
	coordenadas_t posicion_basilisco=(juego->niveles[(juego->nivel_actual)-1].guardian.posicion);
	if((posicion_basilisco.columna == BORDE_DERECHO_BASILISCO) && (posicion_basilisco.fila!= BORDE_INFERIOR_BASILISCO)){
		mover_basilisco_lado_derecho(juego, posicion_basilisco);
	}else if((posicion_basilisco.fila== BORDE_INFERIOR_BASILISCO) && (posicion_basilisco.columna!= BORDE_IZQUIERDO_BASILISCO)){
		mover_basilisco_lado_inferior(juego, posicion_basilisco);
	}else if((posicion_basilisco.columna== BORDE_IZQUIERDO_BASILISCO) && (posicion_basilisco.fila!= BORDE_SUPERIOR_BASILISCO)){
		mover_basilisco_lado_izquierdo(juego, posicion_basilisco);
	}else if((posicion_basilisco.fila== BORDE_SUPERIOR_BASILISCO) && (posicion_basilisco.columna != BORDE_DERECHO_BASILISCO)){
		mover_basilisco_lado_superior(juego, posicion_basilisco);
	}
}

/*
 * Actualiza el estado del juego a "gano" dependiendo su cumple con las condiciones necesarias.
 * Precondiciones:-.
 * Postcondiciones: En caso de que se cumplan las condiciones para ganar, el puntero "actualizar_estado" se igualara con "gano", y en caso
 * 					contrario el puntero "actualizar_estado" se mantiene sin modificar.
 */
void estado_juego_gano(juego_t *juego,coordenadas_t jugador, coordenadas_t salida_final){
	if((jugador.fila == salida_final.fila)&&(jugador.columna == salida_final.columna)){
		if((juego->nivel_actual==NIVEL_CUATRO) && (juego->niveles[juego->nivel_actual-1].horrocrux_destruido==true)){
			juego->estado=JUGADOR_GANO;
		}
	}
}

/*
 * Actualiza el estado del juego a "perdio" dependiendo su cumple con las condiciones necesarias.
 * Precondiciones:-.
 * Postcondiciones: En caso de que se cumplan las condiciones para perder, el puntero "actualizar_estado" se igualara con "perdio", y en caso
 * 					contrario el puntero "actualizar_estado" se mantiene sin modificar.
 */
void estado_juego_perdio(juego_t *juego){
	if((juego->jugador.turnos_restantes == SIN_TURNOS) || (juego->jugador.turnos_envenenado == SIN_TURNOS)){
		juego->estado=JUGADOR_PERDIO;
	}
}


/*
 * Evalua el estado del juego en sus correspondientes funciones.
 * Precondiciones:-.
 * Postcondiciones: El estado del juego terminara modificado segun las condiciones que cumpla
 */
void evaluar_estado_juego(juego_t *juego){
	coordenadas_t salida_final=juego->niveles[ORDEN_NIVEL_CUATRO].salida;
	coordenadas_t jugador=juego->jugador.posicion;
	estado_juego_perdio(juego);
	estado_juego_gano(juego,jugador,salida_final);
}


/*
 * Resta a los turnos correspondientes la cantidad de turnos que se pierden por encontrarse con el guardian "Dolores Umbridge".
 * Precondiciones: -.
 * Postcondiciones: Si las coordeandas coinciden entonces el "Jugador" perdera 10(diez) turnos(incluso los turnos envenenados si es que lo esta)
 *					y en caso de que el jugador tenga menos de 10(diez) turnos entonces perdera todos los turnos restantes que le quedan. 
 * 					En alguna de esas situaciones, dependiendo de las condiciones, el estado del "Jugador" se actualizara.
 */
void restar_turnos_encuentro_dolores(juego_t *juego){
	if((juego->jugador.turnos_restantes)>=TURNOS_PERDIDOS_DOLORES){
		(juego->jugador.turnos_restantes)=((juego->jugador.turnos_restantes) - TURNOS_PERDIDOS_DOLORES);
	}else if ((juego->jugador.turnos_restantes)<TURNOS_PERDIDOS_DOLORES){
		(juego->jugador.turnos_restantes)=PERDIDA_TOTAL_TURNOS;
	}
	if((juego->jugador.envenenado==true) && ((juego->jugador.turnos_envenenado)<TURNOS_PERDIDOS_DOLORES)){
		(juego->jugador.turnos_envenenado)=PERDIDA_TOTAL_TURNOS;
	}else if((juego->jugador.envenenado==true) && ((juego->jugador.turnos_envenenado)>=TURNOS_PERDIDOS_DOLORES)){
		(juego->jugador.turnos_envenenado)=((juego->jugador.turnos_envenenado) - TURNOS_PERDIDOS_DOLORES);
	}
}

/*
 * Verifica si las coordenadas del "Jugador" y el guardian "Dolores Umbridge" coinciden luego de sus respectivos movimientos en el mismo turno.
 * Precondiciones: El estado del juego es válido.
 * Postcondiciones: Se informa el encuentro con el guardian y la cantidad de puntos restados por consola.
 */
void verificar_encuentro_dolores(juego_t *juego){
	unsigned int fila_jugador=juego->jugador.posicion.fila;
	unsigned int columna_jugador=juego->jugador.posicion.columna;
	unsigned int fila_guardian=juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila;
	unsigned int columna_guardian=juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna;
	if((fila_guardian==fila_jugador)&&(columna_guardian==columna_jugador) && (juego->nivel_actual==NIVEL_CUATRO)){
		restar_turnos_encuentro_dolores(juego);
		printf("Chocaste a Dolores\nSe restaron 10 turnos! :(\nY de paso un correctivo(?)\n");
	}
}

/*
 * Resta a los turnos correspondientes la cantidad de turnos que se pierden por encontrarse con el guardian "Duende".
 * Precondiciones: -.
 * Postcondiciones: Si las coordeandas coinciden entonces el "Jugador" perdera 7(siete) turnos(incluso los turnos envenenados si es que lo esta)
 *					y en caso de que el jugador tenga menos de 7(siete) turnos entonces perdera todos los turnos restantes que le quedan.
  * 				En alguna de esas situaciones, dependiendo de las condiciones, el estado del "Jugador" se actualizara.
 */
void restar_turnos_encuentro_duende(juego_t *juego){
	if((juego->jugador.turnos_restantes)>TURNOS_PERDIDOS_DUENDE){
		(juego->jugador.turnos_restantes)=((juego->jugador.turnos_restantes) - TURNOS_PERDIDOS_DUENDE);
	}else if ((juego->jugador.turnos_restantes)<=TURNOS_PERDIDOS_DUENDE){
		(juego->jugador.turnos_restantes)=PERDIDA_TOTAL_TURNOS;
	}
	if((juego->jugador.envenenado==true) && ((juego->jugador.turnos_envenenado)<=TURNOS_PERDIDOS_DUENDE)){
		(juego->jugador.turnos_envenenado)=PERDIDA_TOTAL_TURNOS;
	}else if((juego->jugador.envenenado==true) && ((juego->jugador.turnos_envenenado)>TURNOS_PERDIDOS_DUENDE)){
		(juego->jugador.turnos_envenenado)=((juego->jugador.turnos_envenenado) - TURNOS_PERDIDOS_DUENDE);
	}
}

/*
 * Verifica si las coordenadas del "Jugador" y el guardian "Duende" coinciden luego de sus respectivos movimientos en el mismo turno.
 * Precondiciones: El estado del juego es válido.
 * Postcondiciones: Se informa el encuentro con el guardian y la cantidad de puntos restados por consola.
 */
void verificar_encuentro_duende(juego_t *juego){
	unsigned int fila_jugador=juego->jugador.posicion.fila;
	unsigned int columna_jugador=juego->jugador.posicion.columna;
	unsigned int fila_guardian=juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila;
	unsigned int columna_guardian=juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna;
	if((fila_guardian==fila_jugador)&&(columna_guardian==columna_jugador) && (juego->nivel_actual==NIVEL_TRES)){
		restar_turnos_encuentro_duende(juego);
		printf("Encuentro con el Duende\nSe restaron 7 turnos! :(\n");
	}
}


/*
 * Verifica si las coordenadas del "Jugador" y el guardian "Basilisco" coinciden luego de sus respectivos movimientos en el mismo turno, incluyendo
 * la busqueda del item "ESPADA_GODRIC_GRYFFINDOR_JUEGO" para eliminar al guardian.
 * Precondiciones:El estado del juego es válido.
 * Postcondiciones: Si las coordeandas coinciden entonces el "Jugador" perdera todos sus turnos asi como el juego, y en el caso de que
 * se encuentre el item "ESPADA_GODRIC_GRYFFINDOR_JUEGO" entonces el guardian sera eliminado del nivel.
 */
void verificar_encuentro_basilisco(juego_t *juego){
	unsigned int fila_jugador=juego->jugador.posicion.fila;
	unsigned int columna_jugador=juego->jugador.posicion.columna;
	unsigned int fila_guardian=juego->niveles[(juego->nivel_actual)-1].guardian.posicion.fila;
	unsigned int columna_guardian=juego->niveles[(juego->nivel_actual)-1].guardian.posicion.columna;
	if((fila_guardian==fila_jugador)&&(columna_guardian==columna_jugador) && (juego->nivel_actual==NIVEL_DOS)){
		if(juego->niveles[(juego->nivel_actual)-1].guardian.codigo==BASILISCO){
			for(int i=0; i<(juego->jugador.cantidad_items);i++){
				if(juego->jugador.items[i].codigo==ESPADA_GODRIC_GRYFFINDOR){	
					(juego->niveles[(juego->nivel_actual)-1].tiene_guardian)=false;
					juego->niveles[(juego->nivel_actual)-1].basilisco_destruido=BASILISCO_ESTADO_DESTRUIDO;
					(juego->niveles[(juego->nivel_actual)-1].guardian.codigo)=' ';
					return;
				}
			}
			juego->estado= JUGADOR_PERDIO;
		}
	}
}

/*
 * Verifica el encuentro de los guardianes "Basilisco" y "Duende" en sus respectivos niveles.
 * Precondiciones: -.
 * Postcondiciones: Informa si se encuentran el "Jugador" y el guardian correspondiente al nivel actual.
 */
void verificar_encuentro_guardian(juego_t *juego){
	verificar_encuentro_basilisco(juego);
	verificar_encuentro_duende(juego);
	verificar_encuentro_dolores(juego);
}



void mover_guardian(juego_t *juego){
	if((juego->nivel_actual==NIVEL_DOS) && (juego->niveles[(juego->nivel_actual)-1].tiene_guardian==true)){
		mover_basilisco(juego);
	}else if(juego->nivel_actual==NIVEL_TRES){
		mover_duende(juego);
	}else if(juego->nivel_actual==NIVEL_CUATRO){
		mover_dolores_umbridge(juego);
	}
	verificar_encuentro_guardian(juego);
	evaluar_estado_juego(juego);
}

/*
 * Se elimina el item de su lugar correspondiente acomodando los demas en el mismo orden excluyendo el item eliminado.
 * Precondiciones:El orden del item debe ser el correcto.
 * Postcondiciones: Se elimina el item de su posicion y se reduce la cantidad de items de la mochila.
 */
void eliminar_items(juego_t *juego, unsigned int orden_item){
	for(unsigned int i=orden_item;i<((juego->jugador.cantidad_items)-1);i++){
		juego->jugador.items[i].codigo=juego->jugador.items[i+1].codigo;
	}
	(juego->jugador.cantidad_items)--;
}

/*
 * Busca en los items del "Jugador" el item "Colmillos" para el nivel cuatro.
 * Precondiciones:-.
 * Postcondiciones: Si encuentra el item "Colmillos" devuelve "true", en caso contrario devuelve "false".
 */
void buscar_colmillos_nivel_cuatro(juego_t *juego, bool *encontro){
	for(unsigned int i=0; i<(juego->jugador.cantidad_items);i++){
		if(juego->jugador.items[i].codigo==COLMILLOS){
			eliminar_items(juego, i);
			*encontro=true;
			i=(juego->jugador.cantidad_items);
		}
	}
}
/*
 * Busca en los items del "Jugador" el item "Colmillos" para el nivel tres.
 * Precondiciones:-.
 * Postcondiciones: Si encuentra el item "Colmillos" devuelve "true", en caso contrario devuelve "false".
 */
void buscar_colmillos_nivel_tres(juego_t *juego, bool *encontro){
	for(unsigned int i=0; i<(juego->jugador.cantidad_items);i++){
		if(juego->jugador.items[i].codigo==COLMILLOS){
			eliminar_items(juego, i);
			*encontro=true;
			i=(juego->jugador.cantidad_items);
		}
	}
}

/*
 * Busca en los items del "Jugador" el item "Colmillos" para el nivel dos.
 * Precondiciones:-.
 * Postcondiciones: Si encuentra el item "Colmillos" devuelve "true", en caso contrario devuelve "false".
 */
void buscar_colmillos_nivel_dos(juego_t *juego, bool *encontro){
	for(unsigned int i=0; i<(juego->jugador.cantidad_items);i++){
		if(juego->jugador.items[i].codigo==COLMILLOS){
			eliminar_items(juego, i);
			*encontro=true;
			i=(juego->jugador.cantidad_items);
		}
	}
}

/*
 * Busca en los items del "Jugador" el item "Colmillos" necesarios para el nivel tres.
 * Precondiciones:-.
 * Postcondiciones: Si no encuentra la cantidad de items requeridos o si no encuentra ninguno, entonces devuelve "false" en el puntero "encontro".
 * 					En caso contrario devuelve "true" en el puntero "encontro".
 */
void buscar_colmillos_basilisco_nivel_tres(juego_t *juego, bool *encontro){
	for(unsigned int i=0;i<COLMILLOS_NECESARIOS_DESTRUIR_COPA;i++){
		buscar_colmillos_nivel_tres(juego, encontro);
		if(encontro==false){
			i=COLMILLOS_NECESARIOS_DESTRUIR_COPA;
		}
	}
}

/*
 * Busca en los items del "Jugador" el item "Colmillos".
 * Precondiciones:-.
 * Postcondiciones: Si encuentra el item "Colmillos" devuelve "true", en caso contrario devuelve "false".
 */
bool buscar_colmillos_basilisco(juego_t *juego){
	bool encontro=false;
	if(juego->nivel_actual == NIVEL_DOS){
		buscar_colmillos_nivel_dos(juego, &encontro);
	}else if(juego->nivel_actual == NIVEL_TRES){
		buscar_colmillos_basilisco_nivel_tres(juego, &encontro);
	}else if(juego->nivel_actual == NIVEL_CUATRO){
		buscar_colmillos_nivel_cuatro(juego, &encontro);
	}
	return encontro;
}

/*
 * Busca el item definido como "ESPADA_GODRIC_GRYFFINDOR_JUEGO" (E).
 * Precondiciones:-.
 * Postcondiciones: En caso de que encuentre dicho item entonces se devuelve "true" a travez del puntero "puede_destruir_copa".
 */
void buscar_espada_godric(juego_t *juego, bool *puede_destruir_copa){
	for(unsigned int i=0; i<(juego->jugador.cantidad_items);i++){
		if(juego->jugador.items[i].codigo==ESPADA_GODRIC_GRYFFINDOR){
			*puede_destruir_copa=true;
			i=(juego->jugador.cantidad_items);
		}
	}
}



/*
 * En caso de estar envenenado se busca el item "Cura".
 * Precondiciones:-.
 * Postcondiciones: Si encuentra el item "Cura" el estado envenenado se actualiza a "false".
 *					Imprime por pantalla si se usa el item "Cura", en caso contrario se imprime una "alerta".	
 */
void usar_cura(juego_t *juego){
	for(unsigned int i=0; i<(juego->jugador.cantidad_items);i++){
		if(juego->jugador.items[i].codigo==CURA){
			juego->jugador.envenenado=false;
			printf("Se uso una Cura para salvarte del veneno mortal!\n");
			eliminar_items(juego, i);
			juego->jugador.turnos_envenenado=TURNOS_ENVENENADO;
			return;
		}
	}
	printf("\nEstas envenenado!\nConsigue una Cura pronto!\n");
}

/*
 * Se verifica si el "Horrocrux" del nivel uno es destruido, segun las condiciones correspondientes.
 * Precondiciones:-.
 * Postcondiciones: En caso de que sea destruido entonces imprime por pantalla informando cual se destruyo. En caso contrario informa que condiciones
 *					Son necesarias.
 */
void verificar_destruccion_guardapelo(juego_t *juego, coordenadas_t posicion_jugador, coordenadas_t posicion_horrocrux){
	bool puede_destruir_copa = false;
	if((posicion_jugador.fila == posicion_horrocrux.fila)&&(posicion_jugador.columna == posicion_horrocrux.columna)){
		buscar_espada_godric(juego, &puede_destruir_copa);
		if(puede_destruir_copa==false){
			puede_destruir_copa = buscar_colmillos_basilisco(juego);
		}
		if(puede_destruir_copa==true){
			juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido=true;
			printf("\nDestruiste el Horrocrux: Guardapelo!\n");
			return;
		}
		printf("Necesitas la Espada de Godric Gryffindor (E) o 1(uno) Colmillos de Basiliscos (F)\n para destruir el Horrocrux!\n");
	}
}

/*
 * Se verifica si el "Horrocrux" del nivel uno es destruido, segun las condiciones correspondientes.
 * Precondiciones:-.
 * Postcondiciones: En caso de que sea destruido entonces imprime por pantalla informando cual se destruyo. En caso contrario informa que condiciones
 *					Son necesarias.
 */
void verificar_destruccion_copa(juego_t *juego, coordenadas_t posicion_jugador, coordenadas_t posicion_horrocrux){
	bool puede_destruir_copa = false;
	if((posicion_jugador.fila == posicion_horrocrux.fila)&&(posicion_jugador.columna == posicion_horrocrux.columna)){
		buscar_espada_godric(juego, &puede_destruir_copa);
		if(puede_destruir_copa==false){
			puede_destruir_copa = buscar_colmillos_basilisco(juego);
		}
		if(puede_destruir_copa==true){
			juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido=true;
			printf("\nDestruiste el Horrocrux: Copa!\n");
			return;
		}
		printf("Necesitas la Espada de Godric Gryffindor (E) o 2(dos) Colmillos de Basiliscos (F)\n para destruir el Horrocrux!\n");
	}
}

/*
 * Se verifica si el "Horrocrux" del nivel uno es destruido, segun las condiciones correspondientes.
 * Precondiciones:-.
 * Postcondiciones: En caso de que sea destruido entonces imprime por pantalla informando cual se destruyo. En caso contrario informa que condiciones
 *					Son necesarias.
 */
void verificar_destruccion_diario(juego_t *juego, coordenadas_t posicion_jugador, coordenadas_t posicion_horrocrux){
	bool buscar = false;
	if((posicion_jugador.fila==posicion_horrocrux.fila)&&(posicion_jugador.columna==posicion_horrocrux.columna)){
		buscar = buscar_colmillos_basilisco(juego);
		if(buscar==true){
			juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido=true;
			printf("\nDestruiste el Horrocrux: Diario!\n");
			return;
		}
		printf("Necesitas un Colmillo de Basilisco (F) para destruir el Horrocrux!\n");
	}
}

/*
 * Se verifica si el "Horrocrux" del nivel uno es destruido, segun las condiciones correspondientes.
 * Precondiciones:-.
 * Postcondiciones: En caso de que sea destruido entonces imprime por pantalla informando cual se destruyo. En caso contrario informa que condiciones
 *					Son necesarias.
 */
void verificar_destruccion_anillo(juego_t *juego, coordenadas_t posicion_jugador, coordenadas_t posicion_horrocrux){
	if((posicion_jugador.fila==posicion_horrocrux.fila)&&(posicion_jugador.columna==posicion_horrocrux.columna)){
		juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido=true;
		printf("\nDestruiste el Horrocrux: Anillo!\n");
	}
}

/*
 * Dependiendo del nivel se verifica si el "Horrocrux" del mismo es destruido, segun las condiciones correspondientes.
 * Precondiciones:-.
 * Postcondiciones: Es verficado la destruccion del "Horrocrux" del nivel, en caso de ser destruido se cambia el estado del mismo.
 */
void verificar_destruccion_horrocrux(juego_t *juego){
	coordenadas_t posicion_jugador = juego->jugador.posicion;
	coordenadas_t posicion_horrocrux = juego->niveles[(juego->nivel_actual)-1].horrocrux.posicion;
	if((juego->nivel_actual==NIVEL_UNO) &&(juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==false)){
		verificar_destruccion_anillo(juego,posicion_jugador,posicion_horrocrux);
	}else if((juego->nivel_actual==NIVEL_DOS) && (juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==false)){
		verificar_destruccion_diario(juego,posicion_jugador,posicion_horrocrux);
	}else if((juego->nivel_actual==NIVEL_TRES) && (juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==false)){
		verificar_destruccion_copa(juego,posicion_jugador,posicion_horrocrux);
	}else if((juego->nivel_actual==NIVEL_CUATRO) && (juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==false)){
		verificar_destruccion_guardapelo(juego,posicion_jugador,posicion_horrocrux);
	}
}

void destruir_horrocrux(juego_t *juego){
	if(juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==true){
		juego->niveles[(juego->nivel_actual)-1].horrocrux.codigo=' ';
	}
}

/*
 * Verifica si el jugador esta envenenado, tanto por destruir un "Horrocrux" o por que uso una "Cura" para dejar de estarlo.
 * Precondiciones: La posicion del "Horrocrux" debe estar definida asi como el estado inicial envenenado del jugador en cada nivel .
 * Postcondiciones: El jugador queda envenenado si no posee una "Cura", en caso de poseer una "Cura" automaticamente se usa para dejar de estar
 *					envenenado. Para ambos casos se imprime por pantalla avisando el estado del jugador.
 */
void verificar_envenenado(juego_t *juego){
	verificar_destruccion_horrocrux(juego);
	if((juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==true) && (juego->niveles[(juego->nivel_actual)-1].horrocrux.codigo== ANILLO)){
		juego->jugador.envenenado=true;
	}else if((juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==true) && (juego->niveles[(juego->nivel_actual)-1].horrocrux.codigo==DIARIO)){
		juego->jugador.envenenado=true;
	}else if((juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==true) && (juego->niveles[(juego->nivel_actual)-1].horrocrux.codigo==COPA)){
		juego->jugador.envenenado=true;
	}else if((juego->niveles[(juego->nivel_actual)-1].horrocrux_destruido==true) && (juego->niveles[(juego->nivel_actual)-1].horrocrux.codigo==GUARDAPELOS)){
		juego->jugador.envenenado=true;
	}
	destruir_horrocrux(juego);
	if(juego->jugador.envenenado==true){
		usar_cura(juego);		
	}
}



/*
 * Busca el objeto a eliminar y luego reordena tanto los codigos como las posiciones de los objetos restantes movimiendolos
 * de posicion un lugar a la izquierda desde la posicion del objeto que se eliminara.
 * Precondiciones: El objeto a eliminar no se mueve, solo el resto.
 * Postcondiciones: elimina el objeto de su vector correspondiente, reordena los objetos restantes manteniendo el orden que tenian previamente.
 */
void eliminar_objetos(juego_t *juego, unsigned int orden_item){
	for(unsigned int i=orden_item;i<((juego->niveles[juego->nivel_actual-1].cantidad_objetos)-1);i++){
		juego->niveles[juego->nivel_actual-1].objetos[i].codigo=juego->niveles[juego->nivel_actual-1].objetos[i+1].codigo;
		juego->niveles[juego->nivel_actual-1].objetos[i].posicion=juego->niveles[juego->nivel_actual-1].objetos[i+1].posicion;
	}
	juego->niveles[juego->nivel_actual-1].cantidad_objetos--;
}


/*
 * Resta los turnos correspondientes por cada movimiento aceptado para el "Jugador", y tambien en caso de estar envenenado.
 * Precondiciones:-.
 * Postcondiciones: Se resta 1(uno) por cada movimiento del "Jugador".
 */
void restar_turnos(juego_t *juego){
	if(juego->estado==JUGANDO){
		juego->jugador.turnos_restantes--;
		if(juego->jugador.envenenado==true){
			juego->jugador.turnos_envenenado--;
		}
	}
}

/*
 * En caso de que el jugador se posicione sobre un objeto del escenario en el nivel corresponidente entonces el objeto se guardara
 * como item del jugador para poder ser usado en todo el juego segun sus caracteristicas.
 * Precondiciones: Los objetos deben estar posicionados en cada nivel de forma valida.
 * Postcondiciones: elimina el objeto del escenario, y lo guarda como item.
 */
void guardar_objeto(juego_t *juego){
	elemento_t sacar;
	unsigned int tope_objetos=juego->niveles[(juego->nivel_actual-1)].cantidad_objetos;
	for(unsigned int i=0;i<tope_objetos;i++){
		if((juego->jugador.posicion.fila ==  juego->niveles[(juego->nivel_actual-1)].objetos[i].posicion.fila)&&(juego->jugador.posicion.columna ==  juego->niveles[(juego->nivel_actual-1)].objetos[i].posicion.columna) ){
			sacar=juego->niveles[juego->nivel_actual-1].objetos[i];
			eliminar_objetos(juego, i);
			juego->jugador.items[(juego->jugador.cantidad_items)]=sacar;
			juego->jugador.cantidad_items++;
			printf("Objeto guardado\n");
		}
	}
}

/*
 * Sube de nivel en caso de que las condiciones para tal caso del correspondiente nivel sean las correctas.
 * Precondiciones: Las condiciones de cada nivel deben estar correctas y la posicion del jugador debe ser igual a la posicion de 
 * 				   la "Salida" del nivel correspondiente.
 * Postcondiciones: El nivel actual del juego aumenta en 1(uno).
 */
void subir_nivel(juego_t *juego){
	coordenadas_t posicion_jugador=(juego->jugador.posicion);
	coordenadas_t posicion_salida=(juego->niveles[(juego->nivel_actual-1)].salida);
	if((posicion_jugador.fila == posicion_salida.fila)&&(posicion_jugador.columna == posicion_salida.columna)){
		if(juego->niveles[juego->nivel_actual-1].horrocrux_destruido==true){
			if(juego->nivel_actual!=NIVEL_CUATRO){
				juego->nivel_actual=(juego->niveles[(juego->nivel_actual-1)].numero)+1;
				juego->jugador.posicion=juego->niveles[juego->nivel_actual-1].entrada;
			}else{
				juego->estado=JUGADOR_GANO;
			}
		}
	}
	
}

/*
 * Realiza acciones del juego luego de que el jugador se mueve informando por consola los cambios de las mencionadas.
 * Precondiciones: -.
 * Postcondiciones: Dependiendo de su funcion se realizaran varias acciones definidas en su respectivo desarrollo.
 */
void acciones_del_juego(juego_t *juego){
	guardar_objeto(juego);
	restar_turnos(juego);
	verificar_encuentro_guardian(juego);
	verificar_envenenado(juego);
	subir_nivel(juego);
	evaluar_estado_juego(juego);
}

void mover_jugador(juego_t *juego, char direccion){
	juego->estado=JUGANDO;
	if(direccion==IZQUIERDA){
		juego->jugador.posicion.columna=((juego->jugador.posicion.columna)-1);
	}else if(direccion==DERECHA){
		juego->jugador.posicion.columna=((juego->jugador.posicion.columna)+1);
	}else if(direccion==ARRIBA){
		juego->jugador.posicion.fila=((juego->jugador.posicion.fila)-1);
	}else if(direccion==ABAJO){
		juego->jugador.posicion.fila=((juego->jugador.posicion.fila)+1);
	}
	printf("Estado actual:\n\n");
	acciones_del_juego(juego);
}

/*
 * Verifica que el movimiento ingresado no posicion al "Jugador" fuera del escenario del respectivo nivel.
 * Precondiciones:-.
 * Postcondiciones: Devuelve "false" en caso de que el movimiento no sea aceptado, "true" en caso contrario.
 */
bool verificar_campo(coordenadas_int_t movimiento_campo,juego_t juego){
	int fila_movida;
	int columna_movida;
	fila_movida=((movimiento_campo.fila)+(int)(juego.jugador.posicion.fila));
	columna_movida=((movimiento_campo.columna)+(int)(juego.jugador.posicion.columna));
	if((fila_movida>((juego.niveles[juego.nivel_actual-1].filas)-1)) ||(fila_movida<0)){
		return false;
	}else if((columna_movida>((juego.niveles[juego.nivel_actual-1].columnas)-1)) ||(columna_movida<0)){
		return false;
	}
	return true;
}

bool puede_moverse_jugador(char movimiento, juego_t juego){
	bool fuera_del_campo;

		if(movimiento==IZQUIERDA){
			coordenadas_int_t movimiento_campo={0,-1};
			fuera_del_campo=verificar_campo(movimiento_campo,juego);
		}else if(movimiento==DERECHA){
			coordenadas_int_t movimiento_campo={0,1};
			fuera_del_campo=verificar_campo(movimiento_campo,juego);				
		}else if(movimiento==ARRIBA){
			coordenadas_int_t movimiento_campo={-1,0};
			fuera_del_campo=verificar_campo(movimiento_campo,juego);				
		}else if(movimiento==ABAJO){
			coordenadas_int_t movimiento_campo={1,0};
			fuera_del_campo=verificar_campo(movimiento_campo,juego);
		}
	return fuera_del_campo;
}

/*
 * Inserta bordes superiores tanto inferiores al escenario, solo con fines esteticos, dependiendo de la cantidad de columnas del mismo.
 * Precondiciones: La cantidad de columnas de cada nivel debe estar definida correctamente.
 * Postcondiciones: Se imprime por pantalla los bordes para cada escenario en el nivel correspondiente.
 */
void asignar_bordes_inferiores_superiores(char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int columnas){
	for(int k=0;k<columnas;k++){
		printf(" ———");
	}
	printf("\n");
}

void mostrar_escenario(char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int filas, unsigned int columnas){
	for(int i =0; i<filas;i++){
		asignar_bordes_inferiores_superiores(escenario, columnas);
		for (int j=0;j<columnas;j++){
			printf("| %c ", escenario[i][j]);
		}
		printf("|\n");
	}
	asignar_bordes_inferiores_superiores(escenario, columnas);
}

/*
 * Actualiza la matriz que representa visualmente el estado del juego en el nivel cuatro.
 * Precondiciones: El juego está en un estado válido.
 * Postcondiciones: Se posicionarán en la matriz aquellos elementos pertenecientes al 
 * nivel dos y el jugador, los casilleros sin elementos quedan con
 * un espacio vacío.
 */
void actualizar_escenario_cuatro(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int filas, unsigned int columnas, coordenadas_t posicion_horrocrux){
	for(int i=0;i <filas; i++){
		for(int j=0; j<columnas;j ++){
			if((i==juego.jugador.posicion.fila) && (j==juego.jugador.posicion.columna)){
				escenario[i][j]=JUGADOR;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].salida.fila) && ( j == juego.niveles[(juego.nivel_actual)-1].salida.columna )){
				escenario[i][j]=SALIDA;
			}else if((i == posicion_horrocrux.fila) && (j==posicion_horrocrux.columna) && (juego.niveles[(juego.nivel_actual)-1].horrocrux_destruido==false)){
				escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].horrocrux.codigo;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].guardian.posicion.fila)&&(j == juego.niveles[(juego.nivel_actual)-1].guardian.posicion.columna)){
				escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].guardian.codigo;
			}
		}
	}	
}

/*
 * Actualiza la matriz que representa visualmente el estado del juego en el nivel tres.
 * Precondiciones: El juego está en un estado válido.
 * Postcondiciones: Se posicionarán en la matriz aquellos elementos pertenecientes al 
 * nivel dos y el jugador, los casilleros sin elementos quedan con
 * un espacio vacío.
 */
void actualizar_escenario_tres(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int filas, unsigned int columnas, coordenadas_t posicion_horrocrux){
	for(int i=0;i <filas; i++){
		for(int j=0; j<columnas;j ++){
			if((i==juego.jugador.posicion.fila) && (j==juego.jugador.posicion.columna)){
				escenario[i][j]=JUGADOR;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].salida.fila) && ( j == juego.niveles[(juego.nivel_actual)-1].salida.columna )){
				escenario[i][j]=SALIDA;
			}else if((i == posicion_horrocrux.fila) && (j==posicion_horrocrux.columna) && (juego.niveles[(juego.nivel_actual)-1].horrocrux_destruido==false)){
				escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].horrocrux.codigo;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].guardian.posicion.fila)&&(j == juego.niveles[(juego.nivel_actual)-1].guardian.posicion.columna)){
				escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].guardian.codigo;
			}
		}
	}	
}

/*
 * Actualiza la matriz que representa visualmente el estado del juego en el nivel dos.
 * Precondiciones: El juego está en un estado válido.
 * Postcondiciones: Se posicionarán en la matriz aquellos elementos pertenecientes al 
 * nivel dos y el jugador, los casilleros sin elementos quedan con
 * un espacio vacío.
 */
void actualizar_escenario_dos(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int tope_objetos, unsigned int filas, unsigned int columnas, coordenadas_t posicion_horrocrux){
	for(int i=0;i <filas; i++){
		for(int j=0; j<columnas;j ++){
			if((i==juego.jugador.posicion.fila) && (j==juego.jugador.posicion.columna)){
				escenario[i][j]=JUGADOR;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].salida.fila) && ( j == juego.niveles[(juego.nivel_actual)-1].salida.columna )){
				escenario[i][j]=SALIDA;
			}else if((i == posicion_horrocrux.fila) && (j==posicion_horrocrux.columna) && (juego.niveles[(juego.nivel_actual)-1].horrocrux_destruido==false)){
				escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].horrocrux.codigo;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].guardian.posicion.fila)&&(j == juego.niveles[(juego.nivel_actual)-1].guardian.posicion.columna)){
				if((juego.niveles[(juego.nivel_actual)-1].tiene_guardian==true)&&(juego.niveles[(juego.nivel_actual)-1].basilisco_destruido==false)){
					escenario[i][j]=(juego.niveles[(juego.nivel_actual)-1].guardian.codigo);
				}
			}else{
				for(int k=0;k<tope_objetos;k++){
					if((i==juego.niveles[(juego.nivel_actual)-1].objetos[k].posicion.fila)& (j==juego.niveles[(juego.nivel_actual)-1].objetos[k].posicion.columna) ){
						escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].objetos[k].codigo;
					}
				}
			}
		}
	}	
}

/*
 * Actualiza la matriz que representa visualmente el estado del juego en el nivel uno.
 * Precondiciones: El juego está en un estado válido.
 * Postcondiciones: Se posicionarán en la matriz aquellos elementos pertenecientes al 
 * nivel uno y el jugador, los casilleros sin elementos quedan con
 * un espacio vacío.
 */
void actualizar_escenario_uno(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS], unsigned int tope_objetos, unsigned int filas, unsigned int columnas, coordenadas_t posicion_horrocrux){
	for(int i=0;i <filas; i++){
		for(int j=0; j<columnas;j ++){
			if((i==juego.jugador.posicion.fila) && (j==juego.jugador.posicion.columna)){
				escenario[i][j]=JUGADOR;
			}else if((i == juego.niveles[(juego.nivel_actual)-1].salida.fila) && ( j == juego.niveles[(juego.nivel_actual)-1].salida.columna )){
				escenario[i][j]=SALIDA;
			}else if((i == posicion_horrocrux.fila) && (j==posicion_horrocrux.columna) && (juego.niveles[(juego.nivel_actual)-1].horrocrux_destruido==false)){
				escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].horrocrux.codigo;
			}else{
				for(int k=0;k<tope_objetos;k++){
					if((i==juego.niveles[(juego.nivel_actual)-1].objetos[k].posicion.fila)& (j==juego.niveles[(juego.nivel_actual)-1].objetos[k].posicion.columna) ){
						escenario[i][j]=juego.niveles[(juego.nivel_actual)-1].objetos[k].codigo;
					}
				}
			}
		}
	}	
}

/*
 * Vacia completamente el escenario dejandolo listo para ser actualizado dependiendo del nivel.
 * Precondiciones:-.
 * Postcondiciones: El escenario queda vacio.
 */
void vaciar_escenario(char escenario[MAX_FILAS][MAX_COLUMNAS]){
	for (int i=0; i<MAX_FILAS;i++){
		for(int j=0; j<MAX_COLUMNAS; j++){
			escenario[i][j]=' ';
		}
	}
}

void actualizar_escenario(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS]){
	unsigned int filas=juego.niveles[juego.nivel_actual-1].filas;
	unsigned int columnas=juego.niveles[juego.nivel_actual-1].columnas;
	unsigned int tope_objetos=juego.niveles[juego.nivel_actual-1].cantidad_objetos;
	coordenadas_t posicion_horrocrux=juego.niveles[juego.nivel_actual-1].horrocrux.posicion;
	vaciar_escenario(escenario);
	if(juego.nivel_actual==NIVEL_UNO){
		actualizar_escenario_uno(juego, escenario, tope_objetos,filas,columnas,posicion_horrocrux);
	}else if(juego.nivel_actual==NIVEL_DOS){
		actualizar_escenario_dos(juego, escenario, tope_objetos,filas,columnas,posicion_horrocrux);
	}else if(juego.nivel_actual==NIVEL_TRES){
		actualizar_escenario_tres(juego, escenario, filas, columnas, posicion_horrocrux);
	}else if(juego.nivel_actual==NIVEL_CUATRO){
		actualizar_escenario_cuatro(juego, escenario, filas, columnas, posicion_horrocrux);
	}
}
/*
 * Asigna los codigos a los elementos del juego en el nivel cuatro.
 * Precondiciones: El juego debe estar correctamente inicializado.
 * Postcondiciones: Quedan asignados los codigos correspondientes en el nivel identificado.
 */
void asignar_codigos_nivel_cuatro(juego_t *juego, int identificador_nivel){
	juego->niveles[identificador_nivel].horrocrux.codigo=GUARDAPELOS;
	juego->niveles[identificador_nivel].guardian.codigo=DOLORES;
}
/*
 * Asigna los codigos a los elementos del juego en el nivel tres.
 * Precondiciones: El juego debe estar correctamente inicializado.
 * Postcondiciones: Quedan asignados los codigos correspondientes en el nivel identificado.
 */
void asignar_codigos_nivel_tres(juego_t *juego, int identificador_nivel){
	juego->niveles[identificador_nivel].horrocrux.codigo=COPA;
	juego->niveles[identificador_nivel].guardian.codigo=DUENDE;
}
/*
 * Asigna los codigos a los elementos del juego en el nivel dos.
 * Precondiciones: El juego debe estar correctamente inicializado.
 * Postcondiciones: Quedan asignados los codigos correspondientes en el nivel identificado.
 */
void asignar_codigos_nivel_dos(juego_t *juego, int identificador_nivel, unsigned int tope_objeto){
	juego->niveles[identificador_nivel].horrocrux.codigo=DIARIO;
	juego->niveles[identificador_nivel].guardian.codigo=BASILISCO;
	for(int i=0;i<tope_objeto;i++){
		juego->niveles[identificador_nivel].objetos[i].codigo=COLMILLOS;
		if(i==(tope_objeto-1)){
			juego->niveles[identificador_nivel].objetos[i].codigo=ESPADA_GODRIC_GRYFFINDOR;
		}
	}
}

/*
 * Asigna los codigos a los elementos del juego en el nivel uno.
 * Precondiciones: El juego debe estar correctamente inicializado.
 * Postcondiciones: Quedan asignados los codigos correspondientes en el nivel identificado.
 */
void asignar_codigos_nivel_uno(juego_t *juego, int identificador_nivel, unsigned int tope_objeto){
	if(juego->niveles[identificador_nivel].horrocrux_destruido==false){
			juego->niveles[identificador_nivel].horrocrux.codigo=ANILLO;
		}
		for(int i=0;i<tope_objeto;i++){
			juego->niveles[identificador_nivel].objetos[i].codigo=CURA;
	}
}

/*
 * Asigna los codigos a los elementos del juego dependiendo del nivel identificado.
 * Precondiciones: El juego debe estar correctamente inicializado.
 * Postcondiciones: Se asignaran los codigos dependiendo del nive.
 */
void asignar_codigos(juego_t *juego, int identificador_nivel){
	unsigned int tope_objeto;
	tope_objeto = (juego->niveles[identificador_nivel].cantidad_objetos);
	if(identificador_nivel==ORDEN_NIVEL_UNO){
		asignar_codigos_nivel_uno(juego, identificador_nivel, tope_objeto);
	}else if(identificador_nivel==ORDEN_NIVEL_DOS){
		asignar_codigos_nivel_dos(juego, identificador_nivel, tope_objeto);
	}else if(identificador_nivel==ORDEN_NIVEL_TRES){
		asignar_codigos_nivel_tres(juego, identificador_nivel);
	}else{
		asignar_codigos_nivel_cuatro(juego, identificador_nivel);
	}
}

/*
 * Verifica que la coordenada a comprobar no coincida con el resto dentro del vector "comprobar".
 * Precondiciones: La funcion "verificar_distinto_inicio_salida_nive" tiene que haber devuelto "true" previamente.
 * Postcondiciones: En caso una de que coincida con alguna de las coordenadas devuelve "false". En caso contrario
 * 					devuelve "true" siendo aceptada como coordenada valida junto a las anteriores.
 */
bool verificar_coordenada_repetida(coordenadas_t comprobar[], int orden){
	bool no_paso = false;
	bool paso = true;
	if(orden>0){
		int verificar = orden;
		for(int j=0; j<orden;j++){
			if((comprobar[j].fila==comprobar[verificar].fila) && (comprobar[j].columna==comprobar[verificar].columna) && (j!=verificar)){
				paso=no_paso;
			}
		}
	}
	return paso;
}

/*
 * Verifica que la coordenada ingresada no coincida con las coordenadas de inicio y salida del nivel correspondiente.
 * Precondiciones: -.
 * Postcondiciones: En caso de que coincida con el inicio y salida del nivel correspondiente devuelve "false". En caso contrario
 * 					devuelve "true".
 */
bool verificar_distinto_inicio_salida_nivel(coordenadas_t comprobar[],int orden ,juego_t *juego ,int identificador_nivel ){
	bool no_paso=false;
	bool paso=true;
	unsigned int fila_inicial = juego->niveles[identificador_nivel].entrada.fila;
	unsigned int columna_inicial = juego->niveles[identificador_nivel].entrada.columna;
	unsigned int fila_salida = juego->niveles[identificador_nivel].salida.fila;
	unsigned int columna_salida = juego->niveles[identificador_nivel].salida.columna;
	if((comprobar[orden].fila == fila_inicial) && (comprobar[orden].columna == columna_inicial)){
		paso=no_paso;
	}else if((comprobar[orden].fila==fila_salida) && (comprobar[orden].columna==columna_salida)){
		paso=no_paso;
	}
	return paso;
}

/*
 * Devuelve "true" en caso de que sean comprobadas las coordenadas 
 * al cumplir ser distintas al inicio y salida del nivel, asi como entre si mismas.
 * En caso contrario devuelve "false".
 * Precondiciones: El array "comprobar" debe poseer las coordenadas a comprobar
 * el "orden" debe ser igual a la cantidad de coordenadas a comprobarse.
 * Postcondiciones: Se comprueban las coordenadas aceptandolas como aptas para implementarse en el nivel identificado.
 */
bool comprobar_coordenadas(coordenadas_t comprobar[],int orden ,juego_t *juego ,int identificador_nivel ){
	bool paso=true;
	paso = verificar_distinto_inicio_salida_nivel(comprobar ,orden ,juego , identificador_nivel);
	if(paso==true){
		paso = verificar_coordenada_repetida(comprobar, orden);
	}	
	return paso;
}

coordenadas_t posicion_aleatoria (unsigned int filas, unsigned int columnas){
	unsigned int i, j;
	i = (unsigned int)rand() % filas;
	j = (unsigned int)rand() % columnas;
	coordenadas_t random = {i, j};
	return random;
}

/*
 * Se verifca que la coordeanada del horrocrux del nivel cuatro este dentro del rango definido y verificado para el nivel cuatro.
 * Precondiciones: -.
 * Postcondiciones: En caso de que las coordenadas coincidan con alguna coordenada del rango aceptado entonces el puntero "verificar" 
 *					sera igualado al elemento "paso"[de valor 0(cero)].
 * 					Los puntoros "i" y "j" se valoraran de tal forma para que la iteracin de la funcion, que llama a esta, termine.
 */
void verificar_coordeanada_horrocrux_nivel_cuatro(coordenadas_t comprobar[], int orden, unsigned int mover_fila, unsigned int *i, unsigned int *j, unsigned int *verificar){
	unsigned int paso=0;
	if((comprobar[orden].fila==mover_fila) && (comprobar[orden].columna==(*j))){
		(*verificar)=paso;
		(*i) = FILA_RANGO_ACEPTABLE_HORROCRUX_NIVEL_CUATRO-1;
		(*j) = COLUMNA_RANGO_ACEPTABLE_HORROCRUX_NIVEL_CUATRO-1;
	}
}

/*
 * En caso de que la coordenada no sea valida entonces se movera la fila para cumplir con los requisitos del nivel cuatro.
 * Precondiciones:-.
 * Postcondiciones: La fila se sube [resta 1(uno)] o baja [suma 1(uno)] si es que las coordeanadas no son validas, en caso contrario
 *	      			no se altera la coordenada fila.
 */
void mover_fila_invalida(unsigned int j, unsigned int *mover_fila){
	if(*mover_fila==1){
		if(j==2 || j==3 || j==4){
			(*mover_fila)=(*mover_fila)+1;
		}
	}else if(*mover_fila==5){
		if(j==2 || j==3 || j==4){
			(*mover_fila)=(*mover_fila)-1;
		}
	}
}

/*
 * Verifica que las coordenadas del "Horrocrux" del nivel cuatro sean asignadas tales que el guardian "Dolores" cumpla con las condiciones
 * del nivel (poder girar entorno a la coordeanda asignada del "Horrocrux" sin chocar con la "Entrada" y "Salida" correspondiente al nivel)
 * Precondiciones:-.
 * Postcondiciones: Devuelve "0" si las coordenadas del "Horrocrux" entran en el rango aceptable, y devuelve "1" en caso contrario.
 */
int rango_aceptable_horrocrux_para_guardian(coordenadas_t comprobar[], int orden){
	unsigned int verificar=1;
	unsigned int mover_fila;
	for(unsigned int i=1;i<FILA_RANGO_ACEPTABLE_HORROCRUX_NIVEL_CUATRO;i++){
		for(unsigned int j=1;j<COLUMNA_RANGO_ACEPTABLE_HORROCRUX_NIVEL_CUATRO;j++){
			mover_fila=i;
			mover_fila_invalida(j, &mover_fila);
			verificar_coordeanada_horrocrux_nivel_cuatro(comprobar, orden, mover_fila, &i, &j, &verificar);
		}
	}
	return (int)verificar;
}

/*
 * Verifica que las coordenadas del "Horrocrux" del nivel tres no coincidan con el recorrido del guardian "Duende".
 * Precondiciones:-.
 * Postcondiciones: Devuelve "1" si las coordenadas del "Horrocrux" coincide con el recorrido del guardian, y devuelve "0" en caso contrario.
 */
int distinto_recorrido_duende(coordenadas_t comprobar[], int orden){
	unsigned int fila_duende = FILA_RECORRIDO_DUENDE;
	int no_paso=0;
	if(comprobar[orden].fila == fila_duende) {
		no_paso=1;
	}
	return no_paso;
}


/*
 * Verifica que las coordenadas de los objetos esten fuera del recorrido del guardian "Basilisco" y dentro de las posibles coordenadas
 * del "Horrocrux" correspondiente al nivel dos.
 * Precondiciones:-.
 * Postcondiciones: Devuelve "1" si las coordenadas de los objetos entran en el rango no aceptado, y devuelve "0" en caso contrario.
 */
int distinto_recorrido_basilisco(coordenadas_t comprobar[], int orden_comprobar){
	int no_paso=0;
	unsigned int fila_recorrido_basilisco=RANGO_FILA_GUARDIAN_BASILISCO;
	unsigned int columna_recorrido_basilisco=RANGO_COLUMNA_GUARDIAN_BASILISCO;
	for(unsigned int i=0; i<fila_recorrido_basilisco;i++){
		for(unsigned int j=0;j<columna_recorrido_basilisco;j++){
			coordenadas_t recorrido_guardian={(i+2),(j+1)};
			if((recorrido_guardian.fila == comprobar[orden_comprobar].fila) && (recorrido_guardian.columna == comprobar[orden_comprobar].columna)){
				no_paso=1;
				i=fila_recorrido_basilisco-1;				
				j=columna_recorrido_basilisco-1;
			}
		}
	}
	return no_paso;
}

/*
 * Asigna las coordenadas al guardian del nivel cuatro.
 * Precondiciones: El "identificador_nivel" debe ser asignado previamente.
 * Postcondiciones: Quedan asignadas las coordenadas para el guardian en su estado inicial.
 */
void dar_coordenada_guardian_nivel_cuatro(juego_t *juego, int identificador_nivel){
	unsigned int filas_guardian = RANGO_FILA_GUARDIAN_DOLORES;
	unsigned int columnas_guardian = RANGO_COLUMNA_GUARDIAN_DOLORES;
	juego->niveles[identificador_nivel].guardian.posicion=posicion_aleatoria(filas_guardian, columnas_guardian);
	juego->niveles[identificador_nivel].guardian.posicion.fila=(juego->niveles[identificador_nivel].guardian.posicion.fila)+(juego->niveles[identificador_nivel].horrocrux.posicion.fila)-1;
	juego->niveles[identificador_nivel].guardian.posicion.columna=(juego->niveles[identificador_nivel].guardian.posicion.columna)+(juego->niveles[identificador_nivel].horrocrux.posicion.columna)-1;
	coordenadas_t horrocrux_cuatro = juego->niveles[identificador_nivel].horrocrux.posicion;
	coordenadas_t guardian_cuatro = juego->niveles[identificador_nivel].guardian.posicion;
	if((guardian_cuatro.fila==horrocrux_cuatro.fila) && (guardian_cuatro.columna==horrocrux_cuatro.columna)){
		dar_coordenada_guardian_nivel_cuatro(juego,identificador_nivel);
	}
}

/*
 * Asigna las coordenadas al guardian del nivel tres.
 * Precondiciones: El "identificador_nivel" debe ser asignado previamente.
 * Postcondiciones: Quedan asignadas las coordenadas para el guardian en su estado inicial.
 */
void dar_coordenada_guardian_nivel_tres(juego_t *juego, int identificador_nivel){
	juego->niveles[identificador_nivel].guardian.posicion.fila = FILA_INICIAL_DUENDE;
	juego->niveles[identificador_nivel].guardian.posicion.columna = COLUMNA_INICIAL_DUENDE;
}

/*
 * Asigna las coordenadas al guardian del nivel dos.
 * Precondiciones: El "identificador_nivel" debe ser asignado previamente.
 * Postcondiciones: Quedan asignadas las coordenadas para el guardian en su estado inicial.
 */
void dar_coordenada_guardian_nivel_dos(juego_t *juego, int identificador_nivel){
	juego->niveles[identificador_nivel].guardian.posicion.fila = FILA_INICIAL_BASILISCO;
	juego->niveles[identificador_nivel].guardian.posicion.columna = COLUMNA_INICIAL_BASILISCO;
}

/*
 * Asigna las coordenadas al guardian del nivel correspondiente.
 * Precondiciones: El "identificador_nivel" debe ser asignado previamente.
 * Postcondiciones: Quedan asignadas las coordenadas para el guardian en su estado inicial.
 */
void dar_coordenada_inicial_guardian(juego_t *juego, int identificador_nivel){
	if(identificador_nivel == ORDEN_NIVEL_DOS){
		dar_coordenada_guardian_nivel_dos(juego, identificador_nivel);
	}else if(identificador_nivel == ORDEN_NIVEL_TRES){
		dar_coordenada_guardian_nivel_tres(juego, identificador_nivel);
	}else if(identificador_nivel == ORDEN_NIVEL_CUATRO){
		dar_coordenada_guardian_nivel_cuatro(juego, identificador_nivel);
	}
}



/*
 * Asigna una coordenada aleatoria para los objetos, correspondientes al nivel uno y dos.
 * Precondiciones: "orden_objeto" debe estar bien definido. [tener en cuenta que el orden 0(cero) corresponde al Horrocrux]
 * Postcondiciones: Quedan asignados las coordenadas para los objetos cumpliento los criterios de cada nivel.
 */
void dar_coordenada_aleatoria_objeto(coordenadas_t comprobar[], int orden_objeto, unsigned int filas, unsigned int columnas, int identificador_nivel){
	if(identificador_nivel==ORDEN_NIVEL_UNO || identificador_nivel==ORDEN_NIVEL_DOS){	
		comprobar[orden_objeto]=posicion_aleatoria(filas, columnas);
	}
}

/*
 * Asigna las coordenadas a los objetos del nivel verificando que no coincida con el inicio y salida del mismo asi como las del horrocrux
 * y de su respectivo guardian dependiendo del nivel.
 * Precondiciones: El valor del "orden" debe ser dinstinto de cero.
 * Postcondiciones: Quedan asignados las coordenadas para los objetos cumpliento los criterios de cada nivel.
 */
coordenadas_t dar_coordenada_objeto(coordenadas_t comprobar[], unsigned int filas, unsigned int columnas, int orden ,juego_t *juego ,int identificador_nivel){
	bool paso = false;
	int orden_objeto=orden+1;
	int limitar_bool=1;
	while(paso==false){
		dar_coordenada_aleatoria_objeto(comprobar ,orden_objeto, filas ,columnas ,identificador_nivel);
		paso= comprobar_coordenadas(comprobar ,orden_objeto , juego, identificador_nivel);
		if(identificador_nivel==ORDEN_NIVEL_DOS){
			limitar_bool=distinto_recorrido_basilisco(comprobar,orden_objeto);
			if(limitar_bool==1){
				paso=false;
			}
		}
	}
	return comprobar[orden_objeto];
}

/*
 * Verifica que la coordeanda del horrocrux sea aceptable respecto a las condiciones dadas con el guardian y el escenario del nivel.
 * Precondiciones: -.
 * Postcondiciones: En caso de que no sean aceptadas las coordeandas, el puntero "paso" se iguala a "false". En caso contrario el puntero "paso"
 *                  queda sin modificarse. (quedando en valor "true")
 */
void coordenada_aceptable_horrocrux_respecto_guardian(coordenadas_t comprobar[] ,int identificador_nivel, int orden, int limitar_bool, bool *paso){
	if(identificador_nivel == ORDEN_NIVEL_TRES){
		limitar_bool=distinto_recorrido_duende(comprobar ,orden);
		if(limitar_bool==1){
			*paso=false;
		}
	}else if(identificador_nivel==ORDEN_NIVEL_CUATRO){
		limitar_bool=rango_aceptable_horrocrux_para_guardian(comprobar,orden);
		if(limitar_bool==1){
			*paso=false;
		}
	}	
}



/*
 * Proporciona una coordenada aleatoria dentro del rango del escenario de su respectivo nivel.
 * En caso del nivel dos, la coordenada aleatoria se da en un rango definido más pequeño.
 * Precondiciones: orden e identificador de nivel deben estar bien asignados.
 * Postcondiciones: Dentro del vector "comprobar" queda asignado una posicion aleatoria para el respectivo nivel.
 */
void dar_coordenada_aleatoria_horrocrux(coordenadas_t comprobar[] ,unsigned int filas ,unsigned int columnas ,int identificador_nivel, int orden){
	if((identificador_nivel==ORDEN_NIVEL_UNO) || (identificador_nivel == ORDEN_NIVEL_TRES) || (identificador_nivel== ORDEN_NIVEL_CUATRO)){
		comprobar[orden]=posicion_aleatoria(filas, columnas);	
	}else if(identificador_nivel==ORDEN_NIVEL_DOS){
		columnas = RANGO_COLUMNAS_HORROCRUX_NIVEL_DOS;
		comprobar[orden]=posicion_aleatoria(filas,columnas);
		comprobar[orden].fila= FILA_DESIGNADA_HORROCRUX_NIVEL_DOS;
		comprobar[orden].columna=comprobar[orden].columna+2;
	}
}

/*
 * Asigna las coordenadas al horrocrux del nivel verificando que no coincida con el inicio y salida del mismo, asi tambien como los
 * requisitos de posicion respecto al guardian del nivel.
 * Precondiciones:-.
 * Postcondiciones: Queda asignada la coordenada para horrocrux.
 */
coordenadas_t dar_coordenada_horrocrux(coordenadas_t comprobar[] ,unsigned int filas ,unsigned int columnas ,juego_t *juego ,int identificador_nivel ){
	bool paso= false;
	int orden=0;
	int limitar_bool=1;
	while(paso==false){	
		dar_coordenada_aleatoria_horrocrux(comprobar ,filas ,columnas ,identificador_nivel ,orden);
		paso=comprobar_coordenadas(comprobar ,orden , juego, identificador_nivel);
		coordenada_aceptable_horrocrux_respecto_guardian(comprobar ,identificador_nivel, orden, limitar_bool, &paso);
	}
	return comprobar[orden];
}

/*
 * Asigna las coordenadas a los objetos dependiendo del nivel identificado.
 * Precondiciones: -.
 * Postcondiciones: Quedan asignadas las coordenadas del objeto sin repetirse y distintos al inicio y salida, incluyendo
 				 	al Horrocrux, cumpliendo las condiciones del nivel correspondiente.
 */
void asignar_coordenadas_objetos(juego_t *juego, unsigned int tope_objeto, coordenadas_t comprobar[], unsigned int filas, unsigned int columnas, int identificador_nivel ){
	for(int i=0; i<(tope_objeto);i++){
		juego->niveles[identificador_nivel].objetos[i].posicion = dar_coordenada_objeto(comprobar,filas,columnas, i,juego,identificador_nivel);
	}
}

/*
 * Asigna las coordenadas dependiendo del nivel identificado.
 * Precondiciones: Los elementos "mandar_filas" y "mandar_columnas" tienen que estar definidos correspondientes al nivel, incluido el identificador.
 * Postcondiciones: Quedan asignadas las coordenadas sin repetirse y distintos al inicio y salida del nivel correspondiente.
 */
void asignar_coordenadas ( juego_t *juego, unsigned int *mandar_filas, unsigned int *mandar_columnas, int identificador_nivel){
	unsigned int filas=*mandar_filas;
	unsigned int columnas=*mandar_columnas;
	coordenadas_t comprobar[MAX_COMPROBAR];
	unsigned int tope_objeto;
	juego->niveles[identificador_nivel].horrocrux.posicion = dar_coordenada_horrocrux(comprobar ,filas ,columnas ,juego ,identificador_nivel );
	dar_coordenada_inicial_guardian(juego,identificador_nivel);
	tope_objeto = (juego->niveles[identificador_nivel].cantidad_objetos);
	asignar_coordenadas_objetos(juego ,tope_objeto ,comprobar ,filas ,columnas ,identificador_nivel );
} 

/*
 * Asigna el valor a los elementos "filas" y "columnas" dependiendo del nivel identificado.
 * Precondiciones: Cada funcion que actualice un nivel debe tener un identificador con valor asignado.
 * Postcondiciones: Los elementos "filas" y "columnas" quedan asignados correspondiente al nivel y su identificador.
 */
void dar_limites(unsigned int *mandar_filas ,unsigned int *mandar_columnas ,int identificador_nivel ){
	if(identificador_nivel == ORDEN_NIVEL_UNO){
		*mandar_filas=FILAS_NIVEL_UNO;
		*mandar_columnas=COLUMNAS_NIVEL_UNO;
	}else if(identificador_nivel == ORDEN_NIVEL_DOS){
		*mandar_filas=FILAS_NIVEL_DOS;
		*mandar_columnas=COLUMNAS_NIVEL_DOS;
	}else if(identificador_nivel == ORDEN_NIVEL_TRES){
		*mandar_filas=FILAS_NIVEL_TRES;
		*mandar_columnas=COLUMNAS_NIVEL_TRES;
	}else{
		*mandar_filas=FILAS_NIVEL_CUATRO;
		*mandar_columnas=COLUMNAS_NIVEL_CUATRO;
	}
}

/*
 * Inicializa el estado del nivel cuatro por separado, cargando todos los valores necesarios como
 * la cantidad de objetos en el mismo, las dimensiones del nivel, coordenadas iniciales y de salida, etc.
 * Precondiciones: El orden del nivel debe estar definido correctamente.
 * Postcondiciones: El nivel queda en un estado válido y correcto para ser jugado.
 * Todos los elementos están dentro de los límites de su nivel.
 */
void inicializar_nivel_cuatro(juego_t *juego, unsigned int *mandar_filas, unsigned int *mandar_columnas){
	int identificador_nivel = ORDEN_NIVEL_CUATRO;
	dar_limites(mandar_filas,mandar_columnas,identificador_nivel);
	juego->niveles[ORDEN_NIVEL_CUATRO].numero= NIVEL_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].horrocrux_destruido=false;
	juego->niveles[ORDEN_NIVEL_CUATRO].tiene_guardian=true;
	juego->niveles[ORDEN_NIVEL_CUATRO].entrada.fila=FILA_INICIAL_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].entrada.columna=COLUMNA_INICIAL_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].salida.fila=FILA_SALIDA_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].salida.columna=COLUMNA_SALIDA_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].filas=FILAS_NIVEL_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].columnas=COLUMNAS_NIVEL_CUATRO;
	juego->niveles[ORDEN_NIVEL_CUATRO].cantidad_objetos=OBJETOS_NIVEL_CUATRO;
	asignar_coordenadas(juego ,mandar_filas ,mandar_columnas ,identificador_nivel );
	asignar_codigos(juego,identificador_nivel);
}

/*
 * Inicializa el estado del nivel tres por separado, cargando todos los valores necesarios como
 * la cantidad de objetos en el mismo, las dimensiones del nivel, coordenadas iniciales y de salida, etc.
 * Precondiciones: El orden del nivel debe estar definido correctamente.
 * Postcondiciones: El nivel queda en un estado válido y correcto para ser jugado.
 * Todos los elementos están dentro de los límites de su nivel.
 */
void inicializar_nivel_tres(juego_t *juego, unsigned int *mandar_filas, unsigned int *mandar_columnas){
	int identificador_nivel = ORDEN_NIVEL_TRES;
	dar_limites(mandar_filas,mandar_columnas,identificador_nivel);
	juego->niveles[ORDEN_NIVEL_TRES].numero= NIVEL_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].horrocrux_destruido=false;
	juego->niveles[ORDEN_NIVEL_TRES].tiene_guardian=true;
	juego->niveles[ORDEN_NIVEL_TRES].direccion_duende=DIRECCION_DUENDE_IZQUIERDA;
	juego->niveles[ORDEN_NIVEL_TRES].entrada.fila=FILA_INICIAL_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].entrada.columna=COLUMNA_INICIAL_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].salida.fila=FILA_SALIDA_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].salida.columna=COLUMNA_SALIDA_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].filas=FILAS_NIVEL_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].columnas=COLUMNAS_NIVEL_TRES;
	juego->niveles[ORDEN_NIVEL_TRES].cantidad_objetos=OBJETOS_NIVEL_TRES;
	asignar_coordenadas(juego ,mandar_filas ,mandar_columnas ,identificador_nivel );
	asignar_codigos(juego,identificador_nivel);
}

/*
 * Inicializa el estado del nivel dos por separado, cargando todos los valores necesarios como
 * la cantidad de objetos en el mismo, las dimensiones del nivel, coordenadas iniciales y de salida, etc.
 * Precondiciones: El orden del nivel debe estar definido correctamente.
 * Postcondiciones: El nivel queda en un estado válido y correcto para ser jugado.
 * Todos los elementos están dentro de los límites de su nivel.
 */
void inicializar_nivel_dos(juego_t *juego, unsigned int *mandar_filas, unsigned int *mandar_columnas){
	int identificador_nivel = ORDEN_NIVEL_DOS;
	dar_limites(mandar_filas,mandar_columnas,identificador_nivel);
	juego->niveles[ORDEN_NIVEL_DOS].numero= NIVEL_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].horrocrux_destruido=false;
	juego->niveles[ORDEN_NIVEL_DOS].tiene_guardian=true;
	juego->niveles[ORDEN_NIVEL_DOS].basilisco_destruido=BASILISCO_ESTADO_INICIAL;
	juego->niveles[ORDEN_NIVEL_DOS].entrada.fila=FILA_INICIAL_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].entrada.columna=COLUMNA_INICIAL_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].salida.fila=FILA_SALIDA_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].salida.columna=COLUMNA_SALIDA_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].filas=FILAS_NIVEL_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].columnas=COLUMNAS_NIVEL_DOS;
	juego->niveles[ORDEN_NIVEL_DOS].cantidad_objetos=OBJETOS_NIVEL_DOS;
	asignar_coordenadas(juego ,mandar_filas ,mandar_columnas ,identificador_nivel );
	asignar_codigos(juego,identificador_nivel);
}

/*
 * Inicializa el estado del nivel uno por separado, cargando todos los valores necesarios como
 * la cantidad de objetos en el mismo, las dimensiones del nivel, coordenadas iniciales y de salida, etc.
 * Precondiciones: El orden del nivel debe estar definido correctamente.
 * Postcondiciones: El nivel queda en un estado válido y correcto para ser jugado.
 * Todos los elementos están dentro de los límites de su nivel.
 */
void inicializar_nivel_uno(juego_t *juego, unsigned int *mandar_filas, unsigned int *mandar_columnas){
	int identificador_nivel = ORDEN_NIVEL_UNO;
	dar_limites(mandar_filas,mandar_columnas,identificador_nivel);
	juego->niveles[ORDEN_NIVEL_UNO].numero= NIVEL_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].horrocrux_destruido=false;
	juego->niveles[ORDEN_NIVEL_UNO].tiene_guardian=false;
	juego->niveles[ORDEN_NIVEL_UNO].entrada.fila=FILA_INICIAL_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].entrada.columna=COLUMNA_INICIAL_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].salida.fila=FILA_SALIDA_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].salida.columna=COLUMNA_SALIDA_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].filas=FILAS_NIVEL_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].columnas=COLUMNAS_NIVEL_UNO;
	juego->niveles[ORDEN_NIVEL_UNO].cantidad_objetos=OBJETOS_NIVEL_UNO;
	asignar_coordenadas(juego ,mandar_filas ,mandar_columnas ,identificador_nivel );
	asignar_codigos(juego,identificador_nivel);
}

void inicializar_juego(juego_t *juego){
	unsigned int mandar_filas;
	unsigned int mandar_columnas;
	inicializar_nivel_uno(juego, &mandar_filas,&mandar_columnas);
	inicializar_nivel_dos(juego, &mandar_filas,&mandar_columnas);
	inicializar_nivel_tres(juego, &mandar_filas,&mandar_columnas);
	inicializar_nivel_cuatro(juego, &mandar_filas,&mandar_columnas);
	juego->jugador.posicion.fila = FILA_INICIAL_UNO;
	juego->jugador.posicion.columna = COLUMNA_INICIAL_UNO;
	juego->jugador.cantidad_items=TOPE_INICIAL_MOCHILA;
	juego->jugador.envenenado=false;
	juego->jugador.turnos_envenenado= TURNOS_ENVENENADO;
	juego->jugador.turnos_restantes= CANTIDAD_TURNOS;
	juego->nivel_actual= NIVEL_UNO;
	juego->estado= JUGANDO;
}