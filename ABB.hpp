#ifndef ABB_HPP
#define ABB_HPP
#include "Tipos.hpp"
struct tNodoABB {
    int id;
    Enemigo dato;
    tNodoABB* izq;
    tNodoABB* der;
}
;
class tABB {
    private:

    tNodoABB* raiz;
    
    int tam;
    
    bool insertar(tNodoABB*& nodo, const Enemigo& dato);
    bool buscar(tNodoABB* nodo, int id, Enemigo& out) const;
    
    void inOrden(tNodoABB* nodo, ostream& salida,
    
    int profundidad) const;
    
    void clear(tNodoABB*& nodo);
    
    public:
    tABB();
    ~tABB();
    
    bool insertar(const Enemigo& dato);
    bool buscar(int id, Enemigo& out) const;
    bool vacio() const;
    
    int tamanio() const;
    
    void inOrden(ostream& salida) const;
    void clear();
}
;
#endif
