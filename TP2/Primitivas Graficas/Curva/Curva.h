#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
#include <list>
 
#define FACTOR_BEZIER_INICIAL 10 
 
typedef struct {
    float x;
    float y;
} Vertice2D;

class Curva {
	
	private:
		int factorBezier;
	
	public:		
		Curva();
	
		/* Dibuja los vertices de la curva, apartir de los puntos de control
		 * pasados en la lista (P0, P1, P2, P3).
		 * */ 		
		void BezierCubica(std::list<Vertice2D> ptosControl);

		void setFactorBezier(int factor);
};

#endif /*CURVA_H_*/
