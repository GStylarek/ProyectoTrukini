# ProyectoTrukini
------------------------------------------------------------------------------------
 -. Fabricio Rojas y Gerardo Stylarek .-
------------------------------------------------------------------------------------
Programación I, Tecnicatura en Infraestructura Informática/Desarrollo de Software
------------------------------------------------------------------------------------
Lenguaje de programación: C
------------------------------------------------------------------------------------
La idea del proyecto es lograr simular un juego de cartas argentino llamado "truco", con todas sus caracteristicas y reglas: 
-Reconocer e identificar las distintas cartas y sus respectivos valores.
-Barajar el mazo de 40 cartas.
-Repartir entre dos jugadores, 3 cartas para cada uno.
-Permitir las diferentes "jugadas" de las reglas: truco, retruco, vale 4, envido, real envido, falta envido.
-Imprimir que jugador ganó la ronda y cuantos puntos se lleva cada uno.
-Imprimir en un cuadro una matriz donde se vayan guardando la cantidad de puntos.

------------------------------------------------------------------------------------
-Fase uno (manual)-
------------------------------------------------------------------------------------
*-Nos gustaria utilizar "rand()" y "time()" para implementar el algoritmo de Fisher-Yates, para garantizar un orden aleatorio "justo" 
al repartir las cartas.*

Funciones:

-*inicializar_mazo*: crea las 40 estructuras de Carta y llama asignar_valores_carta para darles sus valores de juego.

-*asignar_valores_carta*: contiene la lógica central del truco, determina el valor_truco (jerarquia) y el valor_envido de cada carta.

-*barajar*: desordena el mazo de cartas de forma aleatoria (aqui utilizamos rand() y time ()).

-*repartir*: asigna las primeras 6 cartas del mazo barajando a las manos de los jugadores.

-------------------------------------------------------------------------------------------------------------------------------

Envido y Puntuación:

*-obetener_valor_envido_mano*: calcula el puntaje de envido más alto que tiene un jugador en su mano (inlcuyendo la logica de
20 + suma de cartas y la detección de Flor).

*-resolver_envido*: compara los puntajes de envido de ambos jugadores y asigna los puntos de la apuesta al ganador.

*-imprimir_puntos_totales:* muestra la tabla (matriz) de puntuación actual de ambos jugadores en la consola.

--------------------------------------------------------------------------------------------------------------------------------

Truco y juego:

*-determinar_ganador_baza*: compara los valor_truco de dos cartas jugadas para saber quién gana una baza individual.

--------------------------------------------------------------------------------------------------------------------------------
Utilizamos los bucles for y while:
--
for:
--
*incializador_mazo*: Itera a través de los 4 palos y los 10 números de cartas (1 al 12, omitiendo 8 y 9) para crear las 40 cartas y
asignarles sus valores.

*barajar*: Itera a través de todo el mazo (39 veces) para intercambiar cada carta con una posición aleatoria, implementando el
algoritmo de Fisher-Yates.

*repartir*: itera 3 veces para asignar las cartas del mazo a la mano de cada jugador.

---------------------------------------------------------------------------------------------------------------------------------
while:
--
*main*: el bucle principal del juego se ejecuta mientras la puntuación de ningún jugador haya alcanzado los puntos necesarios para
ganar (definidos por PUNTOS_FINALES). Este bucle asegura que se jueguen rondas sucesivas hasta que haya un gandor.

------------------------------------------------------------------------------------
Vectores 
--
En el código, los vectores se usan para representar colecciones de elementos del mismo tipo, como las cartas y la mano de un jugador.

1. El Mazo de Cartas

El mazo es el vector más grande, conteniendo todas las cartas del juego:

Declaración: *Carta mazo[NUM_CARTAS];*

Función: Almacena las 40 cartas posibles. Es un arreglo de 40 estructuras de tipo Carta.

2. La Mano del Jugador
   
La mano de cada jugador es un pequeño vector que almacena las cartas que le fueron repartidas:

Declaración: *Carta mano[CARTAS_POR_JUGADOR];* (dentro de la estructura *Jugador*)

Función: Almacena las 3 cartas que tiene cada jugador en una ronda.

3. Arreglos Auxiliares
   
También se usan vectores más pequeños para tareas de puntuación y control:

Puntuación Total: *int puntos_totales[2]*.

Ganadores de Baza: *int ganadores_baza[CARTAS_POR_JUGADOR]* (para llevar el registro de quién ganó cada una de las 3 bazas).


