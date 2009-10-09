#include "Poligono.h"
#include "Relleno/relleno.h"
#include <iostream> //TODO sacar!
#include "liang-barsky.h"

Poligono::Poligono() {
	ancho = 100;
	alto = 100;
}

//Poligono::Poligono(const Poligono &p) {
//	std::list<Vertice>::iterator it = p.vertices.begin();
//	for(int i = 0; it != p.vertices.end(); it++){
//			this->agregarVertice((*it).x, (*it).y);
//	}
//}

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
     
     ClippingPoligonos clipper;
     Poligono *cortado;
     cortado = clipper.clippingLB(400,200,545,295,this);

      //algoritmo de relleno de poligonos Rellena el poligono clippeado
	 dcPt* ptos;
	 ptos = new dcPt[cortado->vertices.size()];
	 std::list<Vertice>::iterator it = cortado->vertices.begin();
	 for(int i=0;it!=cortado->vertices.end();it++,i++){
			vert= t.transformVerts2D(*it);
			ptos[i].x = vert.x;
			ptos[i].y = vert.y;
	 }
	 Relleno relleno;
	 relleno.scanLine(cortado->vertices.size(), ptos);
	 delete []ptos;
	 delete cortado;

}

void Poligono::dibujarContorno(bool esDDA, MatrizTrans2D &matTrans) {

	Vertice origen;
		origen.x= ancho;
		origen.y= alto;
	Transform2D t;

	//Agrego matriz de transformacion
	t.setMatTrans(&matTrans);
	t.setMatView(800, 600, 160,160, origen); //ancho, alto, origen);

	Vertice vert;
	Vertice vertNext;
	Linea linea;
	std::list<Vertice>::iterator it = vertices.begin();
	std::list<Vertice>::iterator next = vertices.begin();
	std::list<Vertice>::iterator end = vertices.end();
	next++;

	//crear un poligono copia, transformarlo y pasarlo al clipper.. despues dibujar

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
	
