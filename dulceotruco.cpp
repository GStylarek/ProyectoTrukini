#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// --- CONSTANTES Y ENUMS ---
#define NUM_CARTAS 40
#define CARTAS_POR_JUGADOR 3
#define PUNTOS_FINALES 15 // Puntos para ganar la partida, si se desea se puede cambiar por 30

// Enum para los Palos
typedef enum {
    ORO, COPA, ESPADA, BASTO, NUM_PALOS
} Palo;

// Enum para la posible acción de un jugador
typedef enum {
    NADA, TRUCO, ENVIDO
} Accion;

//Enum para el estado del truco (v1.1)
typedef enum{
	TRUCO_NINGUNO = 0,
	TRUCO_CANTADO = 1,
	RETRUCO_CANTADO = 2,
	VALE4_CANTADO = 3
}EstadoTruco;

EstadoTruco estadoTruco = TRUCO_NINGUNO;

// --- ESTRUCTURAS ---

// Estructura de la Carta
typedef struct {
    Palo palo;
    int numero;         // 1, 2, 3, 4, 5, 6, 7, 10, 11, 12
    int valor_truco;    // Jerarquía de la carta 
    int valor_envido;   // Valor para el Envido (1-7, 0 para figuras)
} Carta;

// Estructura del Jugador
typedef struct {
    int id;
    char nombre[20];
    Carta mano[CARTAS_POR_JUGADOR];
    int puntos_partida;
} Jugador;

// --- DECLARACIONES DE FUNCIONES ---
void inicializar_mazo(Carta mazo[]);
void asignar_valores_carta(Carta *c);
void barajar(Carta mazo[], int n);
void repartir(Carta mazo[], Jugador *j1, Jugador *j2);
void imprimir_carta(Carta c);
void imprimir_mano(Jugador *j);
int obtener_valor_envido_mano(Jugador *j);
void jugar_mano(Jugador *j1, Jugador *j2, int *puntos_truco, int *puntos_envido);
void imprimir_puntos_totales(Jugador *j1, Jugador *j2);

// --- UTILIDADES DE IMPRESIÓN ---

const char *nombre_palo[] = {"O", "C", "E", "B"};

void imprimir_carta(Carta c) {
    // Muestra el número real y la inicial del palo
    printf("(%d de %s)", c.numero, nombre_palo[c.palo]);
}

void imprimir_mano(Jugador *j) {
    printf("Mano de %s:\n", j->nombre);
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        printf(" [%d]: ", i + 1);
        imprimir_carta(j->mano[i]);
        printf(" (T:%d | E:%d)\n", j->mano[i].valor_truco, j->mano[i].valor_envido);
    }
}

void imprimir_puntos_totales(Jugador *j1, Jugador *j2) {
    printf("\n--- PUNTUACION DE LA PARTIDA ---\n");
    printf("+----------------------+----------------------+\n");
    printf("| %-20s | %-20s |\n", j1->nombre, j2->nombre);
    printf("+----------------------+----------------------+\n");
    printf("| %-20d | %-20d |\n", j1->puntos_partida, j2->puntos_partida);
    printf("+----------------------+----------------------+\n");
}

// --- LÓGICA DE CARTAS ---

// Asigna los valores de Truco y Envido a una carta
void asignar_valores_carta(Carta *c) {
    // 1. Asignar valor de ENVIDO
    if (c->numero >= 10) { // 10, 11, 12 (figuras) valen 0
        c->valor_envido = 0;
    } else {
        c->valor_envido = c->numero;
    }

    // 2. Asignar valor de TRUCO (Jerarquía)
    int num = c->numero;
    Palo p = c->palo;

    if (num == 1 && p == ESPADA) c->valor_truco = 12; // 1 E (Macho)
    else if (num == 1 && p == BASTO) c->valor_truco = 11; // 1 B
    else if (num == 7 && p == ESPADA) c->valor_truco = 10; // 7 E
    else if (num == 7 && p == ORO) c->valor_truco = 9; // 7 O
    else if (num == 3) c->valor_truco = 8;
    else if (num == 2) c->valor_truco = 7;
    else if (num == 1) c->valor_truco = 6; // 1 de Copa y Oro
    else if (num == 12) c->valor_truco = 5; // Reyes
    else if (num == 11) c->valor_truco = 4; // Caballos
    else if (num == 10) c->valor_truco = 3; // Sotas
    else if (num == 7) c->valor_truco = 2; // 7 de Copa y Basto
    else c->valor_truco = 1; // 4, 5, 6
}

