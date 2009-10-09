#include "Pantalla.h"

Pantalla::Pantalla() {
	cargarPantalla();
	max = 12; //VER!!
}

Pantalla::~Pantalla() {
	limpiar();
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

	pantalla.setDimensiones(0,0);
}

void Pantalla::limpiar() {
	while (!numeros.empty())
		numeros.pop();
}

void Pantalla::agregarNumero(Numero *numero) {
	if (numeros.size() == max)
		numeros.pop();

	numeros.push(numero);
}

void Pantalla::dibujar(	MatrizTrans2D &matTrans) {

	glColor3f(0.9,0.9,0.9);
	pantalla.dibujarConRelleno(matTrans);

	//dibujo de numeros
	MatrizTrans2D matTransNumero;
	Vertice fixedPt; // centro del poligono
	fixedPt.x= 50;
	fixedPt.y= 50;

	float x0 = -150;
	float y0 = 50;
	int tam = numeros.size(), i=0;
	Numero *num;

	for (int j=0; j<=2;j++){
		for (int k=0; k<4;k++) {

			//MUGRE!! XD
			if (i == tam)
				break;

			matTransNumero.translate2D(x0+(100*k), y0-(200*j));
			matTransNumero.scale2D(0.1, 0.1, fixedPt);
			matTransNumero.preMultiply(matTrans);

			//obtengo el frente y lo acolo
			num = numeros.front();
			numeros.pop();
			numeros.push(num);

			glColor3f(0,0.8,0.9);
			num->dibujarConRelleno(matTransNumero);

			matTransNumero.loadIdentity();
			i++;
		}
	}
}

