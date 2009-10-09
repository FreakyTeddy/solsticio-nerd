#include "Poligono.h"
#include "Relleno/relleno.h"
#include "liang-barsky.h"
#include "../Constantes.h"

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
     extern int anchoventanaM;
     extern int altoventanaM;
     //matriz de transformada
     t.setMatTrans(&matTrans);	
     t.setMatView(800, 600, anchoventanaM,altoventanaM,origen);//ancho, alto, origen);  
     
     //creo un poligono nuevo transformado
     Poligono transformado;

	 std::list<Vertice>::iterator it = vertices.begin();
	 while(it!=vertices.end()){
			vert= t.transformVerts2D(*it);
			transformado.agregarVertice(vert.x,vert.y);
			it++;
	 }

	 //recorte del poligono transformado
     ClippingPoligonos clipper;
     Poligono *cortado;
     cortado = clipper.clippingLB(Viewtop,Viewbottom,Viewleft,Viewright,&transformado);

      //algoritmo de relleno de poligonos Rellena el poligono clippeado
	 dcPt* ptos;
	 ptos = new dcPt[cortado->vertices.size()];

	 it = cortado->vertices.begin();
	 for(int i=0;it!=cortado->vertices.end();it++,i++){
			ptos[i].x = (*it).x;
			ptos[i].y = (*it).y;
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
	extern int anchoventanaM;
    extern int altoventanaM;
	//Agrego matriz de transformacion
	t.setMatTrans(&matTrans);
	t.setMatView(800, 600, anchoventanaM,altoventanaM, origen); //ancho, alto, origen);

	Vertice vert;
	Vertice vertNext;

	//creo un poligono nuevo transformado
	 Poligono transformado;

	 std::list<Vertice>::iterator it = vertices.begin();
	 while(it!=vertices.end()){
			vert= t.transformVerts2D(*it);
			transformado.agregarVertice(vert.x,vert.y);
			it++;
	 }

	 //recorte del poligono transformado
	  ClippingPoligonos clipper;
	  Poligono *cortado;
	  cortado = clipper.clippingLB(Viewtop,Viewbottom,Viewleft,Viewright,&transformado);

	Linea linea;
	it = cortado->vertices.begin();
	std::list<Vertice>::iterator next = cortado->vertices.begin();
	std::list<Vertice>::iterator end = cortado->vertices.end();
	next++;

	//crear un poligono copia, transformarlo y pasarlo al clipper.. despues dibujar

	if (it == end)
		return;

	if (esDDA) {
		//lineaDDA
		while (next != end) {
			linea.lineaDDA((*it).x, (*it).y, (*next).x, (*next).y);
			it++;
			next++;
		}
		next = cortado->vertices.begin();

		linea.lineaDDA((*it).x, (*it).y, (*next).x, (*next).y);
	}
	else {
		//linea Bresenham
		while (next != end) {

			linea.lineaBresenham((*it).x, (*it).y, (*next).x, (*next).y);
			it++;
			next++;
		}
		next = cortado->vertices.begin();

		linea.lineaBresenham((*it).x, (*it).y, (*next).x, (*next).y);
	}

	delete cortado;

}

std::list<Vertice>& Poligono::obtenerVertices(){
	return this->vertices;
}

void Poligono::setDimensiones(int ancho, int alto) {
	this->ancho  = ancho;
	this->alto = alto;
}	
	
