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
V1.0
----------------------------------------------------------------------------------------------------------------
En la primer versión del código notamos que nuestro código necesitaba varias mejoras:

1. Limpiar la consola por cada nueva ronda.
2. Eliminar el consumo extra de líneas
3. Manejo más correcto de "Flor".

