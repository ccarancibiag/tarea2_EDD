#include "Pila.hpp"
tPila::tPila() : tope(NULL), tam(0) {
}
tPila::~tPila() {
    clear();
}
void tPila::push(const Carta& c) {
    tNodoPila* n = new tNodoPila;
    n->dato=c;
    n->sig=tope;
    tope=n;
    ++tam;
}
void tPila::pop() {
    if (!tope) return;
    tNodoPila* n=tope;
    tope=tope->sig;
    delete n;
    --tam;
}
Carta tPila::topValue() const {
    return tope->dato;
}
bool tPila::vacia() const {
    return tam==0;
}
int tPila::tamanio() const {
    return tam;
}
void tPila::clear() {
    while(tope) pop();
}
