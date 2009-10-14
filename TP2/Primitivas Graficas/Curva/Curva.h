#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
#include <list>
 
typedef struct {
    float x;
    float y;
} Vertice2D;

class Curva {
	
	public:		
		/* Dibuja los vertices de la curva, apartir de los puntos de control
		 * pasados en la lista (P0, P1, P2, P3).
		 * */ 		
		void BezierCubica(std::list<Vertice2D> ptosControl);
};

#endif /*CURVA_H_*/
