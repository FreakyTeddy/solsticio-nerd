SOURCES=Controlador/callbacksTeclado.cpp\
	Primitivas\ Graficas/Boton.cpp\
	Primitivas\ Graficas/Botonera.cpp\
	Primitivas\ Graficas/Celular.cpp\
	Primitivas\ Graficas/Numero.cpp\
	Primitivas\ Graficas/Pantalla.cpp\
	Primitivas\ Graficas/Poligono.cpp\
	Primitivas\ Graficas/Vertice.cpp\
	Primitivas\ Graficas/liang-barsky.cpp\
	Primitivas\ Graficas/Linea/linea.cpp\
	Primitivas\ Graficas/Relleno/relleno.cpp\
	Primitivas\ Graficas/Transformacion2D/tranformacion2D.cpp\
	Primitivas\ Graficas/Transformacion2D/Matriz/matriz.cpp\
	Primitivas\ Graficas/Transformacion2D/Matriz/matrizTrans2D.cpp\

TESTSOURCES=Primitivas\ Graficas/testClippingLB.cpp\
	Primitivas\ Graficas/testcel.cpp\
	Primitivas\ Graficas/Relleno/pruebaRelleno.cpp\
	Primitivas\ Graficas/Transformacion2D/pruebaTransformacion2D.cpp

MAIN=solsticio.cpp

CFLAGS=-g -lGL -lGLU -lglut
CC=g++
EXECUTABLE=Tp1

OBJECTS=$(SOURCES:.cpp=.o)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
MAINSOURCES=$(SOURCES) $(MAIN)
MAINOBJECTS=$(MAIN:.cpp=.o) $(OBJECTS)
ALLOBJECTS=$(MAINOBJECTS) $(TESTOBJECTS)
TESTEXEC=$(TESTSOURCES:.cpp=)

all: $(MAINSOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(MAINOBJECTS)
	$(CC) $(CFLAGS) $(MAINOBJECTS) -o $@

.cpp.o:
	$(CC) -c "$<" -o "$@"

test: $(TESTSOURCES) $(TESTEXEC)

$(TESTEXEC): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) "$@.o" -o "$@"

clean:
	rm -f $(ALLOBJECTS) $(EXECUTABLE) $(TESTEXEC)