----------------------------------------------------------------------------------------------------------------
V1.0(FASE 1)
----------------------------------------------------------------------------------------------------------------
En la primer versión del código notamos que nuestro código necesitaba varias mejoras:

1. Limpiar la consola por cada nueva ronda.
2. Eliminar el consumo extra de líneas
3. Manejo más correcto de las instancias.
4. Más dinamismo.
5. Más complejidad, el código si bien cumple con las consignas, es muy aburrido y monotono.

  
   Fuentes:
   --
  |Flavio Copes| The C Beginner's Handbook: *https://www.freecodecamp.org/news/the-c-beginners-handbook/*
   
 |Brian W. Kernighan, Dennis M. Ritchie|EL LENGUAJE DE PROGRAMACION C, Segunda Edicion: *https://frrq.cvg.utn.edu.ar/pluginfile.php/13741/mod_resource/content/0/El-lenguaje-de-programacion-C-2-ed-kernighan-amp-ritchie.pdf*
   
  |ProgramaciónATS| Programación en C: *https://youtube.com/playlist?list=PLWtYZ2ejMVJmUTNE2QVaCd1y_6GslOeZ6&si=mbGVRJU1UQ3VLRop*
   
  |ProgramaTutos| Programación en C desde cero: *https://youtu.be/-4Aj658ontU?si=BI5llpbJgr6KXZSU*


V1.1(FASE 2)
--
Una vez lograda estas mejoras menores, el código funcionaba de manera optima, pero quisimos ir un paso más allá... Luego de analizar algunos videos tutoriales, visitar algunos blogs y sostenernos un poco de la ayuda de GPT-5.1, decidimos que queriamos cambiar el enfoque y el funcionamiento de nuestro simulador.
Queriamos cambiar el enfoque de "Simulación automátizada", y darle la posibilidad de que el usuario pueda jugar contra la CPU utilizando una 'IA Básica' que se manejaba a partir de probabilidades.

Para esto agregamos a la fase de apuestas una serie de IF-ELSE anidados, en donde el jugador puede decidir si cantar jugadas como "Envido";"Real envido";"Truco";"Retruco";etc. Dentro de estas estructuras le pedimos ayuda al GPT-5.1: queriamos que nos enseñe a crear la posibilidad de que la CPU pueda elegir si tomaba la apuesta o no.

Logros:

-Logramos tener la posibilidad de jugar contra la CPU.

-Jugadas de Envido.

-Jugadas de Truco.
Para esto definimos una variable global *"typedef enum"*, para comunicar el estado del truco *{TRUCO_NINGUNO, TRUCO_CANTADO, RETRUCO_CANTADO, VALE4_CANTADO}*

Aunque esto trajo consigo varios bugs que necesitaban ser atendidos:

-Cuando la CPU rechazaba el envido, la ronda quedaba finalizada. Lo correcto era que al rechazar esto, se pase a la instacia de TRUCO.

-Cuando se pasaba a la instancia de la apuesta del TRUCO, si la CPU rechazaba no nos imprimia la tabla de puntaje, cuando lo mas acertado es que cada que finalizara una ronda, está se imprimiera.

V1.2
--

Fix I| Bug de finalización de ronda cuando la CPU rechazaba el envido: eso se producía debido a que en las estructuras IF-ELSE de los ENVIDOS, al final del ELSE, colocaba un *continue;*. Esto hacía que la máquina tomara como que se continua a la siguiente ronda.

Fix II| Al fixear esto, cuando cantaba {REAL ENVIDO}, {FALTA ENVIDO} o {ENVIDO-ENVIDO}; y la CPU no aceptaba, se realizaba la apuesta igualmente. Lo correcto sería que se sume solo 1 punto al que canto el envido.

Fix III| La impresión de la tabla fue fácil solucionar, debido a que fue tan fácil como colocar el void *imprimir_puntos_totales(&jugador1, &jugador2);* al final de cada IF-ELSE de los cantos de TRUCO.

Nuevos Objetivos:

1. Lograr que haya turnos donde la CPU sea "mano" y tome la iniciativa de cantar las jugadas.
2. Intercalar esto, un turno empieza el jugador, otro turno la CPU.
3. Que las jugadas sean realistas, que la CPU tenga la probabilidad de elevar la apuesta del jugador. (TRUCO-RETRUCO, RETRUCO-VALE 4)

