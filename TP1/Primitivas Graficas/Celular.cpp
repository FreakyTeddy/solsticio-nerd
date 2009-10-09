#include "Celular.h"
#include <iostream>



Celular::Celular() {
	for (int i=0; i<10; i++) {
		numero[i] = new Numero(i);
	}
	botonera.setNumeros(numero);
	crearCarcasa();
	crearSombras();
}

Celular::~Celular() {
	for (int i=0; i<10; i++) {
		delete numero[i];
	}
}

void Celular::crearCarcasa() {

	cel.agregarVertice(55,0);
	cel.agregarVertice(47,4);
	cel.agregarVertice(45,10);
	cel.agregarVertice(45,65);
	cel.agregarVertice(47,71);
	cel.agregarVertice(58,75);
	cel.agregarVertice(55,80);
	cel.agregarVertice(47,84);
	cel.agregarVertice(45,90);
	cel.agregarVertice(45,150);
	cel.agregarVertice(47,156);
	cel.agregarVertice(55,160);
	cel.agregarVertice(105,160);
	cel.agregarVertice(113,156);
	cel.agregarVertice(115,150);
	cel.agregarVertice(115,90);
	cel.agregarVertice(112,84);
	cel.agregarVertice(104,80);
	cel.agregarVertice(102,75);
	cel.agregarVertice(112,71);
	cel.agregarVertice(115,65);
	cel.agregarVertice(115,10);
	cel.agregarVertice(112,4);
	cel.agregarVertice(105,0);
	cel.setDimensiones(0,0);
}

void Celular::crearSombras() {

	//sombra arriba
	sombra[0].agregarVertice(49,155);
	sombra[0].agregarVertice(47,152);
	sombra[0].agregarVertice(46,145);
	sombra[0].agregarVertice(46,90);
	sombra[0].agregarVertice(49,85);
	sombra[0].agregarVertice(51,84);
	sombra[0].agregarVertice(54,82);
	sombra[0].agregarVertice(51,86);
	sombra[0].agregarVertice(49,90);

	//sombra abajo
	sombra[1].agregarVertice(49,70);
	sombra[1].agregarVertice(47,69);
	sombra[1].agregarVertice(46,65);
	sombra[1].agregarVertice(46,10);
	sombra[1].agregarVertice(49,5);
	sombra[1].agregarVertice(51,4);
	sombra[1].agregarVertice(54,2);
	sombra[1].agregarVertice(51,6);
	sombra[1].agregarVertice(49,10);

	//sombra clara abajo
	sombra[2].agregarVertice(52,71);
	sombra[2].agregarVertice(49,70);
	sombra[2].agregarVertice(49,65);
	sombra[2].agregarVertice(49,10);
	sombra[2].agregarVertice(52,5);
	sombra[2].agregarVertice(54,4);
	sombra[2].agregarVertice(57,2);
	sombra[2].agregarVertice(54,6);
	sombra[2].agregarVertice(52,10);

	//sombra clara arriba
	sombra[3].agregarVertice(52,157);
	sombra[3].agregarVertice(49,154);
	sombra[3].agregarVertice(49,145);
	sombra[3].agregarVertice(49,90);
	sombra[3].agregarVertice(52,85);
	sombra[3].agregarVertice(54,84);
	sombra[3].agregarVertice(57,82);
	sombra[3].agregarVertice(54,86);
	sombra[3].agregarVertice(52,90);

	for (int i=0; i<4;i++)
		sombra[i].setDimensiones(160,160);

}

void Celular::dibujar() {
	//transformar
	 MatrizTrans2D matTrans;
	 Vertice fixed;  /* escala del celular */
	 fixed.x = 80;
	 fixed.y = 80;

	  matTrans.translate2D(-80,-80);
	
	 glColor3f(0.3,0.3,0.3);
	 cel.dibujarConRelleno(matTrans);

	 glColor3f(0.25,0.25,0.25);
	  sombra[1].dibujarConRelleno(matTrans);
	  sombra[0].dibujarConRelleno(matTrans);

	  glColor3f(0.28,0.28,0.28);
	  sombra[2].dibujarConRelleno(matTrans);
	  sombra[3].dibujarConRelleno(matTrans);

	 MatrizTrans2D matTransPantalla;

	 Vertice fixedPt; // centro del poligono
	 fixedPt.x= 50;
	 fixedPt.y= 50;
	 matTransPantalla.translate2D(-50,-35);
	 matTransPantalla.translate2D(0,40);
//	 matTransPantalla.preMultiply(matTrans);
	 pantalla.dibujar(matTransPantalla);
	

	 MatrizTrans2D matTransBotonera;
	 matTransBotonera.translate2D(-50,-35);
	 matTransBotonera.translate2D(0,-40);
	 botonera.dibujar(matTransBotonera);
}

void Celular::apretarBoton(int boton) {
	if (boton >=0){
		botonera.apretarBoton(boton);
		pantalla.agregarNumero(numero[boton]);
	}
}

void Celular::soltarBoton() {
	
	botonera.apretarBoton(-1);
}

void Celular::cambiarLinea(char tipo) {
	
	botonera.cambiarLinea(tipo);
}	

void Celular::limpiarPantalla() {
	pantalla.limpiar();
}
