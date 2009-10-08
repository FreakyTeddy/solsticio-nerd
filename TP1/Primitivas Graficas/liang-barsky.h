#ifndef LIANGBARSKY_H_
#define LIANGBARSKY_H_

#include "Poligono.h"

class ClippingPoligonos 
{
	private:
	
	public:
		ClippingPoligonos();
		void clippingLB(int Vtop,int Vbottom, int Vleft, int Vright, float& x0, float& x1, float& y0, float& y1);
		Poligono* clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, Poligono* poligono);
		Poligono* clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, Poligono* poligono, int numVerticeInicial);
		~ClippingPoligonos();
		
};

#endif /*LIANGBARSKY_H_*/
