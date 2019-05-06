#include "horrocrux.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ESPADA_GODRIC_GRYFFINDOR_JUEGO 'E'

#define ARRIBA_JUEGO 'w'
#define IZQUIERDA_JUEGO 'a'
#define ABAJO_JUEGO 's'
#define DERECHA_JUEGO 'd'

#define NIVEL_UNO_JUEGO 1
#define NIVEL_DOS_JUEGO 2
#define NIVEL_TRES_JUEGO 3
#define NIVEL_CUATRO_JUEGO 4

#define JUGANDO 0

const int JUGADOR_PERDIO_JUEGO = -1;
const int JUGADOR_GANO_JUEGO = 1;

#define CURA_JUEGO 'P'
#define ANILLO_JUEGO 'A'
#define COLMILLOS_JUEGO 'F'
#define DIARIO_JUEGO 'D'
#define COPA_JUEGO 'C'
#define GUARDAPELO_JUEGO 'L'

/*
 * Imprime mensajes por consola dependiendo de que tipo de turno se termino primero, en caso de ambos informa tambien.
 * Precondiciones:-.
 * Postcondiciones: Se imprime por consola las razones del GAME OVER.
 */
void informar_razon_de_juego_terminado(juego_t juego){

	if((juego.estado== JUGADOR_PERDIO_JUEGO) && (juego.nivel_actual==NIVEL_DOS_JUEGO)){
		printf("\nEl Basilisco tenia hambre :(\n\nGAME OVER\n\n");
	}else if((juego.jugador.turnos_restantes == 0) || (juego.jugador.turnos_restantes == 0)){
		if(juego.estado== JUGADOR_PERDIO_JUEGO ){
		printf("\nTe quedaste sin turnos :(\n\nGAME OVER\n\n");
		}
	}else if((juego.jugador.turnos_envenenado == 0) && (juego.estado== JUGADOR_PERDIO_JUEGO) && (juego.jugador.turnos_restantes != 0)){
		printf("\nNo lograste curarte del veneno mortal :(\nA lo menos destruiste uno que otro horro.ux(?)\n\nGAME OVER\n\n");
	}else if((juego.jugador.turnos_restantes == 0) && (juego.jugador.turnos_envenenado == 0) && (juego.estado== JUGADOR_PERDIO_JUEGO)){
		printf("\nSe acabaron todos tus turnos y tambien no lograste curarte del veneno mortal\nmuy tragico :(\n\nGAME OVER\n\n");
	}else if((juego.estado== JUGADOR_GANO_JUEGO) && (juego.nivel_actual==NIVEL_CUATRO_JUEGO)){
		printf("\n\n\n\nFelicidades!!! lograste terminar el juego DESTRUYENDO HORROCRUXES :D\n\n");
		printf("Aunque aun quedan más horrocrux por destruir :( \nProximamente en DESTRUYENDO HORROCRUXES 2 - Voldemort's Last Stand \n");
		printf("maybe(?)\n\n\n");
		printf("Creditos:\n\n	Quien se atraso pero termino el tp(?): Erick Katsuo\n\n");
		printf("	El .h que me complico al principio: horrocrux.h(?)\n\n");
		printf("	Quienes hicieron el pdf del juego: no se quienes fueron exactamente(?)\n\n");
		printf("	El curso más copado: Algoritmos y Programación I - Curso Mendez\n				Alias: ALgo1Mendez (?)\n");
		printf("\n\n\n\n\n\n\nTengo hambre :(\n\n");
	}
}

/*
 * Informa el estado del guardian "Dolores Umbridge" mediante consola.
 * Precondiciones:-.
 * Postcondiciones: Informara todo el tiempo sobre el guardian mientras se permanezca en el nivel correspondiente.
 */
void mostrar_estado_dolores(juego_t juego){
	if((juego.nivel_actual==NIVEL_CUATRO_JUEGO) && ((juego.niveles[(juego.nivel_actual)-1].tiene_guardian)==true)){
		printf("Cuidado con Dolores Umbridge\nSi chocas con ella perderas 10 turnos!!! D:\n\n");
	}
}

/*
 * Informa el estado del guardian "Duende" mediante consola.
 * Precondiciones:-.
 * Postcondiciones: Informara todo el tiempo sobre el guardian mientras se permanezca en el nivel correspondiente.
 */
void mostrar_estado_duende(juego_t juego){
	if((juego.nivel_actual==NIVEL_TRES_JUEGO) && ((juego.niveles[(juego.nivel_actual)-1].tiene_guardian)==true)){
		printf("Cuidado con el Duende\nSi se encuentran perderas 7 turnos!!! D:\n\n");
	}
}

