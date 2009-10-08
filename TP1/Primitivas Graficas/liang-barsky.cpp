#include "liang-barsky.h"
#include <iostream>

ClippingPoligonos::ClippingPoligonos()
{
	
}

// TODO:
// A este algoritmo habria que pasarle un objeto de tipo Poligono
// en vez de x0,x1,y0,y1 y agregarle un parametro int n = numero del vertice inicial,
// es una version de prueba para ver si recorta una linea correctamente.
// Para generalizarlo a poligonos ademas falta implementar el TODO de agregar vertices. 
void ClippingPoligonos::clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, float& x0, float& x1, float& y0, float& y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;

//	if(!dx || !dy) return;
	float p[4];
	float q[4];
	p[0] = -dx;	
	p[1] = dx;
	p[2] = -dy;
	p[3] = dy;
	q[0] = x0 - Vleft;
	q[1] = Vright - x0;
	q[2] = y0 - Vbottom;
	q[3] = Vtop - y0;
	float t = 0;
	float t0 = 0;
	float t1 = 1;
	
	for(int i = 0; i < 4; i++){
		t = q[i] / p[i];
		std::cout << "paso: "<<i<<" t=" << t << std::endl;
		if((t >= 0) && (t <= 1)){
			if(p[i] < 0){
				if(t > t0) t0 = t;
			}else{
				if(t < t1) t1 = t;
			}
		}
		
	}
	std::cout << "Puntos antes de calcular: x0=" << x0 << " y0= " << y0 << " x1= " << x1 << " y1= " << y1 << std::endl;
	std::cout << "parametros: t0= " << t0 << " t1= " << t1 << std::endl;
	std::cout << "deltas: dx= " << dx << " dy= " << dy << std::endl;
	y1 = y0 + (t1 * dy);
	x1 = x0 + (t1 * dx);
	x0 = x0 + (t0 * dx);
	y0 = y0 + (t0 * dy);


	std::cout << "Puntos despues de calcular: x0=" << x0 << " y0= " << y0 << " x1= " << x1 << " y1= " << y1 << std::endl;
	
}

Poligono* ClippingPoligonos::clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, Poligono* poligono){
     std::list<Vertice> verticesOriginales = poligono->obtenerVertices();
     std::list<Vertice>::iterator it = verticesOriginales.begin();
     Poligono* poligonoClippeado = new Poligono();
     std::list<Vertice> verticesClippeados = poligonoClippeado->obtenerVertices();
     Vertice vertice0;
     Vertice vertice1;
     float xo0,xo1,yo0,yo1; //pares x,y originales
     int i = 0;
     bool encontrado = false;
     float x0 = (*it).x;
     float x1 = 0;
     float y0 = (*it).y;
     float y1 = 0;

     vertice0.x=x0;
     vertice0.y=y0;

     verticesOriginales.push_back(vertice0);

     for(it=verticesOriginales.begin();it!=verticesOriginales.end();it++,x0=xo1,y0=yo1){
	  xo1=x1=(*it).x;
	  yo1=y1=(*it).y;

	  if(x0 < Vleft && x1 < Vleft){
	       continue;
	  }


	  std::cout << "x0: " << x0 << " y0: " << y0 << std::endl;
	  std::cout << "x1: " << x1 << " y1: " << y1 << std::endl;

	  clippingLB(Vtop,Vbottom,Vleft,Vright, x0,x1,y0,y1);

	  std::cout << "x0: " << x0 << " y0: " << y0 << std::endl;
	  std::cout << "x1: " << x1 << " y1: " << y1 << std::endl;

	  std::cout << "----------------------------------\n";

	  poligonoClippeado->agregarVertice(x0,y0);
	  poligonoClippeado->agregarVertice(x1,y1);
     }
     
     return poligonoClippeado;
}





Poligono* ClippingPoligonos::clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, Poligono* poligono, int numVerticeInicial)
{
     std::list<Vertice> verticesOriginales = poligono->obtenerVertices();
     std::list<Vertice>::iterator it = verticesOriginales.begin();
     Poligono* poligonoClippeado = new Poligono();
     int i = 0;
     bool encontrado = false;
     float x0 = 0;
     float x1 = 0;
     float y0 = 0;
     float y1 = 0;
     for(it = verticesOriginales.begin(); it != verticesOriginales.end() && !encontrado; it++,i++){
	  if(i == numVerticeInicial){
	       x0 = (*it).x;
	       y0 = (*it).y;
	  }else{
	       if(i > numVerticeInicial){
		    encontrado = true;
		    x1= (*it).x;
		    y1 = (*it).y;
	       }
	  }
     }
	
     float dx = x1 - x0;
     float dy = y1 - y0;

     if(!dx || !dy) return NULL;
     float p[4];
     float q[4];
     p[0] = -dx;	
     p[1] = dx;
     p[2] = -dy;
     p[3] = dy;
     q[0] = x0 - Vleft;
     q[1] = Vright - x0;
     q[2] = y0 - Vbottom;
     q[3] = Vtop - y0;
     float t = 0;
     float t0 = 0;
     float t1 = 1;
	
     for(int i = 0; i < 4; i++){
	  t = q[i] / p[i];
	  std::cout << "paso: "<<i<<" t=" << t << std::endl;
	  if((t >= 0) && (t <= 1)){
	       if(p[i] < 0){
		    if(t > t0) t0 = t;
	       }else{
		    if(t < t1) t1 = t;
	       }
	  }
		
	  //TODO agregar vertices
		
//		x0 = x0 + (t0 * dx);
//		y0 = y0 + (t0 * dy);
//		x1 = x0 + (t1 * dx);
//		y1 = y0 + (t1 * dy);
     }
     std::cout << "Puntos antes de calcular: x0=" << x0 << " y0= " << y0 << " x1= " << x1 << " y1= " << y1 << std::endl;
     std::cout << "parametros: t0= " << t0 << " t1= " << t1 << std::endl;
     std::cout << "deltas: dx= " << dx << " dy= " << dy << std::endl;
     Vertice vertice0;
     Vertice vertice1;
	
     vertice1.y = y0 + (t1 * dy);
     vertice1.x = x0 + (t1 * dx);
     vertice0.x = x0 + (t0 * dx);
     vertice0.y = y0 + (t0 * dy);
	
     // agrego vertices
     std::list<Vertice> verticesClippeados = poligonoClippeado->obtenerVertices();
     i = 0;
     for(it = verticesOriginales.begin() ; it != verticesOriginales.end() ; it++, i++){
	  if(i == numVerticeInicial){
	       verticesClippeados.push_back(vertice0);
			
	  }else{
	       if (i == numVerticeInicial+1){
		    verticesClippeados.push_back(vertice1);
	       }else{
		    verticesClippeados.push_back(*it);
	       }
	  }
     }

     std::cout << "Puntos despues de calcular: x0=" << x0 << " y0= " << y0 << " x1= " << x1 << " y1= " << y1 << std::endl;
	
     return poligonoClippeado;
}


ClippingPoligonos::~ClippingPoligonos()
{
	
}
