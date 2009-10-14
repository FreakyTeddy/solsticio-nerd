SOURCES=Primitivas\ Graficas/Curva/Curva.cpp


TESTSOURCES=Primitivas\ Graficas/Curva/pruebaCurva.cpp

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