
#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "Tipos.hpp"
#include "Pila.hpp"
#include "Cola.hpp"
#include "ABB.hpp"
#include "AVL.hpp"

class Juego {
private:
    tPila mazo;
    tPila descarte;
    tCola horda;
    tABB bestiario;
    tAVL grimorio;

    Carta mano[5];
    int tamMano;

    int vidaJugador;
    int energia;
    int turno;

    bool derrota;
    bool victoria;

    bool cargarInicio(const string& ruta);
    void eliminarMano(int pos);
    void comprobarVictoria(ostream& salida);

public:
    Juego();
    ~Juego();

    bool cargar(const string& ruta);

    bool robar();
    bool jugar(int pos);
    bool descartar(int pos);
    bool atacar();

    void imprimirMano(ostream& salida) const;
    void imprimirHorda(ostream& salida);
    void imprimirBestiario(ostream& salida) const;

    void guardar(const string& ruta) const;
    void ejecutarComandos(
        const string& ruta,
        const string& salida
    );
};

#endif
