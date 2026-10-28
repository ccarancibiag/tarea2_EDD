#ifndef PILA_HPP
#define PILA_HPP
#include "Tipos.hpp"
struct tNodoPila {
    Carta dato;
    tNodoPila* sig;
}
;
class tPila {
    private:
    tNodoPila* tope;
    int tam;
    public:
    tPila();
    ~tPila();
    void push(const Carta& carta);
    void pop();
    Carta topValue() const;
    bool vacia() const;
    int tamanio() const;
    void clear();
}
;
#endif
