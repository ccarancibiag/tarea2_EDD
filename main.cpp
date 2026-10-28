#include "Juego.hpp"
#include <iostream>
#include <fstream>
int main(int argc,char* argv[]) {
    if(argc!=4) {
        std::cerr<<"Uso: ./tarea2 <archivo_inicio.txt> <archivo_comandos.txt> <archivo_salida.txt>\n";
        return 1;
    }
    std::ifstream comandos(argv[2]);
    if(!comandos) {
        std::cerr<<"No se puede abrir archivo de comandos: "<<argv[2]<<'\n';
        return 1;
    }
    comandos.close();
    Juego juego;
    if(!juego.cargar(argv[1]))return 2;
    juego.ejecutarComandos(argv[2],argv[3]);
    return 0;
}
