# Tarea 2
Cesar Arancibia Gil
rut: 22.176.081-6
Rol: 202573066-9

## TDA´s
- `Tipos.hpp": tipos `Carta` y `Enemigo`.
- `Pila.hpp/.cpp`: mazo y descarte LIFO; push/pop/top.
- `Cola.hpp/.cpp`: horda FIFO; encolar/desencolar/frente.
- `ABB.hpp/.cpp`: ordenado por ID; inserción/búsqueda promedio; recorrido.
- `AVL.hpp/.cpp`: grimorio ordenado por ID con balanceo; inserción/búsqueda, rotaciones , recorridos.
- `Juego.hpp`, `Juego.cpp`: carga, mano fija de 5 cartas, combate, comandos y guardado.
- `main.cpp`: argumentos de línea de comandos.

## Compilación
En Linux con `g++`:
```sh
make
```
tambien se puede usar:
```sh
g++ main.cpp Pila.cpp Cola.cpp ABB.cpp AVL.cpp Juego.cpp -o tarea2 -Wall -std=c++11
```

## Ejecución
```sh
./tarea2 inicio.txt partida.txt arbol.txt
```
También puede usarse `make run INICIO=inicio.txt COMANDOS=partida.txt SALIDA=arbol.txt`.

## Mapeo mecánica a TDA respectiva
|     Mecánica      | Estructura | Complejidad principal |
|-------------------|------------|-----------------------|
| Mazo y descarte   |   `tPila`  | operaciones, reciclaje|
|       Horda       |   `tCola`  | operaciones ,impresión por rotación|
|     Bestiario     |   `tABB`   | búsqueda/inserción |
|     Grimorio      |   `tAVL`   | búsqueda/inserción |
|Mano y coordinación| arreglo `Carta mano[5]` en `Juego` | inserción/eliminación |
