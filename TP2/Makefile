SOURCES=Primitivas\ Graficas/Curva/Curva.cpp \
	Controlador/Controlador.cpp \
	Imagenes/Imagen.cpp 


TESTSOURCES=Primitivas\ Graficas/Curva/TestCurvas.cpp \
	Imagenes/TestImagen.cpp 

MAIN=mainPrincipal.cpp

CFLAGS+=-g -lGL -lGLU -lglut `pkg-config --cflags --libs sdl` -lSDL_image
CC=g++
EXECUTABLE=Tp2

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
	$(CC) $(CFLAGS) -c "$<" -o "$@"

test: $(TESTSOURCES) $(TESTEXEC)

$(TESTEXEC): $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) "$@.o" -o "$@"

clean:
	rm -f $(ALLOBJECTS) $(EXECUTABLE) $(TESTEXEC)
