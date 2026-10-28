CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = tarea2
SOURCES = main.cpp Pila.cpp Cola.cpp ABB.cpp AVL.cpp Juego.cpp

all: $(TARGET)

$(TARGET): $(SOURCES) Tipos.hpp Pila.hpp Cola.hpp ABB.hpp AVL.hpp Juego.hpp
	$(CXX) $(SOURCES) -o $(TARGET) $(CXXFLAGS)

run: $(TARGET)
	@if [ -z "$(INICIO)" ] || [ -z "$(COMANDOS)" ] || [ -z "$(SALIDA)" ]; then echo 'Uso: make run INICIO=inicio.txt COMANDOS=partida.txt SALIDA=arbol.txt'; exit 1; fi
	./$(TARGET) "$(INICIO)" "$(COMANDOS)" "$(SALIDA)"

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean run
