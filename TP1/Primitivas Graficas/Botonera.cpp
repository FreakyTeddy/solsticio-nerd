#include "Botonera.h"

Botonera::Botonera() {
	
	b_apretado=-1;
	
	fondo.agregarVertice(70,5);
	fondo.agregarVertice(75,10);
	fondo.agregarVertice(75,60);
	fondo.agregarVertice(70,65);
	fondo.agregarVertice(30,65);
	fondo.agregarVertice(25,60);
	fondo.agregarVertice(25,10);
	fondo.agregarVertice(30,5);
	
	fondo.setDimensiones(0,0);
}

Botonera::~Botonera() {
}

void Botonera::setNumeros(Numero **numeros) {
	this->numero = numeros;
}

void Botonera::dibujar(MatrizTrans2D &matTrans) {
	
	glColor3f(0.1,0.1,0.1);
	fondo.dibujarConRelleno(matTrans);
	
	//trasladar y dibujar cada boton con su numero correspondiente
	MatrizTrans2D matTransBoton;
	Vertice fixedPt; // centro del poligono
	fixedPt.x= 50;
	fixedPt.y= 50;
		
	
	float x0 = -110;
	float y0 = -150;
	int i=1;
	
	//Dibujo boton
	
	for (int j=2; j>=0;j--){
		for (int k=0; k<3;k++) {

			matTransBoton.translate2D(x0+(110*k), y0+(80*j));			
			matTransBoton.scale2D(0.15, 0.15, fixedPt); //escalo el boton
			matTransBoton.preMultiply(matTrans);
			
			if (i == b_apretado)
				boton.apretar();			
			
			boton.dibujar(numero[i], matTransBoton);	
			
			boton.soltar();
			matTransBoton.loadIdentity();	
			i++;			
		}
	}
	
	//dibujo el cero

	matTransBoton.translate2D(x0+110, y0-80);
	matTransBoton.scale2D(0.15,0.15, fixedPt);
	matTransBoton.preMultiply(matTrans);
	if (0 == b_apretado)
			boton.apretar();
	boton.dibujar(numero[0], matTransBoton);	
	boton.soltar();
	
}

void Botonera::apretarBoton(int boton) {
	b_apretado = boton;
}

void Botonera::cambiarLinea(char tipo) {
	
	if('D')
		boton.setDDA(true);
	else
		boton.setDDA(false);		
}	
