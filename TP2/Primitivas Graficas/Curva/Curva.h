#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
 
typedef struct {
    float x;
    float y;
} Vertice2D;


class Curva {
	
	
	public:
		/*
 			ComputeBezier fills an array of Point2D structs with the curve   
 		  points generated from the control points cp. Caller must 
 			allocate sufficient memory for the result, which is 
 			<sizeof(Point2D) numberOfPoints>
		*/
		void Bezier(Vertice2D* cp, int numberOfPoints, Vertice2D* curve);
};

#endif /*CURVA_H_*/
