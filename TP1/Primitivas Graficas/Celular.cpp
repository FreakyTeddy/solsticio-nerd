#include "Celular.h"
#include <iostream>

Celular::Celular() {
	for (int i=0; i<10; i++) {
		numero[i] = new Numero(i);
	}
	crearCarcasa();
	crearSombras();
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

	//botonera
	botonera.agregarVertice(70,10);
	botonera.agregarVertice(75,15);
	botonera.agregarVertice(75,60);
	botonera.agregarVertice(70,65);
	botonera.agregarVertice(30,65);
	botonera.agregarVertice(25,60);
	botonera.agregarVertice(25,15);
	botonera.agregarVertice(30,10);
	botonera.agregarVertice(70,10);

}

void Celular::crearSombras() {
	//sombra arriba
//	sombra[0].agregarVertice(25,160);
//	sombra[0].agregarVertice(17,150);
//	sombra[0].agregarVertice(17,90);
//	sombra[0].agregarVertice(25,83);
//	sombra[0].agregarVertice(30,77);
//	sombra[0].agregarVertice(40,77);
//	sombra[0].agregarVertice(43,83);
//	sombra[0].agregarVertice(58,83);
//	sombra[0].agregarVertice(61,77);
//	sombra[0].agregarVertice(69,77);
//	sombra[0].agregarVertice(69,81);
//	sombra[0].agregarVertice();



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

}


void Celular::dibujar() {
	//transformar
	std::cout<<"------------cel--------------------------"<<std::endl;

	glColor3f(0.5,0.5,0.5);
	cel.dibujarConRelleno();

	glColor3f(0.3,0.3,0.3);
	sombra[1].dibujarConRelleno();

	glColor3f(0.4,0.4,0.4);
	sombra[2].dibujarConRelleno();

	std::cout<<"------------cel Done--------------------------"<<std::endl;
	glColor3f(1.0,0.5,1.0);
	botonera.dibujarConRelleno();
	std::cout<<"------------botonera Done--------------------------"<<std::endl;
	glColor3f(0.9,0.9,0.9);
	pantalla.dibujar();
	std::cout<<"------------Pantalla Done--------------------------"<<std::endl;

	//trasladar y dibujar cada boton con su numero correspondiente
	//boton.dibujar(numero[i]);
}
