#include "Celular.h"
#include <iostream>

Celular::Celular() {
//	for (int i=0; i<10; i++) {
//		numero[i] = new Numero(i);
//	}
	crearCarcasa();
}

Celular::~Celular() {
//	for (int i=0; i<10; i++) {
//		delete numero[i];
//	}
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
	cel.agregarVertice(77,156);
	cel.agregarVertice(85,150);
	cel.agregarVertice(85,90);
	cel.agregarVertice(82,84);
	cel.agregarVertice(74,80);
	cel.agregarVertice(72,75);
	cel.agregarVertice(82,71);//!!!!warning
	cel.agregarVertice(85,65);
	cel.agregarVertice(85,10);
	cel.agregarVertice(82,4);
	cel.agregarVertice(75,0);
}


void Celular::dibujar() {
	//transformar
	std::cout<<"------------cel--------------------------"<<std::endl;
	cel.dibujarConRelleno();
	std::cout<<"------------cel Done--------------------------"<<std::endl;
	boton.dibujar();
}
