#include "Juego.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <fstream>

static string trim(const string& s) {
    size_t a=0,b=s.size();
    while(a<b&&isspace((unsigned char)s[a]))++a;
    while(b>a&&isspace((unsigned char)s[b-1]))--b;
    return s.substr(a,b-a);
}
static bool entero(const string& s,int& v) {
    if(s.empty())return false;
    char* e=NULL;
    long x=strtol(s.c_str(),&e,10);
    if(*e||e==s.c_str()||x < -2147483648L || x > 2147483647L)return false;
    v=(int)x;
    return true;
}
static bool posicionValidaSintaxis(const string& s,int& v) {
    if(s.empty())return false;
    if(s.size()>1&&s[0]=='0')return false;
    for(size_t i=0;i<s.size();++i)if(s[i]<'0'||s[i]>'9')return false;
    return entero(s,v);
}
static int campos(const string& s,string out[],int max) {
    int n=0;
    size_t a=0;
    while(true) {
        size_t p=s.find('|',a);
        if(n>=max)return max+1;
        out[n++]=trim(s.substr(a,p==string::npos?string::npos:p-a));
        if(p==string::npos)break;
        a=p+1;
    }
    return n;
}
Juego::Juego():tamMano(0),vidaJugador(30),energia(3),turno(0),derrota(false),victoria(false) {
}
Juego::~Juego() {
}
bool Juego::cargar(const string& r) {
    return cargarInicio(r);
}
bool Juego::cargarInicio(const string& ruta) {
    ifstream f(ruta.c_str());
    if(!f) {
        cout<<"[CARGA] ERROR\n";
        return false;
    }
    string linea,seccion="",header="";
    bool vistas[4]= {
        false,false,false,false
    }
    ;
    bool ordenMalo=false,ordenMaloHorda=false;
    int num=0;
    while(getline(f,linea)) {
        ++num;
        linea=trim(linea);
        if(linea.empty()||linea[0]=='#')continue;
        if(linea[0]=='@') {
            if(!seccion.empty()&&header.empty()) {
                cout<<"[CARGA] ERROR\n";
                return false;
            }
            seccion=linea;
            int ix=seccion=="@GRIMORIO"?0:seccion=="@BESTIARIO"?1:seccion=="@MAZO"?2:seccion=="@HORDA"?3:-1;
            if(ix<0||vistas[ix]) {
                cout<<"[CARGA] ERROR\n";
                return false;
            }
            if(ix==2&&!vistas[0])ordenMalo=true;
            if(ix==3&&!vistas[1])ordenMaloHorda=true;
            vistas[ix]=true;
            header="";
            continue;
        }
        if(seccion.empty()) {
            cout<<"[CARGA] ERROR\n";
            return false;
        }
    if(header.empty()) {
    header=linea;

    string h[5];
    int nh=campos(linea,h,5);
    bool valido=false;

    if(seccion=="@GRIMORIO") {
        valido=(nh==5 &&
                h[0]=="ID" &&
                h[1]=="NOMBRE" &&
                h[2]=="COSTE" &&
                h[3]=="ATAQUE" &&
                h[4]=="EFECTO");
    }
    else if(seccion=="@BESTIARIO") {
        valido=(nh==4 &&
                h[0]=="ID" &&
                h[1]=="NOMBRE" &&
                h[2]=="VIDA" &&
                h[3]=="ATAQUE");
    }
    else if(seccion=="@MAZO" || seccion=="@HORDA") {
        valido=(nh==1 && h[0]=="ID");
    }

    if(!valido) {
        cout<<"[CARGA] ERROR\n";
        return false;
    }

    continue;
}
        string c[6];
        int n=campos(linea,c,6),id;
        if(n<1||!entero(c[0],id)||id<1||id>9999) {
            cout<<"[CARGA] ERROR\n";
            return false;
        }
        if(seccion=="@GRIMORIO") {
            int cost,atk;
            if(n!=5||c[1].empty()||c[1].size()>31||!entero(c[2],cost)||!entero(c[3],atk)||cost<0||cost>9||atk<0||atk>99||(c[4]!="NINGUNO"&&c[4]!="FUEGO"&&c[4]!="HIELO"&&c[4]!="VENENO"&&c[4]!="CURACION")) {
                cout<<"[CARGA] ERROR\n";
                return false;
            }
            Carta x;
            x.id=id;
            x.nombre=c[1];
            x.coste=cost;
            x.ataque=atk;
            x.efecto=c[4];
            if(!grimorio.insertar(x))cerr<<"[CARGA] ID de carta duplicado: "<<id<<'\n';
        }
        else if(seccion=="@BESTIARIO") {
            int hp,atk;
            if(n!=4||c[1].empty()||c[1].size()>31||!entero(c[2],hp)||!entero(c[3],atk)||hp<1||hp>9999||atk<0||atk>999) {
                cout<<"[CARGA] ERROR\n";
                return false;
            }
            Enemigo e;
            e.id=id;
            e.nombre=c[1];
            e.vida=hp;
            e.ataque=atk;
            e.vidaActual=hp;
            if(!bestiario.insertar(e))cerr<<"[CARGA] Enemigo duplicado: "<<id<<'\n';
        }
        else if(seccion=="@MAZO") {
            if(n!=1) {
                cout<<"[CARGA] ERROR\n";
                return false;
            }
            Carta x;
            if(!grimorio.buscar(id,x))cerr<<"[CARGA] Referencia de carta inexistente: "<<id<<'\n';
            else mazo.push(x);
        }
        else {
            if(n!=1) {
                cout<<"[CARGA] ERROR\n";
                return false;
            }
            Enemigo e;
            if(!bestiario.buscar(id,e))cerr<<"[CARGA] Referencia de enemigo inexistente: "<<id<<'\n';
            else {
                e.vidaActual=e.vida;
                horda.encolar(e);
            }
        }
    }
    if(!seccion.empty()&&header.empty()) {
        cout<<"[CARGA] ERROR\n";
        return false;
    }
    if((ordenMalo&&vistas[0])||(ordenMaloHorda&&vistas[1])) {
        cout<<"[CARGA] ERROR\n";
        return false;
    }
    return true;
}
bool Juego::robar() {
    if(derrota)return false;
    if(tamMano==5) {
        cout<<"ROBAR -> MANO_LLENA\n";
        return false;
    }
    if(mazo.vacia()&&!descarte.vacia()) {
        cout<<"RECICLAJE: descarte -> mazo\n";
        while(!descarte.vacia()) {
            Carta c=descarte.topValue();
            descarte.pop();
            mazo.push(c);
        }
    }
    if(mazo.vacia()) {
        cout<<"ROBAR -> MAZO_VACIO\n";
        return false;
    }
    Carta c=mazo.topValue();
    mazo.pop();
    mano[tamMano++]=c;
    cout<<"ROBAR -> "<<c.id<<" (mano="<<tamMano<<")\n";
    return true;
}
void Juego::eliminarMano(int p) {
    for(int i=p-1;i<tamMano-1;++i)mano[i]=mano[i+1];
    --tamMano;
}
void Juego::comprobarVictoria(ostream& s) {
    if(!victoria&&horda.vacia()) {
        victoria=true;
        s<<"VICTORIA\n";
    }
}
bool Juego::jugar(int p) {
    if(derrota)return false;
    if(p<1||p>tamMano) {
        cout<<"JUGAR "<<p<<" -> POS_INVALIDA\n";
        return false;
    }
    Carta c=mano[p-1];
    if(c.coste>energia) {
        cout<<"JUGAR "<<p<<" -> ENERGIA_INSUFICIENTE\n";
        return false;
    }
    energia-=c.coste;
    eliminarMano(p);
    descarte.push(c);
    int muerto=-1;
    if(!horda.vacia()&&c.ataque>0) {
        Enemigo& e=horda.frenteRef();
        e.vidaActual-=c.ataque;
        if(e.vidaActual<0)e.vidaActual=0;
        if(e.vidaActual==0) {
            muerto=e.id;
            horda.desencolar();
        }
    }
    int cura=0;
    if(c.efecto=="CURACION") {
        int antes=vidaJugador;
        vidaJugador+=3;
        if(vidaJugador>30)vidaJugador=30;
        cura=vidaJugador-antes;
    }
    cout<<"JUGAR "<<p<<" -> "<<c.id<<" (energia="<<energia<<")";
    if(muerto!=-1)cout<<" MATA "<<muerto;
    if(cura>0)cout<<" CURA +"<<cura;
    cout<<'\n';
    comprobarVictoria(cout);
    return true;
}
bool Juego::descartar(int p) {
    if(derrota)return false;
    if(p<1||p>tamMano) {
        cout<<"DESCARTAR "<<p<<" -> POS_INVALIDA\n";
        return false;
    }
    Carta c=mano[p-1];
    eliminarMano(p);
    descarte.push(c);
    cout<<"DESCARTAR "<<p<<" -> "<<c.id<<'\n';
    return true;
}
bool Juego::atacar() {
    if(derrota)return false;
    if(horda.vacia()) {
        cout<<"ATACAR -> HORDA_VACIA\n";
        comprobarVictoria(cout);
        return false;
    }
    Enemigo& e=horda.frenteRef();
    int dmg=e.vidaActual<4?e.vidaActual:4;
    e.vidaActual-=dmg;
    ++turno;
    energia=3;
    cout<<"ATACAR -> dmg="<<dmg<<" turno="<<turno;
    if(e.vidaActual==0) {
        int id=e.id;
        horda.desencolar();
        cout<<" MATA "<<id<<'\n';
        comprobarVictoria(cout);
    }
    else {
        int contra=e.ataque<vidaJugador?e.ataque:vidaJugador;
        vidaJugador-=contra;
        cout<<" CONTRAATAQUE -"<<contra<<" (hp="<<vidaJugador<<")\n";
        if(vidaJugador==0&&!derrota) {
            derrota=true;
            cout<<"DERROTA\n";
        }
    }
    return true;
}
void Juego::imprimirMano(ostream& s)const {
    s<<"MANO:";
    if(!tamMano) {
        s<<" (vacia)\n";
        return;
    }
    for(int i=0;i<tamMano;++i)s<<' '<<mano[i].id;
    s<<'\n';
}
void Juego::imprimirHorda(ostream& s) {
    s<<"HORDA:";
    int n=horda.tamanio();
    if(!n) {
        s<<" (vacia)\n";
        return;
    }
    for(int i=0;i<n;++i) {
        Enemigo e=horda.frenteValue();
        s<<' '<<e.id<<"(vida="<<e.vidaActual<<")";
        horda.desencolar();
        horda.encolar(e);
    }
    s<<'\n';
}
void Juego::imprimirBestiario(ostream& s)const {
    s<<"BESTIARIO (in-orden):\n";
    if(bestiario.vacio())s<<"(vacio)\n";
    else bestiario.inOrden(s);
}
void Juego::guardar(const string& ruta)const {
    ofstream f(ruta.c_str());
    if(!f) {
        cerr<<"No se pudo abrir archivo de salida: "<<ruta<<'\n';
        return;
    }
    grimorio.exportar(f);
    cout<<"GUARDADO "<<ruta<<'\n';
}
void Juego::ejecutarComandos(const string& ruta,const string& salida) {
    ifstream f(ruta.c_str());
    if(!f) {
        cerr<<"No se pudo abrir archivo de comandos: "<<ruta<<'\n';
        return;
    }
    string l;
    while(getline(f,l)) {
        l=trim(l);
        if(l.empty()||l[0]=='#')continue;
        istringstream ss(l);
        string cmd,arg,extra;
        ss>>cmd;
        for(size_t i=0;i<cmd.size();++i)cmd[i]=(char)toupper((unsigned char)cmd[i]);
        ss>>arg;
        ss>>extra;
        if(cmd=="ROBAR"&&arg.empty()&&extra.empty())robar();
        else if(cmd=="JUGAR"||cmd=="DESCARTAR") {
            int p;
            if(arg.empty()||!posicionValidaSintaxis(arg,p)||!extra.empty()) {
                cerr<<"Argumento invalido en comando "<<cmd<<'\n';
                continue;
            }
            if(cmd=="JUGAR")jugar(p);
            else descartar(p);
        }
        else if(cmd=="ATACAR"&&arg.empty()&&extra.empty())atacar();
        else if(cmd=="IMPRIMIR_MANO"&&arg.empty()&&extra.empty())imprimirMano(cout);
        else if(cmd=="IMPRIMIR_HORDA"&&arg.empty()&&extra.empty())imprimirHorda(cout);
        else if(cmd=="IMPRIMIR_BESTIARIO"&&arg.empty()&&extra.empty())imprimirBestiario(cout);
        else if(cmd=="IMPRIMIR_AVL"&&arg.empty()&&extra.empty()) {
            grimorio.exportar(cout);
        }
        else if(cmd=="GUARDAR") {
            if(!extra.empty()) {
                cerr<<"Argumentos de mas en GUARDAR\n";
                continue;
            }
            guardar(arg.empty()?salida:arg);
        }
        else cerr<<"Comando desconocido o argumentos invalidos: "<<l<<'\n';
    }
}
