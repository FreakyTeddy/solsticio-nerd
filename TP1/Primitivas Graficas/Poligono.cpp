#include "Poligono.h"
#include "Relleno/relleno.h"
#include <iostream> //TODO sacar!

Poligono::Poligono() {
}

Poligono::~Poligono() {
	vertices.clear();
}

void Poligono::agregarVertice(float x, float y) {
	Vertice v;
	v.x = x;
	v.y = y;
	vertices.push_back(v);
}

void Poligono::dibujarConRelleno() {

		Vertice origen;
		origen.x= 0;
		origen.y= 0;
		
		Transform2D t(800, 600, 100, 160, origen);
		Vertice vert; 
		Vertice vertNext; 
		MatrizTrans2D matTrans;
		//Escalo
		Vertice fixedPt;
		fixedPt.x= 0;
		fixedPt.y= 0;
		matTrans.scale2D(0.5, 1, fixedPt);
		t.setMatTrans(&matTrans);	

		//algoritmo de relleno de poligonos
	     dcPt* ptos;
	     ptos = new dcPt[vertices.size()];
	     std::list<Vertice>::iterator it = vertices.begin();
	     for(int i=0;it!=vertices.end();it++,i++){
		  		vert= t.transformVerts2D(*it);
		  		ptos[i].x = vert.x;
		  		ptos[i].y = vert.y;
	     }
	     Relleno relleno;
	     relleno.scanLine(vertices.size(), ptos);
}

void Poligono::dibujarContorno(bool esDDA) {

	Vertice origen;
	origen.x= 0;
	origen.y= 0;
	Transform2D t(800, 600, 100, 100, origen);
	Vertice vert;
	Vertice vertNext;
	MatrizTrans2D matTrans;
	//Escalo
	Vertice fixedPt;
	fixedPt.x= 0;
	fixedPt.y= 0;
	matTrans.scale2D(1, 1, fixedPt);
	t.setMatTrans(&matTrans);

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

std::list<Vertice>& Poligono::obtenerVertices(){
	return this->vertices;
}
