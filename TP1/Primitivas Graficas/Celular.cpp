#include "Celular.h"
#include <iostream>

Celular::Celular() {
	for (int i=0; i<10; i++) {
		numero[i] = new Numero(i);
	}
	botonera.setNumeros(numero);
	crearCarcasa();
	crearSombras();
	//para probar pantalla :)

//	pantalla.agregarNumero(numero[1]);
//	pantalla.agregarNumero(numero[2]);
//	pantalla.agregarNumero(numero[3]);
//	pantalla.agregarNumero(numero[4]);
//	pantalla.agregarNumero(numero[1]);
//	pantalla.agregarNumero(numero[2]);
//	pantalla.agregarNumero(numero[3]);
//	pantalla.agregarNumero(numero[1]);
//	pantalla.agregarNumero(numero[5]);
//	pantalla.agregarNumero(numero[1]);
//	pantalla.agregarNumero(numero[2]);
//	pantalla.agregarNumero(numero[9]);
//	pantalla.agregarNumero(numero[8]);

}

Celular::~Celular() {
	for (int i=0; i<10; i++) {
		delete numero[i];
	}
}

void Celular::crearCarcasa() {

	cel.agregarVertice(25,0);
	cel.agregarVertice(17,4);
	cel.agregarVertice(15,10);
	cel.agregarVertice(15,65);
	cel.agregarVertice(17,71);
	cel.agregarVertice(28,75);
	cel.agregarVertice(25,80);
	cel.agregarVertice(17,84);
	cel.agregarVertice(15,90);
	cel.agregarVertice(15,150);
	cel.agregarVertice(17,156);
	cel.agregarVertice(25,160);
	cel.agregarVertice(75,160);
	cel.agregarVertice(83,156);
	cel.agregarVertice(85,150);
	cel.agregarVertice(85,90);
	cel.agregarVertice(82,84);
	cel.agregarVertice(74,80);
	cel.agregarVertice(72,75);
	cel.agregarVertice(82,71);
	cel.agregarVertice(85,65);
	cel.agregarVertice(85,10);
	cel.agregarVertice(82,4);
	cel.agregarVertice(75,0);
	cel.setDimensiones(160,160);

}

void Celular::crearSombras() {

	//sombra arriba
	sombra[0].agregarVertice(19,155);
	sombra[0].agregarVertice(17,152);
	sombra[0].agregarVertice(16,145);
	sombra[0].agregarVertice(16,90);
	sombra[0].agregarVertice(19,85);
	sombra[0].agregarVertice(21,84);
	sombra[0].agregarVertice(24,82);
	sombra[0].agregarVertice(21,86);
	sombra[0].agregarVertice(19,90);

	//sombra abajo
	sombra[1].agregarVertice(19,70);
	sombra[1].agregarVertice(17,69);
	sombra[1].agregarVertice(16,65);
	sombra[1].agregarVertice(16,10);
	sombra[1].agregarVertice(19,5);
	sombra[1].agregarVertice(21,4);
	sombra[1].agregarVertice(24,2);
	sombra[1].agregarVertice(21,6);
	sombra[1].agregarVertice(19,10);

	//sombra clara abajo
	sombra[2].agregarVertice(22,71);
	sombra[2].agregarVertice(19,70);
	sombra[2].agregarVertice(19,65);
	sombra[2].agregarVertice(19,10);
	sombra[2].agregarVertice(22,5);
	sombra[2].agregarVertice(24,4);
	sombra[2].agregarVertice(27,2);
	sombra[2].agregarVertice(24,6);
	sombra[2].agregarVertice(22,10);

	//sombra clara arriba
	sombra[3].agregarVertice(22,157);
	sombra[3].agregarVertice(19,154);
	sombra[3].agregarVertice(19,145);
	sombra[3].agregarVertice(19,90);
	sombra[3].agregarVertice(22,85);
	sombra[3].agregarVertice(24,84);
	sombra[3].agregarVertice(27,82);
	sombra[3].agregarVertice(24,86);
	sombra[3].agregarVertice(22,90);

	for (int i=0; i<4;i++)
		sombra[i].setDimensiones(160,160);
	//hacer visagra TODO

}


void Celular::dibujar() {
	//transformar
	MatrizTrans2D matTrans;
	Vertice fixed;  /* escala del celular */
	fixed.x = 80;
	fixed.y = 80;
	//matTrans.scale2D(0.5,0.5, fixed); Desfasado
	//matTrans.translate2D(10,10); desfasado!!!!
	matTrans.scale2D(1,1, fixed);
	matTrans.translate2D(0,0);
	

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
	matTransPantalla.postMultiply(matTrans);
	matTransPantalla.translate2D(-18.5,35);
	matTransPantalla.scale2D(0.6,0.6, fixedPt);


	pantalla.dibujar(matTransPantalla);
	
	MatrizTrans2D matTransBotonera;

	matTransBotonera.postMultiply(matTrans);
	matTransBotonera.translate2D(-18.5,-18.0);//no escala bien vertical!!!
	matTransBotonera.scale2D(0.6,0.65, fixedPt);


	botonera.dibujar(matTransBotonera);
		
}

void Celular::apretarBoton(int boton) {
	
	botonera.apretarBoton(boton);
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

void Celular::mostrarNumero(int num) {
	pantalla.agregarNumero(numero[num]);
}

