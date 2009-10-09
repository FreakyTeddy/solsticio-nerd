#include "Poligono.h"
#include "Relleno/relleno.h"
#include <iostream> //TODO sacar!

Poligono::Poligono() {
	ancho = 100;
	alto = 100;
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

void Poligono::dibujarConRelleno(MatrizTrans2D &matTrans) {

     Vertice origen;
     origen.x= ancho;
     origen.y= alto;
     
     Transform2D t;
     
     Vertice vert; 
     Vertice vertNext; 
     
     //matriz de transformada
     t.setMatTrans(&matTrans);	
     t.setMatView(800, 600, 160,160,origen);//ancho, alto, origen);  
     
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
//     ClippingPoligonos cl;
     //   Poligono *p;
//     p = cl.clippingLB(400,0,5,795,this);
     relleno.scanLine(vertices.size(), ptos);
}

void Poligono::dibujarContorno(bool esDDA, MatrizTrans2D &matTrans) {

	Vertice origen;
		origen.x= ancho;
		origen.y= alto;
	Transform2D t;

	//Agrego matriz de vista
	t.setMatTrans(&matTrans);
	t.setMatView(800, 600, 160,160, origen); //ancho, alto, origen);
	Vertice vert;
	Vertice vertNext;
	
	//Agrego matriz de transformacion


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

void Poligono::setDimensiones(int ancho, int alto) {
	this->ancho  = ancho;
	this->alto = alto;
}	
	
