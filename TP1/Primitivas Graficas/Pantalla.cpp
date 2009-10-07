#include "Pantalla.h"

Pantalla::Pantalla() {
	cargarPantalla();
}

Pantalla::~Pantalla() {
	while (!numeros.empty())
		numeros.pop();
}

void Pantalla::cargarPantalla() {
	pantalla.agregarVertice(35,90);
	pantalla.agregarVertice(25,100);
	pantalla.agregarVertice(25,140);
	pantalla.agregarVertice(35,150);
	pantalla.agregarVertice(65,150);
	pantalla.agregarVertice(75,140);
	pantalla.agregarVertice(75,100);
	pantalla.agregarVertice(65,90);
}

void Pantalla::dibujar() {
	pantalla.dibujarConRelleno();
}