// Inicializa las 40 cartas del mazo
void inicializar_mazo(Carta mazo[]) {
    int indice = 0;
    for (int p = ORO; p < NUM_PALOS; p++) {
        for (int n = 1; n <= 12; n++) {
            // Se saltan los números 8 y 9
            if (n != 8 && n != 9) {
                mazo[indice].palo = (Palo)p;
                mazo[indice].numero = n;
                asignar_valores_carta(&mazo[indice]);
                indice++;
            }
        }
    }
}

// --- LÓGICA DE REPARTO Y MEZCLA ---

// Algoritmo de Fisher-Yates para barajar, aqui hago un cambio para que solo baraje y no siembre. Porque puede producir malas mezclas
void barajar(Carta mazo[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta temp = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temp;
    }
}

// Reparte las primeras 6 cartas del mazo a los jugadores
void repartir(Carta mazo[], Jugador *j1, Jugador *j2) {
    int idx = 0;
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        j1->mano[i] = mazo[idx++]; // carta para j1
        j2->mano[i] = mazo[idx++]; // carta para j2
    }
}

// --- LÓGICA DE JUEGO (ENVIDO) ---

// Calcula el puntaje de Envido de una mano
int obtener_valor_envido_mano(Jugador *j) {
    int flor = 0;
    int envido = 0;

    // Detectar Flor: las 3 cartas del mismo palo
    if (j->mano[0].palo == j->mano[1].palo &&
        j->mano[0].palo == j->mano[2].palo) {

        flor = 20 +
               j->mano[0].valor_envido +
               j->mano[1].valor_envido +
               j->mano[2].valor_envido;

        return flor;  // Flor tiene prioridad
    }

    // Si no hay Flor, calcular Envido normal
    int max_pareja = 0;

    for (int i = 0; i < 3; i++) {
        for (int k = i + 1; k < 3; k++) {
            if (j->mano[i].palo == j->mano[k].palo) {
                int envido_pareja =
                    20 + j->mano[i].valor_envido + j->mano[k].valor_envido;

                if (envido_pareja > max_pareja)
                    max_pareja = envido_pareja;
            }
        }
    }

    // si no hubo pareja, el envido es la carta más alta
    if (max_pareja == 0) {
        int max_carta = 0;
        for (int i = 0; i < 3; i++)
            if (j->mano[i].valor_envido > max_carta)
                max_carta = j->mano[i].valor_envido;

        return max_carta;
    }

    return max_pareja;
}

// Resuelve la apuesta de Envido
void resolver_envido(Jugador *j1, Jugador *j2, int *puntos_envido) {
    int envido1 = obtener_valor_envido_mano(j1);
    int envido2 = obtener_valor_envido_mano(j2);
    
    printf("\n*** RESOLUCION DEL ENVIDO ***\n");
    printf("%s canta %d de envido. | %s canta %d de envido.\n", j1->nombre, envido1, j2->nombre, envido2);

    if (envido1 > envido2) {
        printf("Gana %s con %d Suma %d puntos.\n", j1->nombre, envido1, *puntos_envido);
        j1->puntos_partida += *puntos_envido;
    } else if (envido2 > envido1) {
        printf("Gana %s con %d Suma %d puntos.\n", j2->nombre, envido2, *puntos_envido);
        j2->puntos_partida += *puntos_envido;
    } else {
        // En caso de empate, gana el que es "Mano" (el jugador 1 en este caso)
        printf("Empate Gana %s (Mano) con %d. Suma %d puntos.\n", j1->nombre, envido1, *puntos_envido);
        j1->puntos_partida += *puntos_envido;
    }
}

