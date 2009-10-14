#include "Curva.h"

/*
cp es una matriz de 4 elementos donde:
cp[0] es el primer punto, o P0 en el diagrama de abajo
cp[1] es el primer punto de control, o P1 en el diagrama de abajo
cp[2] es el segundo punto de control, o P2 en el diagrama de abajo
cp[3] es el punto final, o P3 en el diagrama de abajo
t es el valor del parámetro, 0 <= t <= 1
*/
 
Vertice2D PointOnCubicBezier(Vertice2D* cp, float t) {
    
	float   ax, bx, cx;
  float   ay, by, cy;
  float   tSquared, tCubed;
  Vertice2D result;
 
  /* cálculo de los coeficientes polinomiales */
 
  cx = 3.0 * (cp[1].x - cp[0].x);
  bx = 3.0 * (cp[2].x - cp[1].x) - cx;
  ax = cp[3].x - cp[0].x - cx - bx;
 
  cy = 3.0 * (cp[1].y - cp[0].y);
  by = 3.0 * (cp[2].y - cp[1].y) - cy;
  ay = cp[3].y - cp[0].y - cy - by;
 
  /* cálculo del punto de la curva en el valor de parámetro t */
 
  tSquared = t * t;
  tCubed = tSquared * t;
 
  result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
  result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + cp[0].y;
 
 	glVertex2i(result.x, result.y);
 
  return result;
}

void Curva::Bezier(Vertice2D* cp, int numberOfPoints, Vertice2D* curve) {

  float dt=(float) 1.0 / (numberOfPoints - 1);
 
  for(int i = 0; i < numberOfPoints; i++)
  curve[i] = PointOnCubicBezier(cp, i*dt);	
}
