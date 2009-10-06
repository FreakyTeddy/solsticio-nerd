#include "Poligono.h"
#include "Relleno/relleno.h"
#include <iostream> //TODO sacar!

Poligono::Poligono() {
	relleno = false;
	contorno = true;
	esDDA = true;
}
Poligono::Poligono(bool relleno) {
	this->relleno = relleno;
	this->contorno = false;
	this->esDDA = true;
}

Poligono::~Poligono() {
	vertices.clear();
}

void Poligono::setRelleno(bool relleno) {
	this->relleno = relleno;
}

void Poligono::setContorno(bool contorno) {
	this->contorno = contorno;
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

	if(contorno) {
		Linea linea;
		std::list<Vertice>::iterator it = vertices.begin();
		std::list<Vertice>::iterator next = vertices.begin();
		std::list<Vertice>::iterator end = vertices.end();
		next++;

		if (it == end)
			return;
		
		Vertice origen;
		origen.x= 0;
		origen.y= 0;
		
		Transform2D t(800, 600, 100, 100, origen);
		Vertice vert; 
		Vertice vertNext; 

		if (esDDA) {
			//lineaDDA			
			while (next != end) {
				
				vert= t.transformVerts2D(*it);
				vertNext= t.transformVerts2D(*next);
				
				linea.lineaDDA(vert.x, vert.y, vertNext.x, vertNext.y);
				it++;
				next++;
			}
			//next = vertices.begin(); //uno el ultimo con el primero
			vert= t.transformVerts2D(*vertices.begin());
			
			linea.lineaDDA(vert.x, vert.y, vertNext.x, vertNext.y);
		}
		else {
			//linea Bresenham
			while (next != end) {
				vert= t.transformVerts2D(*it);
				vertNext= t.transformVerts2D(*next);
				
				linea.lineaBresenham(vert.x, vert.y, vertNext.x, vertNext.y);
				it++;
				next++;
			}
//			next = vertices.begin(); //uno el ultimo con el primero
			vert= t.transformVerts2D(*vertices.begin());

			linea.lineaBresenham(vert.x, vert.y, vertNext.x, vertNext.y);
		}
	}
}