/*
 * Informa el estado del guardian "Basilisco" mediante consola.
 * Precondiciones:-.
 * Postcondiciones: Informara dependiendo de si en el nivel se encuentra o no el guardian.
 */
void mostrar_estado_basilisco(juego_t juego){
	if((juego.nivel_actual==NIVEL_DOS_JUEGO) && ((juego.niveles[(juego.nivel_actual)-1].tiene_guardian)==false)){
		printf("Mataste al Basilisco!\n\n");
	}else if((juego.nivel_actual==NIVEL_DOS_JUEGO) && ((juego.niveles[(juego.nivel_actual)-1].tiene_guardian)==true)){
		printf("Cuidado con el Basilisco!!! D: \n\n");
	}
}

/*
 * Muestra la cantidad y el codigo de los items que se poseen en cada turno.
 * Precondiciones:-.
 * Postcondiciones: Imprime por pantalla el codigo del los items poseidos.
 */
void mostrar_estado_items(juego_t juego){
	unsigned int tope_items = (juego.jugador.cantidad_items);
	printf("Mochila\n");
	for(int k=0; k<(juego.jugador.cantidad_items);k++){
		printf(" ———");
	}
	printf("\n");
	for(int i=0;i< tope_items;i++){
		printf("| %c ",juego.jugador.items[i].codigo);
	}
	printf("|\n");
	for(int k=0; k<(juego.jugador.cantidad_items);k++){
		printf(" ———");
	}
	printf("\n");
}


/*
 * Pide ingresar una direccion valida para el juego, en caso de no ingresar una direccion valida se pide que se reingrese.
 * Precondiciones: parametro "direccion" es usado con un pasaje por referencia.
 * Postcondiciones: el puntero "direccion" es asignado con un movimiento verificado.
 */
void pedir_direccion(juego_t juego, char *direccion){
	char movimiento;
	bool ingreso_confirmado=false;
	printf("Arriba: %c\nIzquierda: %c\nDerecha: %c\nAbajo: %c\n",ARRIBA_JUEGO,IZQUIERDA_JUEGO,DERECHA_JUEGO,ABAJO_JUEGO);
	while(ingreso_confirmado==false){
		
		scanf(" %c", &movimiento);
		ingreso_confirmado=puede_moverse_jugador(movimiento, juego);
		if(ingreso_confirmado==false){
			printf("\nIngreso no acepado\nReingrese movimiento valido\n");
		}

	}
	system("clear");
	system("clear");
	*direccion= movimiento;
}	

/*
 * Muestra por consola los Turnos restantes para el estado normal y el estado envenenado, en caso de que lo este.
 * Precondiciones:-.
 * Postcondiciones: Se imprime por consola los Turnos que el jugador posee.
 */
void mostrar_estado_turnos(juego_t juego){
	printf("TURNOS TOTALES: %i\n",juego.jugador.turnos_restantes );
	if(juego.jugador.envenenado==true){
		printf("TURNOS TOTALES ENVENENADO: %i\n",juego.jugador.turnos_envenenado);
	}
}

/*
 * Verifica si la posicion del jugador es la entrada del nivel correspondiente.
 * Precondiciones:-.
 * Postcondiciones: Segun el nivel, si el jugador esta en la posicion de entrada entonces se devuelve "true" en el puntero "comenzar_mover".
 */
void verificar_entrada_al_nivel(juego_t juego,bool *comenzar_mover){
	coordenadas_t posicion_jugador=juego.jugador.posicion;
	coordenadas_t posicion_inicio_nivel=juego.niveles[juego.nivel_actual-1].entrada;
	if((posicion_jugador.fila==posicion_inicio_nivel.fila)&&(posicion_jugador.columna==posicion_inicio_nivel.columna)){
		*comenzar_mover=true;
	}
}

/*
 * Inicia al guardian dependiendo del nivel.
 * Precondiciones:-.
 * Postcondiciones: Modifica alguno de los punteros dependiendo del nivel.
 */
void iniciar_guardian(juego_t juego,bool *comenzar_mover_basilisco, bool *comenzar_mover_duende, bool *comenzar_mover_dolores){
	if((juego.nivel_actual==NIVEL_DOS_JUEGO)){
		verificar_entrada_al_nivel(juego,comenzar_mover_basilisco);
	}else if(juego.nivel_actual==NIVEL_TRES_JUEGO){
		verificar_entrada_al_nivel(juego,comenzar_mover_duende);
	}else if(juego.nivel_actual==NIVEL_CUATRO_JUEGO){
		verificar_entrada_al_nivel(juego,comenzar_mover_dolores);
	}
}


