#ifndef TIPOS_HPP
#define TIPOS_HPP
#include <iostream>
#include <string>
using namespace std;

struct Carta {
    int id;
    string nombre;
    int coste;
    int ataque;
    string efecto;
    
}
;
struct Enemigo {
    int id;
    string nombre;
    int vida;
    int ataque;
    int vidaActual;
}
;
ostream& operator<<(ostream& salida, const Enemigo& enemigo);
#endif
