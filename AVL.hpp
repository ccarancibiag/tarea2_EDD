#ifndef AVL_HPP
#define AVL_HPP
#include "Tipos.hpp"
struct tNodoAVL {
    int id;
    Carta dato;
    int altura;
    tNodoAVL* izq;
    tNodoAVL* der;
}
;
class tAVL {
    private:
    
    tNodoAVL* raiz;
    
    int tam;
    int altura(tNodoAVL* nodo) const;
    int factorBalance(tNodoAVL* nodo) const;
    
    tNodoAVL* rotDer(tNodoAVL* nodo);
    tNodoAVL* rotIzq(tNodoAVL* nodo);
    tNodoAVL* rotIzqDer(tNodoAVL* nodo);
    tNodoAVL* rotDerIzq(tNodoAVL* nodo);
    tNodoAVL* insertar(tNodoAVL* nodo, const Carta& carta,
    
    bool& insertada);
    bool buscar(tNodoAVL* nodo, int id, Carta& out) const;
    
    void preOrden(tNodoAVL* nodo, ostream& salida,
    
    int profundidad, bool& primero) const;
    
    void inOrden(tNodoAVL* nodo, ostream& salida,
    
    int profundidad, bool& primero) const;
    
    void clear(tNodoAVL* nodo);
    
    public:
    tAVL();
    ~tAVL();
    
    bool insertar(const Carta& carta);
    bool buscar(int id, Carta& out) const;
    
    int tamanio() const;
    
    void exportar(ostream& salida) const;
    void clear();
}
;
#endif
