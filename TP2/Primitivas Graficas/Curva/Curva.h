#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
#include <list>

#include <iostream>
 
#define FACTOR_BEZIER_INICIAL 20 
#define FACTOR_MIN 0 
#define FACTOR_MAX 30 
 
typedef struct {
    float x;
    float y;
} Vertice2D;

typedef std::list<Vertice2D> VertexList;  //TODO en realidad debe ser 3d ;)

class Curva {
	
	private:
		int factorBezier;
	
	public:
		/* Crea una curva con factores de paso por defecto.
		 * */		
		Curva();

//TODO en lugar de dibujar deberian devolver los puntos no? porque nos sirven :P

		/* Dibuja los vertices de la curva, apartir de los puntos de control
		 * pasados en la lista (P0, P1, P2, P3).
		 * */ 		
		void BezierCubica(std::list<Vertice2D> ptosControl, std::list<Vertice2D> &ptosCurva,
											std::list<Vertice2D> &ptosTangente, std::list<Vertice2D> &ptosNormal);

		/* Guarda en curva los puntos a unir para dibujar
		 * una curva Bspline cubica uniforme a partir de los puntos de control
		 *
		 * requiere al menos 4 puntos de control para dibujar algo
		 * */
		void Bspline(VertexList ptosControl, VertexList *curva);

		/* Suma al factor del paso de Bezier la cantidad pasada por
		 * parametro.
		 * */ 		
		void modificarFactorBezier(int cantidad);
};

#endif /*CURVA_H_*/
