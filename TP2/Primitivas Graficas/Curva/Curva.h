#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
#include <list>
#include <math.h>
#include "../Vertice/Vertice.h"

#include <iostream>
 
#define FACTOR_INICIAL 50 
#define FACTOR_MIN 0 
#define FACTOR_MAX 100 
 
class Curva {
	
private:
  int factorBezier;
  float longitudBezier;

  int factorBspline;
	
public:
  /* Crea una curva con factores de paso por defecto.
   * */
  Curva();

  /* Dibuja los vertices de la curva, apartir de los puntos de control
   * pasados en la lista (P0, P1, P2, P3).
   * */
  void BezierCubica(std::list<Vertice> ptosControl, std::list<Vertice> &ptosCurva,
                    std::list<Vertice> &ptosTangente, std::list<Vertice> &ptosNormal);

  /* Suma al factor del paso de Bezier la cantidad pasada por parametro.
   * */
  void modificarFactorBezier(int cantidad);
		
  /* Devuelve la longitud de la ultima curva de Bezier
   * */
  float getLongitudBezier() { return longitudBezier; }

  /* Guarda en curva los puntos a unir para dibujar una curva Bspline cubica uniforme a
   * partir de los puntos de control requiere al menos 4 puntos de control para dibujar algo
   * */
  void Bspline(std::list<Vertice> ptosControl, std::list<Vertice> &ptosCurva,
               std::list<Vertice> &ptosTangente, std::list<Vertice> &ptosNormal);

  /* Suma al factor del paso de Bspline la cantidad pasada por parametro.
   * */
  void modificarFactorBspline(int cantidad);
};

#endif /*CURVA_H_*/
