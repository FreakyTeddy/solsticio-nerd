#include "Curva.h"

Curva::Curva(): factorBezier(FACTOR_BEZIER_INICIAL) { };


Vertice2D& find(std::list<Vertice2D> vertices, unsigned int position) {
	
	std::list<Vertice2D>::iterator it= vertices.begin();
	
	for(unsigned int i= 0; it != vertices.end(); i++, it++) { 
		if(i == position)
			break;	
	}
	
	return *it;
} 

void Curva::BezierCubica(std::list<Vertice2D> ptosControl) {
	
  float dt=(float) 1.0 / (ptosControl.size()*factorBezier);
	
	std::list<Vertice2D>::iterator it= ptosControl.end();

	float   ax, bx, cx;
  float   ay, by, cy;
  float   t, tSquared, tCubed;
  Vertice2D result;
	 
	bool end= false; 
	 
	for(int i= 0; !end; i++) {
 
 		t= dt*i;
 	
	  // cálculo de los coeficientes polinomiales	 
	  cx = 3.0 * (find(ptosControl, 1).x - find(ptosControl, 0).x);
	  bx = 3.0 * (find(ptosControl, 2).x - find(ptosControl, 1).x) - cx;
	  ax = find(ptosControl, 3).x - find(ptosControl, 0).x - cx - bx;
	 
	  cy = 3.0 * (find(ptosControl, 1).y - find(ptosControl, 0).y);
	  by = 3.0 * (find(ptosControl, 2).y - find(ptosControl, 1).y) - cy;
	  ay = find(ptosControl, 3).y - find(ptosControl, 0).y - cy - by;
 
	  //cálculo del punto de la curva en el valor de parámetro t	 
	  //t es el valor del parámetro, 0 <= t <= 1
	  
	  tSquared= t * t;
	  tCubed= tSquared * t;
	 
	  result.x= (ax * tCubed) + (bx * tSquared) + (cx * t) + find(ptosControl, 0).x;
	  result.y= (ay * tCubed) + (by * tSquared) + (cy * t) + find(ptosControl, 0).y;
	 
	 	glVertex2i(result.x, result.y);
	 	
	 	//Llegamos al P3
	 	if(result.x == it->x && result.y == it->y)
	 		end= true;
  }
}

void Curva::setFactorBezier(int factor) {

	factorBezier= factor;
}
