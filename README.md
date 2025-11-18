# ProyectoTrukini
------------------------------------------------------------------------------------
 -. Fabricio Rojas y Gerardo Stylarek .-
------------------------------------------------------------------------------------
Programación I, Tecnicatura en Infraestructura Informática/Desarrollo de Software
------------------------------------------------------------------------------------
Lenguaje de programación: C
------------------------------------------------------------------------------------
La idea del proyecto es lograr simular un juego de cartas argentino llamado "truco", con todas sus caracteristicas y reglas: 

- Reconocer e identificar las distintas cartas y sus respectivos valores.

- Barajar el mazo de 40 cartas.

- Repartir entre dos jugadores, 3 cartas para cada uno.

- Permitir las diferentes "jugadas" de las reglas: truco, retruco, vale 4, envido, real envido, falta envido.

- Imprimir que jugador ganó la ronda y cuantos puntos se lleva cada uno.

- Imprimir en un cuadro una matriz donde se vayan guardando la cantidad de puntos.

------------------------------------------------------------------------------------
-Fase uno (manual)-
------------------------------------------------------------------------------------
*-Nos gustaria utilizar "rand()" y "time()" para implementar el algoritmo de Fisher-Yates, para garantizar un orden aleatorio "justo" 
al repartir las cartas.*

Funciones:

- *inicializar_mazo*: crea las 40 estructuras de Carta y llama asignar_valores_carta para darles sus valores de juego.

- *asignar_valores_carta*: contiene la lógica central del truco, determina el valor_truco (jerarquia) y el valor_envido de cada carta.

- *barajar*: desordena el mazo de cartas de forma aleatoria (aqui utilizamos rand() y time ()).

- *repartir*: asigna las primeras 6 cartas del mazo barajando a las manos de los jugadores.

-------------------------------------------------------------------------------------------------------------------------------

Envido y Puntuación:

- *obetener_valor_envido_mano*: calcula el puntaje de envido más alto que tiene un jugador en su mano (inlcuyendo la logica de
20 + suma de cartas y la detección de Flor).

- *resolver_envido*: compara los puntajes de envido de ambos jugadores y asigna los puntos de la apuesta al ganador.

- *imprimir_puntos_totales:* muestra la tabla (matriz) de puntuación actual de ambos jugadores en la consola.

--------------------------------------------------------------------------------------------------------------------------------

Truco y juego:

- *determinar_ganador_baza*: compara los valor_truco de dos cartas jugadas para saber quién gana una baza individual.

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

- Opción de que el usuario coloque el nombre que quisiera tener.

- Logramos tener la posibilidad de jugar contra la CPU.

- Jugadas de Envido.

- Jugadas de Truco.
Para esto definimos una variable global *"typedef enum"*, para comunicar el estado del truco *{TRUCO_NINGUNO, TRUCO_CANTADO, RETRUCO_CANTADO, VALE4_CANTADO}*

Aunque esto trajo consigo varios bugs que necesitaban ser atendidos:

- Cuando la CPU rechazaba el envido, la ronda quedaba finalizada. Lo correcto era que al rechazar esto, se pase a la instacia de TRUCO.

- Cuando se pasaba a la instancia de la apuesta del TRUCO, si la CPU rechazaba no nos imprimia la tabla de puntaje, cuando lo mas acertado es que cada que finalizara una ronda, está se imprimiera.

V1.2
--

Fix I| Bug de finalización de ronda cuando la CPU rechazaba el envido: eso se producía debido a que en las estructuras IF-ELSE de los ENVIDOS, al final del ELSE, colocaba un *continue;*. Esto hacía que la máquina tomara como que se continua a la siguiente ronda.

Fix II| Al fixear esto, cuando cantaba {REAL ENVIDO}, {FALTA ENVIDO} o {ENVIDO-ENVIDO}; y la CPU no aceptaba, se realizaba la apuesta igualmente. Lo correcto sería que se sume solo 1 punto al que canto el envido.

Fix III| La impresión de la tabla fue fácil solucionar, debido a que fue tan fácil como colocar el void *imprimir_puntos_totales(&jugador1, &jugador2);* al final de cada IF-ELSE de los cantos de TRUCO.

Nuevos Objetivos:

1. Lograr que haya turnos donde la CPU sea "mano" y tome la iniciativa de cantar las jugadas.
2. Intercalar esto, un turno empieza el jugador, otro turno la CPU.
3. Que las jugadas sean realistas, que la CPU tenga la probabilidad de elevar la apuesta del jugador. (TRUCO-RETRUCO, RETRUCO-VALE 4)

V1.3
--

Fix I| Bug de puntos de envido: con el cambio del sistema de envido, resolvimos un bug que hacía que en algunos casos el resultado sea "empate" a pesar de tener una diferencia de puntos.
Fix II| Pulimos mejor el menú de jugadas, ahora cuando la mano es de la CPU, no nos permite cantar ENVIDO a nosotros primero.

- Reemplazamos el sistema del TRUCO, dejandolo más realista.
  1. Esto logramos reemplazando la estructura único de IF-ELSE anidado que tenia dentro de main anteriormente, y agregando una variable global con un conjunto de IF-ELSE anidado, junto con: *int = rand () %100;* para que la CPU evalúe probabilidades y pueda cantar o contra-cantar jugadas.
  
- Logramos intercalar las "manos" y que la CPU tome la iniciativa para cantar jugadas.
  