/*
 * En caso de que cumpla las condiciones requeridas entonces el guardian del nivel correspondiente comenzara a moverse.
 * Precondiciones: -.
 * Postcondiciones: El guardian del nivel se mueve.
 */
void pedir_mover_guardian(juego_t *juego,bool comenzar_mover_basilisco, bool comenzar_mover_duende, bool comenzar_mover_dolores){
	if((juego->niveles[(juego->nivel_actual)-1].tiene_guardian)==true){
		if((comenzar_mover_basilisco==true) && (juego->nivel_actual==NIVEL_DOS_JUEGO)){
			mover_guardian(juego);
		}else if((comenzar_mover_duende==true) && (juego->nivel_actual==NIVEL_TRES_JUEGO)){
			mover_guardian(juego);
		}else if((comenzar_mover_dolores==true) && (juego->nivel_actual==NIVEL_CUATRO_JUEGO)){
			mover_guardian(juego);
		}
	}
}

/*
 * Muestra el estado de los turnos, items y de los guardianes correspondiente al nivel actual.
 * Precondiciones:-.
 * Postcondiciones: Informa detalles y advertencias de lo mencionado.
 */
void mostrar_estado_horrocrux(juego_t juego){
	if(juego.niveles[juego.nivel_actual-1].horrocrux_destruido==false){
		printf("El Horrocrux a destruir es: %c\n",juego.niveles[juego.nivel_actual-1].horrocrux.codigo);
	}
}

/*
 * Muestra el estado de los turnos, items, el horrocrux a destruir y de los guardianes correspondiente al nivel actual.
 * Precondiciones:-.
 * Postcondiciones: Informa detalles y advertencias de lo mencionado.
 */
void mostrar_estados(juego_t juego){
	mostrar_estado_horrocrux(juego);
	mostrar_estado_basilisco(juego);
	mostrar_estado_duende(juego);
	mostrar_estado_dolores(juego);
	mostrar_estado_turnos(juego);
	mostrar_estado_items(juego);
}


/*
 * Comienza el juego de tal manera que usa las funciones desarrolladas en el programa para dicho proposito, teniento en cuenta
 * los enunciados y caracteristicas de los niveles asi como las condiciones para ganar cada nivel y el juego en si.
 * Precondiciones: El juego esta en un estado valido, el escenario esta definido y actualizado segun el nivel actual.
 * Postcondiciones: El juego comienza teniendo en cuenta los turnos restantes correspondientes,y tambien los turnos envenenados.
 */
void comenzar_juego(juego_t juego, char escenario[MAX_FILAS][MAX_COLUMNAS]){
	int estado=JUGANDO;
	char direccion;
	bool comenzar_mover_basilisco=false;
	bool comenzar_mover_duende=false;
	bool comenzar_mover_dolores=false;
	unsigned int filas=juego.niveles[(juego.nivel_actual-1)].filas;
	unsigned int columnas=juego.niveles[(juego.nivel_actual-1)].columnas;
	mostrar_escenario(escenario, filas, columnas);
	while(estado==JUGANDO){
		iniciar_guardian(juego, &comenzar_mover_basilisco, &comenzar_mover_duende, &comenzar_mover_dolores);
		mostrar_estados(juego);
		pedir_direccion(juego,&direccion);
		mover_jugador(&juego, direccion);
		pedir_mover_guardian(&juego,comenzar_mover_basilisco,comenzar_mover_duende,comenzar_mover_dolores);
		filas=juego.niveles[(juego.nivel_actual-1)].filas;
		columnas=juego.niveles[(juego.nivel_actual-1)].columnas;
		actualizar_escenario(juego, escenario);
		mostrar_escenario(escenario, filas, columnas);
		printf("Nivel actual: %i\n",juego.nivel_actual );
		estado=estado_juego(juego);	
	}
	informar_razon_de_juego_terminado(juego);
}

int main(){
	srand((unsigned int)time(NULL));
	juego_t juego;
	char escenario[MAX_FILAS][MAX_COLUMNAS]={
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '},
		{' ',' ',' ',' ',' ',' ',' '}
	};
	inicializar_juego(&juego);
	actualizar_escenario(juego, escenario);
	comenzar_juego(juego, escenario);
	return 0;
}