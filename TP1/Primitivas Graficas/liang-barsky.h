#ifndef LIANGBARSKY_H_
#define LIANGBARSKY_H_

#include "Poligono.h"

class ClippingPoligonos 
{
	private:
	
	public:
		ClippingPoligonos();

		Poligono* clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, Poligono* poligono);

		~ClippingPoligonos();
		
};

#endif /*LIANGBARSKY_H_*/
