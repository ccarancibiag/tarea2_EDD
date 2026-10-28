#include "Cola.hpp"
tCola::tCola() : frente(NULL), fin(NULL), tam(0) {
}
tCola::~tCola() {
    clear();
}
void tCola::encolar(const Enemigo& e) {
    tNodoCola* n=new tNodoCola;
    n->dato=e;
    n->sig=NULL;
    if(fin) fin->sig=n;
    else frente=n;
    fin=n;
    ++tam;
}
void tCola::desencolar() {
    if(!frente) return;
    tNodoCola* n=frente;
    frente=frente->sig;
    delete n;
    --tam;
    if(!frente) fin=NULL;
}
Enemigo tCola::frenteValue() const {
    return frente->dato;
}
Enemigo& tCola::frenteRef() {
    return frente->dato;
}
bool tCola::vacia() const {
    return tam==0;
}
int tCola::tamanio() const {
    return tam;
}
void tCola::clear() {
    while(frente) desencolar();
}
