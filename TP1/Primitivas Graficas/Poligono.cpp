#include "Poligono.h"
#include "Relleno/relleno.h"
#include <iostream> //TODO sacar!

Poligono::Poligono() {
	relleno = false;
	esDDA = true;
}
Poligono::Poligono(bool relleno) {
	this->relleno = relleno;
	this->esDDA = true;
}

Poligono::~Poligono() {
	vertices.clear();
}

void Poligono::setRelleno(bool relleno) {
	this->relleno = relleno;
}

void Poligono::setBresenham() {
	esDDA = false;
}

void Poligono::setDDA() {
	esDDA = true;
}

void Poligono::agregarVertice(int x, int y) {
	Vertice v;
	v.x = x;
	v.y = y;
	vertices.push_back(v);
}

void Poligono::dibujar() {
	//TODO implementar!
	if (relleno) {
		//algoritmo de relleno de poligonos
	     dcPt* ptos;
	     ptos = new dcPt[vertices.size()];
	     std::list<Vertice>::iterator it = vertices.begin();
	     for(int i=0;it!=vertices.end();it++,i++){
		  ptos[i].x = (*it).x;
		  ptos[i].y = (*it).y;

	     }
	     Relleno relleno;
	     relleno.scanLine(vertices.size(), ptos);
	}
	else {
		Linea linea;
		std::list<Vertice>::iterator it = vertices.begin();
		std::list<Vertice>::iterator next = vertices.begin();
		std::list<Vertice>::iterator end = vertices.end();
		next++;

		if (it == end)
			return;

		if (esDDA) {
			//lineaDDA
			while (next != end) {
				linea.lineaDDA((*it).x, (*it).y, (*next).x, (*next).y);
				it++;
				next++;
			}
			next = vertices.begin(); //uno el ultimo con el primero
			linea.lineaDDA((*it).x, (*it).y, (*next).x, (*next).y);
		}
		else {
			//linea Bresenham
			while (next != end) {
				linea.lineaBresenham((*it).x, (*it).y, (*next).x, (*next).y);
				it++;
				next++;
			}
			next = vertices.begin(); //uno el ultimo con el primero
			linea.lineaBresenham((*it).x, (*it).y, (*next).x, (*next).y);
		}
	}
}


