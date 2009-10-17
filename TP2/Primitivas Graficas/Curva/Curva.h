#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
#include <list>
 
#define FACTOR_BEZIER_INICIAL 10 
#define FACTOR_MIN 0 
#define FACTOR_MAX 30 
 
typedef struct {
    float x;
    float y;
} Vertice2D;

class Curva {
	
	private:
		int factorBezier;
	
	public:
		/* Crea una curva con factores de paso por defecto.
		 * */		
		Curva();
	
		/* Dibuja los vertices de la curva, apartir de los puntos de control
		 * pasados en la lista (P0, P1, P2, P3).
		 * */ 		
		void BezierCubica(std::list<Vertice2D> ptosControl);

		/* Suma al factor del paso de Bezier la cantidad pasada por
		 * parametro.
		 * */ 		
		void modificarFactorBezier(int cantidad);
};

#endif /*CURVA_H_*/