// --- LÓGICA DE JUEGO (TRUCO) ---

// Determina el ganador de una baza (una carta contra otra)
// Devuelve 1 si gana j1, 2 si gana j2, 0 si es empate.
int determinar_ganador_baza(Carta c1, Carta c2) {
    if (c1.valor_truco > c2.valor_truco) {
        return 1;
    } else if (c2.valor_truco > c1.valor_truco) {
        return 2;
    } else {
        return 0; // Empate
    }
}

// Bucle principal de la mano
void jugar_mano(Jugador *j1, Jugador *j2, int *puntos_truco, int *puntos_envido) {
    int bazas_j1 = 0;
    int bazas_j2 = 0;
    int ganadores_baza[CARTAS_POR_JUGADOR] = {0, 0, 0};
    
    // Simulación simplificada de la jugada de cartas (1 baza por carta)
    for (int i = 0; i < CARTAS_POR_JUGADOR; i++) {
        printf("\n--- BAZA %d ---\n", i + 1);
        
        // Juegan las cartas más altas que les quedan
        // (Esto es una simplificación; en el juego real el jugador elige)
        Carta c1 = j1->mano[i]; 
        Carta c2 = j2->mano[i]; 
        
        printf("%s juega ", j1->nombre); imprimir_carta(c1);
        printf(" vs. %s juega ", j2->nombre); imprimir_carta(c2);
        printf("\n");

        ganadores_baza[i] = determinar_ganador_baza(c1, c2);

        if (ganadores_baza[i] == 1) {
            bazas_j1++;
            printf("Baza ganada por %s.\n", j1->nombre);
        } else if (ganadores_baza[i] == 2) {
            bazas_j2++;
            printf("Baza ganada por %s.\n", j2->nombre);
        } else {
            printf("Baza empatada.\n");
        }
        
        // Lógica de corte: si alguien gana 2 bazas, se termina
        if (bazas_j1 >= 2) break;
        if (bazas_j2 >= 2) break;
        // La lógica de empate es más compleja en Truco (se define por la primera baza ganada)
    }

    // Determinar el ganador final del TRUCO
    printf("\n*** RESOLUCION DEL TRUCO ***\n");
    if (bazas_j1 > bazas_j2) {
        printf("%s gana la mano de Truco Suma %d puntos.\n", j1->nombre, *puntos_truco);
        j1->puntos_partida += *puntos_truco;
    } else if (bazas_j2 > bazas_j1) {
        printf("%s gana la mano de Truco Suma %d puntos.\n", j2->nombre, *puntos_truco);
        j2->puntos_partida += *puntos_truco;
    } else {
        printf("Mano empatada Se define por la primera baza, gana %s. Suma %d puntos.\n", j1->nombre, *puntos_truco);
        j1->puntos_partida += *puntos_truco;
    }
}

// --- FUNCIÓN PRINCIPAL ---

