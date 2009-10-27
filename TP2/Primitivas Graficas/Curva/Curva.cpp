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
	bool last= false; 
	
	Vertice2D ptos[4];
	int first= 0;
	
	while(!last) {	 
	 
	 	for(int j= 0; j<4; j++) {
	 		ptos[j].x= find(ptosControl, first+j).x;
	 		ptos[j].y= find(ptosControl, first+j).y;	 
	 	}
	 
		for(int i= 0; !end; i++) { 	 	
	 		t= dt*i;
	 		 		
		  // cálculo de los coeficientes polinomiales	 
		  cx= 3.0 * (ptos[1].x - ptos[0].x);
		  bx= 3.0 * (ptos[2].x - ptos[1].x) - cx;
		  ax= ptos[3].x - ptos[0].x - cx - bx;
		 
		  cy= 3.0 * (ptos[1].y - ptos[0].y);
		  by= 3.0 * (ptos[2].y - ptos[1].y) - cy;
		  ay= ptos[3].y - ptos[0].y - cy - by;
	 
		  //cálculo del punto de la curva en el valor de parámetro t	 
		  //t es el valor del parámetro, 0 <= t <= 1
		  tSquared= t * t;
		  tCubed= tSquared * t;
		 
		  result.x= (ax * tCubed) + (bx * tSquared) + (cx * t) + ptos[0].x;
		  result.y= (ay * tCubed) + (by * tSquared) + (cy * t) + ptos[0].y;
		 
		 	glVertex2i(result.x, result.y);
		 	
		 	//Llegamos al P3
		 	if(result.x == ptos[3].x && result.y == ptos[3].y)
		 		end= true;
		}
		
		//Avanzo a los proximos 4 ptos de control
		if(ptos[3].x != it->x || ptos[3].y != it->y) {
			first= first+3;
			end= false;
		} else
			last= true;
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

	Vertice2D puntos[4];

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

		//multiplico B con los puntos
		for (int k=0; k<4; k++) {
			for (int m=0; m<4; m++) {

				result[k].x += B[k][m] * puntos[m].x;
				result[k].y += B[k][m] * puntos[m].y;

			}
		}

		//divido por seis
		for (int j= 0; j<4; j++) {
			result[j].x /= 6;
			result[j].y /= 6;
		}

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

			glVertex2i(v.x, v.y);

		}
	}

}
