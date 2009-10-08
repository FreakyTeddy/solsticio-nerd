#include "Pantalla.h"

Pantalla::Pantalla() {
	cargarPantalla();
}

Pantalla::~Pantalla() {
	while (!numeros.empty())
		numeros.pop();
}

void Pantalla::cargarPantalla() {
	pantalla.agregarVertice(70,5);
	pantalla.agregarVertice(75,10);
	pantalla.agregarVertice(75,60);
	pantalla.agregarVertice(70,65);
	pantalla.agregarVertice(30,65);
	pantalla.agregarVertice(25,60);
	pantalla.agregarVertice(25,10);
	pantalla.agregarVertice(30,5);

	pantalla.setDimensiones(100,100);
}

void Pantalla::dibujar(	MatrizTrans2D &matTrans) {
	glColor3f(0.9,0.9,0.9);
	pantalla.dibujarConRelleno(matTrans);
}

