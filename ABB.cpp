#include "ABB.hpp"
ostream& operator<<(ostream& s,const Enemigo& e) {
    s<<e.id<<" "<<e.nombre<<" vida="<<e.vida<<" atk="<<e.ataque;
    return s;
}
tABB::tABB():raiz(NULL),tam(0) {
}
tABB::~tABB() {
    clear();
}
bool tABB::insertar(const Enemigo& d) {
    return insertar(raiz,d);
}
bool tABB::insertar(tNodoABB*& n,const Enemigo& d) {
    if(!n) {
        n=new tNodoABB;
        n->id=d.id;
        n->dato=d;
        n->izq=n->der=NULL;
        ++tam;
        return true;
    }
    if(d.id==n->id)return false;
    if(d.id<n->id)return insertar(n->izq,d);
    return insertar(n->der,d);
}
bool tABB::buscar(int id,Enemigo& out)const {
    return buscar(raiz,id,out);
}
bool tABB::buscar(tNodoABB* n,int id,Enemigo& out)const {
    if(!n)return false;
    if(id==n->id) {
        out=n->dato;
        return true;
    }
    return id<n->id?buscar(n->izq,id,out):buscar(n->der,id,out);
}
bool tABB::vacio()const {
    return tam==0;
}
int tABB::tamanio()const {
    return tam;
}
void tABB::inOrden(ostream& s)const {
    inOrden(raiz,s,0);
}
void tABB::inOrden(tNodoABB* n,ostream& s,int)const {
    if(!n)return;
    inOrden(n->izq,s,0);
    s<<"  "<<n->dato<<'\n';
    inOrden(n->der,s,0);
}
void tABB::clear(tNodoABB*& n) {
    if(!n)return;
    clear(n->izq);
    clear(n->der);
    delete n;
    n=NULL;
}
void tABB::clear() {
    clear(raiz);
    tam=0;
}
