#include <iostream>
#include "liang-barsky.h"


int main (int argc, char** argv){
	ClippingPoligonos clipper;
	float x0 = 50.0;
	float y0 = 17.0;
	float x1 = 100.0;
	float y1 = 102.0;
	int Vtop = 25;
	int Vbottom = 35;
	int Vleft = 65;
	int Vright = 85;
	
	std::cout << "Linea original: x0 = " << x0 << "x1 = " << x1 << "y0 = " << y0 << "y1 = " << y1 << std::endl;
	std::cout << "Viewport: Vleft = " << Vleft << "Vright = " << Vright << "Vtop = " << Vtop << "Vbottom = " << Vbottom << std::endl;
	
	clipper.clippingLB(Vtop,Vbottom,Vleft,Vright,x0,x1,y0,y1);
	
	std::cout << "Linea clippeada: x0 = " << x0 << "x1 = " << x1 << "y0 = " << y0 << "y1 = " << y1 << std::endl;
	
	return 0;
}
 