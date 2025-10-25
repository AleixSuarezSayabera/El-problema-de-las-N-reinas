# El problema de las N reinas

**Programa:** `vuit_reines.c`  
**Autor:** Aleix Suárez Sayabera  
**Fecha:** 31-05-2024  

---

## Descripción

Este programa implementa **cinco algoritmos diferentes** para estudiar las soluciones al clásico problema de las **N reinas**, que consiste en colocar N reinas en un tablero de ajedrez de tamaño N×N de forma que ninguna se ataque entre sí (ni en filas, ni columnas, ni diagonales).

El objetivo del proyecto es comparar el rendimiento y comportamiento de distintos enfoques —tanto deterministas como aleatorios— para resolver o analizar este problema computacional.

---

## Algoritmos implementados

1. **`aleatori1`**  
   Determina si un vector dado representa una solución válida al problema para valores de *n* mayores que 100.

2. **`aleatori2`**  
   Busca una **solución aleatoria** al problema.  
   Ha logrado encontrar soluciones hasta *n = 23*, con tiempos variables debido a la naturaleza aleatoria del método.

3. **`aleatori3`**  
   Busca **todas las soluciones posibles** de forma aleatoria.  
   - Para un tablero de **13x13**, encuentra todas las soluciones en **3 minutos y 43 segundos**,  
     mientras que el algoritmo **backtrack** resuelve el mismo tablero en **10 segundos**.

4. **`backtrack`**  
   Implementa la búsqueda exhaustiva mediante **backtracking**.  
   - Ha conseguido encontrar soluciones para un tablero de **15x15** en **5 minutos y 51 segundos**.

5. **`matriu`**  
   Calcula las **diferentes matrices de soluciones** posibles.  
   - Para un tablero de **13x13**, las obtiene en **54 segundos**.

---

## Resultados y observaciones

| Algoritmo  | Tipo de búsqueda | Tamaño máximo probado | Tiempo aproximado |
|-------------|------------------|------------------------|--------------------|
| aleatori1   | Validación       | n > 100                | Muy rápido         |
| aleatori2   | Aleatoria (una)  | n = 23                 | Variable           |
| aleatori3   | Aleatoria (todas)| n = 13                 | 3 min 43 s         |
| backtrack   | Determinista     | n = 15                 | 5 min 51 s         |
| matriu      | Matricial        | n = 13                 | 54 s               |

---

## Objetivo del estudio

El análisis comparativo de estos algoritmos permite observar:
- La **eficiencia** de los métodos deterministas frente a los aleatorios.  
- La **escalabilidad** en función del tamaño del tablero (*n*).  
- El impacto del **azar** y las **estructuras de datos** en el tiempo de ejecución.  

