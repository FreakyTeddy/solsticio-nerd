#ifndef CURVA_H_
#define CURVA_H_

#include "GL/glut.h"
#include <map>
#include <math.h>
#include <vector>
#include <iostream>


#include "../Vertice.h"


 
#define FACTOR_INICIAL 4
#define FACTOR_MIN 1
#define FACTOR_MAX 25
 //usar valores tipo 5 o 10 esta bien :)

class Curva {
	
private:
  int factorBezier;
  int factorBspline;
	
public:
  /* Crea una curva con factores de paso por defecto.
   * */
  Curva();

  /* Dibuja los vertices de la curva, apartir de los puntos de control
   * pasados en la lista (P0, P1, P2, P3).
   * */
  void BezierCubica(std::vector<Vertice>& ptosControl, std::vector<Vertice> &ptosCurva);

  /* Suma al factor del paso de Bezier la cantidad pasada por parametro.
   * */
  void setFactorBezier(int cantidad);
		
  /* Guarda en curva los puntos a unir para dibujar una curva Bspline cubica uniforme a
   * partir de los puntos de control requiere al menos 4 puntos de control para dibujar algo
   * */

  void Bspline(std::vector<float> &ptosControl, std::vector<float> &ptosCurva);

  void Bspline(std::vector<Vertice> &ptosControl, std::vector<Vertice> &ptosCurva);

  /* Modifica al factor del paso de Bspline a la cantidad pasada por parametro.
   * */
  void setFactor(int cantidad);

};

#endif /*CURVA_H_*/
