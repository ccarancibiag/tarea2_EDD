#include "AVL.hpp"
tAVL::tAVL():raiz(NULL),tam(0) {
}
tAVL::~tAVL() {
    clear();
}
int tAVL::altura(tNodoAVL* n)const {
    return n?n->altura:-1;
}
int tAVL::factorBalance(tNodoAVL* n)const {
    return n?altura(n->der)-altura(n->izq):0;
}
tNodoAVL* tAVL::rotDer(tNodoAVL* n) {
    tNodoAVL* x=n->izq;
    tNodoAVL* t=x->der;
    x->der=n;
    n->izq=t;
    n->altura=1+(altura(n->izq)>altura(n->der)?altura(n->izq):altura(n->der));
    x->altura=1+(altura(x->izq)>altura(x->der)?altura(x->izq):altura(x->der));
    return x;
}
tNodoAVL* tAVL::rotIzq(tNodoAVL* n) {
    tNodoAVL* x=n->der;
    tNodoAVL* t=x->izq;
    x->izq=n;
    n->der=t;
    n->altura=1+(altura(n->izq)>altura(n->der)?altura(n->izq):altura(n->der));
    x->altura=1+(altura(x->izq)>altura(x->der)?altura(x->izq):altura(x->der));
    return x;
}
tNodoAVL* tAVL::rotIzqDer(tNodoAVL* n) {
    n->izq=rotIzq(n->izq);
    return rotDer(n);
}
tNodoAVL* tAVL::rotDerIzq(tNodoAVL* n) {
    n->der=rotDer(n->der);
    return rotIzq(n);
}
bool tAVL::insertar(const Carta& c) {
    bool ok=false;
    raiz=insertar(raiz,c,ok);
    if(ok)++tam;
    return ok;
}
tNodoAVL* tAVL::insertar(tNodoAVL* n,const Carta& c,bool& ok) {
    if(!n) {
        n=new tNodoAVL;
        n->id=c.id;
        n->dato=c;
        n->altura=0;
        n->izq=n->der=NULL;
        ok=true;
        return n;
    }
    if(c.id==n->id)return n;
    if(c.id<n->id)n->izq=insertar(n->izq,c,ok);
    else n->der=insertar(n->der,c,ok);
    if(!ok)return n;
    n->altura=1+(altura(n->izq)>altura(n->der)?altura(n->izq):altura(n->der));
    int fb=factorBalance(n);
    if(fb < -1) {
        if(factorBalance(n->izq)>0)return rotIzqDer(n);
        return rotDer(n);
    }
    if(fb>1) {
        if(factorBalance(n->der)<0)return rotDerIzq(n);
        return rotIzq(n);
    }
    return n;
}
bool tAVL::buscar(int id,Carta& out)const {
    return buscar(raiz,id,out);
}
bool tAVL::buscar(tNodoAVL* n,int id,Carta& out)const {
    if(!n)return false;
    if(id==n->id) {
        out=n->dato;
        return true;
    }
    return id<n->id?buscar(n->izq,id,out):buscar(n->der,id,out);
}
int tAVL::tamanio()const {
    return tam;
}
void tAVL::preOrden(tNodoAVL* n,ostream& s,int d,bool& primero)const {
    if(!n)return;
    if(!primero)s<<' ';
    primero=false;
    s<<n->id<<'('<<d<<')';
    preOrden(n->izq,s,d+1,primero);
    preOrden(n->der,s,d+1,primero);
}
void tAVL::inOrden(tNodoAVL* n,ostream& s,int d,bool& primero)const {
    if(!n)return;
    inOrden(n->izq,s,d+1,primero);
    if(!primero)s<<' ';
    primero=false;
    s<<n->id<<'('<<d<<')';
    inOrden(n->der,s,d+1,primero);
}
void tAVL::exportar(ostream& s)const {
    bool primero=true;
    preOrden(raiz,s,0,primero);
    s<<'\n';
    primero=true;
    inOrden(raiz,s,0,primero);
    s<<'\n';
}
void tAVL::clear(tNodoAVL* n) {
    if(!n)return;
    clear(n->izq);
    clear(n->der);
    delete n;
}
void tAVL::clear() {
    clear(raiz);
    raiz=NULL;
    tam=0;
}
