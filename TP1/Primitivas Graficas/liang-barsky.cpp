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
	float aux = 0;
	if(x0 > x1){
		  dx = x0 - x1;
		  aux = x1;
		  x1 = x0;
		  x0 = aux;
	}
	if(y0 > y1) {
		 dy = y0 - y1;
		 aux = y1;
		 y1 = y0;
		 y0 = aux;
	}
	if(!dx || !dy) return;
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
	x0 = x0 + (t0 * dx);
	y0 = y0 + (t0 * dy);
	x1 = x0 + (t1 * dx);
	y1 = y0 + (t1 * dy);
	std::cout << "Puntos despues de calcular: x0=" << x0 << " y0= " << y0 << " x1= " << x1 << " y1= " << y1 << std::endl;
	
}

ClippingPoligonos::~ClippingPoligonos()
{
	
}
