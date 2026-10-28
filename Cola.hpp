#ifndef COLA_HPP
#define COLA_HPP
#include "Tipos.hpp"
struct tNodoCola {
    Enemigo dato;
    tNodoCola* sig;
}
;
class tCola {
    private:
    
    tNodoCola* frente;
    tNodoCola* fin;
    
    int tam;
    
    public:
    tCola();
    ~tCola();
    
    void encolar(const Enemigo& enemigo);
    void desencolar();
    
    Enemigo frenteValue() const;
    Enemigo& frenteRef();
    
    bool vacia() const;
    
    int tamanio() const;
    
    void clear();
}
;
#endif