int main() {
    Carta mazo[NUM_CARTAS];
    Jugador jugador1 = {1, "", {}, 0};
    Jugador jugador2 = {2, "CPU", {}, 0};
    
    //Pedir nombre al jugador
    printf("Ingresa tu nombre: ");
    fgets(jugador1.nombre, 20, stdin);
    jugador1.nombre[strcspn(jugador1.nombre, "\n")] = '\0'; //sacar salto de línea
    
    // Inicialización
    inicializar_mazo(mazo);
    srand((unsigned) time(NULL)); //<<--- aquí movi el srand, para sembrar una sola vez
    printf("¡Trukini iniciado!\n");
    printf("Objetivo: %d puntos.\n\n", PUNTOS_FINALES);
    
    // Bucle principal del juego
    while (jugador1.puntos_partida < PUNTOS_FINALES && jugador2.puntos_partida < PUNTOS_FINALES) {
        
        //LIMPIAR CONSOLA
        
        #ifdef _WIN32
              system("cls");
              #else
              system("clear");
        #endif
        
        printf("===========================================\n");
        printf("              NUEVA RONDA\n");
        printf("===========================================\n");
        
        barajar(mazo, NUM_CARTAS);
        repartir(mazo, &jugador1, &jugador2);
        
        // Puntuación de la ronda actual
        int puntos_truco_ronda = 1; // La mano vale 1 punto (o más si se canta Truco)
        int puntos_envido_ronda = 2; // Envido vale 2 si se acepta
        
        // --- 1. MOSTRAR MANOS (En un juego real, esto no se mostraría) ---
        imprimir_mano(&jugador1);
        printf("\n");
        imprimir_mano(&jugador2);
        printf("\n");

        // --- 2. FASE DE APUESTAS (Envido y Truco) ---

        // Camtar Envido
        int opcion;
        int puntos_envido = 0;
        int estadoEnvido = 0;
        int envido_aceptado = 0; //Fix bug de la finalizacion de ronda en el envido y suma de puntos
        
        printf("\nDeseas cantar envido?\n");
        
        printf("1) No\n");
        printf("2) Envido\n");
        printf("3) Real Envido\n");
        printf("4) Falta Envido\n");
        printf("Elige: ");
        scanf("%d", &opcion);
        getchar();
        //agregar el if anidado de envido,envido,real envido, falta envido
        
        if(opcion == 2){
        	printf("\n%s dice: le canto Envido compa!.\n", jugador1.nombre);
        	estadoEnvido = 1;
        	puntos_envido = 2;
        	
        	int prob = rand() % 100;
        	if (prob < 70){
        		printf("El rival dice: Quiero!\n");
        		envido_aceptado = 1;
        	} else {
        		printf("El rival dice: NO quiero...\n");
        	    jugador1.puntos_partida +=1;
				printf("%s suma 1 punto.\n", jugador1.nombre); 
				printf("\nPresiona ENTER para la siguiente ronda...\n");
				getchar();
        	}
        } else if (opcion == 3){
        	printf("\nREAL ENVIDO hermano!\n");
        	estadoEnvido = 3;
        	puntos_envido = 3;
        	
        	int prob = rand() % 100;
        	if(prob < 50){
        		printf("El rival dice: QUIERO!!\n");
        		envido_aceptado = 1;
        	} else {
        		printf("El rival dice: NO quiero...\n");
        		jugador1.puntos_partida += 1; //Real envido directo no querido = 1
        		printf("%s suma 1 punto.\n", jugador1.nombre);
        		printf("\nPresiona ENTER para la siguiente ronda...\n");
        		getchar();
        		
        	}
        } else if (opcion == 4){
        	printf("\nAchica que te canto la FALTA ENVIDO!!\n");
			estadoEnvido = 4;
			
			int prob = rand() % 100;
			if (prob < 45){
				printf("El rival dice: Oa TATA, QUIERO que p*ta no voy a querer!!\n");
				envido_aceptado = 1;
				puntos_envido = 30 - jugador1.puntos_partida;
			} else {
				printf("El rival dice: me achico nomas... NO quiero!\n");
				jugador1.puntos_partida += 1;
				printf("%s suma 1 punto. \n", jugador1.nombre);
				printf("\nPresiona ENTER para la siguiente ronda...\n");
				getchar();
			}	
        }
        
        if (envido_aceptado == 1){
        	int puntaje_j1 = obtener_valor_envido_mano(&jugador1);
        	int puntaje_j2 = obtener_valor_envido_mano(&jugador2);
        	
        	printf("\nTu envido es: %d\n", puntaje_j1);
        	printf("Envido del rival: %d\n", puntaje_j2);
        	
        	if (puntaje_j1 > puntaje_j2){
        		jugador1.puntos_partida += puntos_envido;
        		printf("\nGANASTE el Envido! +%d puntos.\n", puntos_envido);
        	} else {
        		jugador2.puntos_partida += puntos_envido;
        		printf("\nPerdiste el Envido...el rival suma %d puntos.\n", puntos_envido);
        	}
        	printf("\nPresiona ENTER para continuar...\n");
        	getchar();
        }
        
        //------ OPCION DE CANTAR TRUCO -------
	
		estadoTruco = TRUCO_NINGUNO;
		
		printf("\nDeseas cantar truco?\n");
		printf("1) No\n");
		printf("2) Truco\n");
		printf("Elige: ");
		scanf("%d",&opcion);
		getchar();
		
		if (opcion == 2){
			printf("\nCantas TRUCO.\n");
			estadoTruco= TRUCO_CANTADO;
			
						//Respuesta del rival (IA simple)
			int prob = rand() % 100;
			if (prob < 70){
				printf("El rival dice: QUIERO!\n");
				puntos_truco_ronda = 2;
			} else {
			printf("El rival dice: NO quiero...\n");
			jugador1.puntos_partida +=1;
			printf ("%s suma 1 punto. \n", jugador1.nombre);
			imprimir_puntos_totales(&jugador1, &jugador2);
			printf("\nPresiona ENTER para la siguiente ronda...\n");
			getchar();
			continue;	
			}
			
			if(estadoTruco == TRUCO_CANTADO){
				printf("\nDeseas cantar Retruco?\n");
				printf("1) No\n");
				printf("2) Retruco!\n");
				printf("Elegi: ");
				scanf("%d",&opcion);
				getchar();
				
				if (opcion == 2){
					printf("\nRETRUCO!\n");
					estadoTruco = RETRUCO_CANTADO;
					
					int prob = rand() %100;
					if (prob < 50){
						printf("El rival dice: QUIERO LA PUCHA!\n");
						puntos_truco_ronda = 3;
					}else {
					printf("El rival dice: NO quiero...\n");
					jugador1.puntos_partida += 2;
					printf("%s suma 2 puntos.\n", jugador1.nombre);
					imprimir_puntos_totales(&jugador1, &jugador2);
					printf("\nPresiona ENTER para la siguiente ronda...\n");
					getchar();
					continue;
			     	}
			     	
			     	
					if (estadoTruco == RETRUCO_CANTADO){
						printf("\nDeseas cantar VALE 4?\n");
		               	printf("1) NO\n");
		            	printf("2) QUIERO VALE 4!!\n");
		            	printf("Elige: ");
		            	scanf("%d", &opcion);
			            getchar();
			            
			            if (opcion == 2){
							printf("\nCantas VALE CUATRO!\n");
				            estadoTruco = VALE4_CANTADO;
				
				            int prob = rand() % 100;
							
							if(prob<40){
								printf("El rival dice: QUIERO!!\n");
					            puntos_truco_ronda = 4;
							} else {
									printf("El rival dice: No che, no quiero...\n");
					                jugador1.puntos_partida += 3;
				                	printf("%s suma 3 puntos.\n", jugador1.nombre);
				                	imprimir_puntos_totales(&jugador1, &jugador2);
					                printf("\nPresiona ENTER para la siguiente ronda...\n");
					                getchar();
					                continue;
							}
							
							
						}
					}
					
				}
			}

		}  
		
        
        // --- 3. FASE DE JUEGO DE CARTAS ---
        jugar_mano(&jugador1, &jugador2, &puntos_truco_ronda, &puntos_envido_ronda);
        
        // --- 4. MOSTRAR PUNTUACIÓN ---
        imprimir_puntos_totales(&jugador1, &jugador2);
        
        printf("\nPresiona ENTER para la siguiente ronda...\n");
        // Limpiar el buffer de entrada para esperar un ENTER
        fflush(stdout);
        getchar();
      
    }
    
    // --- 5. RESULTADO FINAL ---
    printf("\n\n###########################################\n");
    if (jugador1.puntos_partida >= PUNTOS_FINALES) {
        printf("GANADOR DE LA PARTIDA: %s !!!\n", jugador1.nombre);
    } else {
        printf("GANADOR DE LA PARTIDA: %s !!!\n", jugador2.nombre);
    }
    printf("###########################################\n");

    return 0;
}



