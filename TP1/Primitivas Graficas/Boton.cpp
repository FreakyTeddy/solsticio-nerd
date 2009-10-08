#include "Boton.h"

Boton::Boton() {
	apretado = false;
	esDDA = true;
	cargarVertices();
}

Boton::~Boton() {}

void Boton::apretar() {
	apretado = true;
}

void Boton::soltar() {
	apretado = false;
}

void Boton::dibujar(Numero *numero, MatrizTrans2D &matTrans) {

	//luz arriba
	if (apretado)
		glColor3f(0.55,0.55,0.55);
	else
		glColor3f(0.99,0.99,0.99);
	sombra[0].dibujarConRelleno(matTrans);

	//luz derecha
	if (apretado)
		glColor3f(0.66,0.66,0.66);
	else
		glColor3f(0.95,0.95,0.95);
	sombra[1].dibujarConRelleno(matTrans);

	//sombra abajo
	glColor3f(0.6,0.6,0.6);
	sombra[2].dibujarConRelleno(matTrans);

	//sombra derecha
	glColor3f(0.7,0.7,0.7);
	sombra[3].dibujarConRelleno(matTrans);

	if (apretado)
		glColor3f(0.50,0.50,0.50);
	else
		glColor3f(0.90,0.90,0.90);
	centro.dibujarConRelleno(matTrans);
numero = NULL;

	if(numero != NULL) {
		if(apretado)
			glColor3f(1.0,1.0,0);
		else
			glColor3f(0,0.5,1.0);
		
		//escalar numero
		
		Vertice fixedPt; // centro del poligono
		fixedPt.x= 50;
		fixedPt.y= 50;
		matTrans.scale2D(0.3, 0.34, fixedPt);
		numero->dibujarContorno(esDDA, matTrans);
	}
}

void Boton::cargarVertices() {

	//cuadrado de fondo
	centro.agregarVertice(20,70);
	centro.agregarVertice(80,70);
	centro.agregarVertice(80,30);
	centro.agregarVertice(20,30);
	centro.setDimensiones(100,100);

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

	for (int i=0; i<4;i++)
		sombra[i].setDimensiones(100,100);

}

void Boton::setDDA(bool dda) {
	this->esDDA = dda;
}
