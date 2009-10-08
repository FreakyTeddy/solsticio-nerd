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
	
	fondo.setDimensiones(100,100);
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
		
	
	float x0 = 260;
	float y0 = 270;
	int i=1;
	
	//Dibujo boton
	
	for (int j=2; j>=0;j--){
		for (int k=0; k<3;k++) {
			
			matTransBoton.scale2D(0.15, 0.15, fixedPt); //escalo el boton			
			matTransBoton.translate2D(x0+(15*k), y0+(15*j));
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
	matTransBoton.preMultiply(matTrans);
	matTransBoton.translate2D(x0+15, y0-15);
	matTransBoton.scale2D(0.15,0.15, fixedPt);
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