- Con el nuevo sistema, logramos pulir la inteligencia artificial de la CPU, esto permite que:
  1. Acepte y/o eleve las apuestas tanto en la instancia de TRUCO.
  2. La CPU, si bien tiene una inteligencia básica, el juego es bastante fluido y llevadero.
  3. Logramos resumir un poco mas el código, eliminando enums y otras estructuras que quedaron obsoletas con esta actualización.

  A este punto el juego es completamente funcional, dinamico y cumple su función de entretener. Aún queda mecanicas que pulir, asi que esta no seria la versión "final".

  Nuevos Objetivos:
  - Actualizar el sistema del ENVIDO, permitiendo que la IA tenga la posibilidad de aumentar la apuesta en la instancia (no solo proponer ENVIDO).
  - Pulir mejor el manejo de los turnos:
    1. Permitir cantar Truco entre rondas, si no fue cantado con anterioridad.
    2. Permitir contra-cantar ENVIDO, si el rival canta TRUCO sin haberse medido los tantos antes.
  - Perfeccionar la resolución del TRUCO, hay algunos bugs cuando se empardan las bazas que necesitan revisarse.
  - Agregar la posibilidad de rendirse o "irse al mazo", tanto para el jugador como para la CPU.
  - Aumentar la dificultad de la CPU.
    
       
 |CODIGO VERSION FINAL|
--

 1. Estructuras de Datos (La base del juego)
El código organiza la información en dos estructuras principales (structs) y dos enumeraciones (enums):

- typedef enum { ORO, COPA, ESPADA, BASTO ... } Palo; Define los 4 palos de la baraja española para facilitar la comparación y asignación.

- typedef struct { ... } Carta; Es la unidad fundamental. Cada carta tiene:

- palo y numero: Identidad visual (ej. 1 de Espada).

valor_truco: Un entero que representa la jerarquía en el juego. Por ejemplo, el 1 de Espada tiene un valor de 14 (el más alto) y un 4 tiene un valor de 1 (el más bajo). Esto evita tener que programar if complejos durante la partida; simplemente se compara carta1.valor_truco > carta2.valor_truco.

valor_envido: El valor numérico para sumar en el envido (ej. un 12 vale 0, un 7 vale 7).

typedef struct { ... } Jugador; Representa al usuario y a la CPU. Guarda el nombre, la mano actual (array de 3 cartas) y los puntos acumulados en la partida.


2. Inicialización y Lógica de Cartas
Antes de jugar, el código prepara el terreno mediante dos funciones clave:

inicializar_mazo y asignar_valores_carta: Aquí es donde se definen las reglas del Truco. El código recorre los palos y números, omite los 8 y 9, y asigna el valor_truco manualmente según el reglamento (Ancho de espada > Ancho de basto > 7 de espada, etc.).

barajar: Utiliza el algoritmo Fisher-Yates para mezclar el array de cartas de manera eficiente y aleatoria.


3. El Flujo Principal (main)
El juego corre dentro de un bucle while que continúa hasta que uno de los jugadores alcanza los PUNTOS_FINALES (definido en 15). La secuencia de una ronda es:

Limpieza y Reparto: Se limpia la consola, se baraja y se reparten 3 cartas a cada uno.

Alternancia de Mano: Se usa la variable global mano (1 o 2) para saber quién "es mano" (quien juega primero y gana los empates de envido).

Fase de Envido:

Se evalúa si se canta Envido.

La función obtener_valor_envido_mano calcula los puntos automáticamente, detectando si hay "Flor" (3 del mismo palo) o sumando la mejor pareja del mismo palo + 20.

El código permite cantar Envido, Real Envido y Falta Envido.

Fase de Truco (Cantos):

Se llama a cantar_truco. Aquí los jugadores pueden subir la apuesta (Truco, Retruco, Vale 4).

Si alguien dice "No quiero", la ronda termina inmediatamente y se suman los puntos al ganador.

Fase de Bazas (Jugar las cartas):

Si el Truco fue querido (o no se cantó nada), se ejecuta jugar_mano.

4. Inteligencia Artificial (La CPU)
La "IA" de la CPU es sencilla y se basa en probabilidades aleatorias (RNG):

En el Envido: Calcula sus puntos. Si tiene más de 31 puntos, tiene un 80% de probabilidad de cantar envido. Si tiene menos, la probabilidad baja drásticamente (simulando que a veces miente o "bluffea" con puntos bajos).

En el Truco:

Para cantar o responder, usa rand() % 100. Por ejemplo, si le cantan Truco, tiene un 50% de chance de querer, 30% de no querer y un porcentaje restante de revirar con Retruco.

Jugando Cartas (jugar_mano):

Actualmente, la CPU juega una carta al azar (rand() % cartas_restantes). No analiza si está matando la carta del jugador o si está desperdiciando un ancho de espadas.

5. Mecánica de Juego (jugar_mano)
Esta función maneja el "mejor de tres":

Bucle de 3 iteraciones (máximo).

El jugador elige una carta por índice (1, 2 o 3).

Se usa eliminar_carta para sacar la carta jugada del array de la mano (desplazando las restantes).

Se compara con determinar_ganador_baza.

El primero en ganar 2 manos (bazas) gana la ronda.

Regla de primera: Si hay empate en bazas (parda), el código tiene lógica para definir ganador basándose en quién ganó la primera (variable primera_ganada).

Resumen de Variables Globales Importantes
EstadoTruco estadoTruco: Mantiene el estado actual (si se cantó Truco, Retruco, etc.) para saber cuántos puntos están en juego.

int mano: Controla quién empieza la ronda. Es vital para definir quién gana en caso de empate en el envido.
