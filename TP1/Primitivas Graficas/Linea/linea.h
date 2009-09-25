#ifndef LINEA_H_
#define LINEA_H_

#include "GL/glut.h"
#include "math.h"

class Linea {

	private:
		void swap(int &n1, int &n2);
	
	public:
		void lineaBresenham(int x0, int y0, int x1, int y1);
	
		void lineaDDA(int x0, int y0, int x1, int y1);
};

#endif /*LINEA_H_*/
