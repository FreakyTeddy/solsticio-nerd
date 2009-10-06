#include "Boton.h"

Boton::Boton() {
	apretado = false;
	numero = NULL;
	cargarVertices();
	centro.setRelleno(true);
	centro.setContorno(false);
	for (int i=0;i<4;i++) {
		sombra[i].setRelleno(true);
		sombra[i].setContorno(false);
	}
}

Boton::~Boton() {}

void Boton::apretar() {
	apretado = true;
}

void Boton::soltar() {
	apretado = false;
}

void Boton::setNumero(Numero *num) {
	numero = num;
}

void Boton::dibujar() {

	//TODO color y matrices!!!!!

	//luz arriba
	glColor3f(0.99,0.99,0.99);
	sombra[0].dibujar();

	//luz derecha
	glColor3f(0.95,0.95,0.95);
	sombra[1].dibujar();

	//sombra abajo
	glColor3f(0.6,0.6,0.6);
	sombra[2].dibujar();

	//sombra derecha
	glColor3f(0.7,0.7,0.7);
	sombra[3].dibujar();

	glColor3f(0.90,0.90,0.90);
	centro.dibujar();

	if (numero != NULL) {//VER esto no deberia pasar nunca
		numero->setRelleno(true);
		glColor3f(0,0.5,1.0);
		numero->setContorno(true);
		//trasladar numero
		numero->dibujar();
	}
}

void Boton::cargarVertices() {

	//cuadrado de fondo
	centro.agregarVertice(20,70);
	centro.agregarVertice(80,70);
	centro.agregarVertice(80,30);
	centro.agregarVertice(20,30);

	//sombra
	sombra[0].agregarVertice(15,75);
	sombra[0].agregarVertice(20,80);
	sombra[0].agregarVertice(80,80);
	sombra[0].agregarVertice(85,75);
	sombra[0].agregarVertice(80,70);
	sombra[0].agregarVertice(20,70);

	sombra[1].agregarVertice(80,70);
	sombra[1].agregarVertice(85,75);
	sombra[1].agregarVertice(90,70);
	sombra[1].agregarVertice(90,30);
	sombra[1].agregarVertice(85,25);
	sombra[1].agregarVertice(80,30);

	sombra[2].agregarVertice(80,30);
	sombra[2].agregarVertice(85,25);
	sombra[2].agregarVertice(80,20);
	sombra[2].agregarVertice(20,20);
	sombra[2].agregarVertice(15,25);
	sombra[2].agregarVertice(20,30);

	sombra[3].agregarVertice(20,30);
	sombra[3].agregarVertice(15,25);
	sombra[3].agregarVertice(10,30);
	sombra[3].agregarVertice(10,70);
	sombra[3].agregarVertice(15,75);
	sombra[3].agregarVertice(20,70);

}
