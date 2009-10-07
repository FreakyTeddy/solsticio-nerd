#include "Boton.h"

Boton::Boton() {
	apretado = false;
	esDDA = true;
	numero = NULL;
	cargarVertices();
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

	//matrices!!!!!

	//luz arriba
	glColor3f(0.99,0.99,0.99);
	sombra[0].dibujarConRelleno();

	//luz derecha
	glColor3f(0.95,0.95,0.95);
	sombra[1].dibujarConRelleno();

	//sombra abajo
	glColor3f(0.6,0.6,0.6);
	sombra[2].dibujarConRelleno();

	//sombra derecha
	glColor3f(0.7,0.7,0.7);
	sombra[3].dibujarConRelleno();

	glColor3f(0.90,0.90,0.90);
	centro.dibujarConRelleno();

	if (numero != NULL) {//VER esto no deberia pasar nunca
		glColor3f(0,0.5,1.0);
		//trasladar numero
		numero->dibujarContorno(esDDA);//TODO
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

void Boton::setDDA(bool dda) {
	this->esDDA = dda;
}
