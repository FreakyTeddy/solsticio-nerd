#include "Curva.h"
#include <iostream>

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
	  cx= 3.0 * (find(ptosControl, 1).x - find(ptosControl, 0).x);
	  bx= 3.0 * (find(ptosControl, 2).x - find(ptosControl, 1).x) - cx;
	  ax= find(ptosControl, 3).x - find(ptosControl, 0).x - cx - bx;
	 
	  cy= 3.0 * (find(ptosControl, 1).y - find(ptosControl, 0).y);
	  by= 3.0 * (find(ptosControl, 2).y - find(ptosControl, 1).y) - cy;
	  ay= find(ptosControl, 3).y - find(ptosControl, 0).y - cy - by;
 
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

void Curva::modificarFactorBezier(int cantidad) {

	factorBezier+= cantidad;

	if(factorBezier <= FACTOR_MIN)
		factorBezier= 1;
	if(factorBezier > FACTOR_MAX)
		factorBezier= FACTOR_MAX;
}

void Curva::Bspline(std::list<Vertice2D> ptosControl) {

	if (ptosControl.size() < 4)
		return;

	float base_u[4]; //tiene (u^3, u^2, u, 1)

	const int B[][4] = { { -1 , 3 , -3 , 1 },
						{ 3 , -6 , 3 , 0 },
						{ -3 , 0 , 3 , 0 },
						{ 1 , 4 , 1 , 0 }
					  };

	Vertice2D puntos[4]; //VER tal vez se puede usar una cola (aunque yo usaria una pila =O)

	std::list<Vertice2D>::iterator it = ptosControl.begin();

	//itero por los puntos de control
	for (unsigned int i=0; i<(ptosControl.size()-3); i++, it++) {

		Vertice2D result[4];

		for (int j= 0; j<4; j++, it++) {
			//tomo los 4 puntos de control
			puntos[j].x = (*it).x;
			puntos[j].y = (*it).y;

			result[j].x = 0;	//inicializo
			result[j].y = 0;
		}
		//decremento el it
		for (int j= 0; j<4; j++, it--){}
		std::cout<<"Result"<<std::endl;
		//multiplico B con los puntos
		for (int k=0; k<4; k++) {
			for (int m=0; m<4; m++) {

				result[k].x += B[k][m] * puntos[m].x;
				result[k].y += B[k][m] * puntos[m].y;

			}
			std::cout<<"x: "<<result[k].x<<"   y: "<<result[k].y<<std::endl;
		}
std::cout<<"dividido 6"<<std::endl;
		//multiplico por 1/6
		for (int j= 0; j<4; j++) {
			result[j].x /= 6;
			result[j].y /= 6;
			std::cout<<"x: "<<result[j].x<<"   y: "<<result[j].y<<std::endl;
		}

std::cout<<"Puntos Finales"<<std::endl;
		//multiplico por el parametro TODO paso u hardcodeado!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for (float u=0; u<=1; u+=0.1) {

			base_u[0] = u*u*u;
			base_u[1] = u*u;
			base_u[2] = u;
			base_u[3] = 1;

			Vertice2D v;
			v.x=0;
			v.y=0;
			for (int j= 0; j<4; j++) {
				v.x += base_u[j] * result[j].x;
				v.y += base_u[j] * result[j].y;
			}

			std::cout<<"x: "<<v.x<<"   y: "<<v.y<<std::endl;
			glVertex2i(v.x, v.y);

		}
		std::cout<<std::endl<<std::endl;
	}

}
