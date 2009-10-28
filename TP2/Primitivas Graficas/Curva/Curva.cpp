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

bool load(std::list<Vertice2D> ptosControl, Vertice2D ptos[4], unsigned int &first) {

	Vertice2D last;	
	bool complete= false;
	unsigned int position= 0;
	unsigned int size= ptosControl.size();
	
	ptos[position].x= find(ptosControl, first).x;
 	ptos[position].y= find(ptosControl, first).y;	 
	last= ptos[position];
	position++;
	first++;
		
	while(!complete && first<size) {
		
		ptos[position].x= find(ptosControl, first).x;
 		ptos[position].y= find(ptosControl, first).y;
 		
 		if(last.x != ptos[position].x || ptos[position].y != ptos[3].y) {
			last= ptos[position];
			position++;
 		}

 		if(position == 4)
 			complete= true;
		else
			first++;
	}
	
	return complete;	
}

void Curva::BezierCubica(std::list<Vertice2D> ptosControl, std::list<Vertice2D> &ptosCurva,
												 std::list<Vertice2D> &ptosTangente, std::list<Vertice2D> &ptosNormal) {

	
  float dt=(float) 1.0 / factorBezier;
	
	std::list<Vertice2D>::iterator it= ptosControl.end();

  float	u, uSquared, uCubed;
  float	uSquaredLess, uCubedLess;
  float c0, c1, c2, c3;
  float dc0, dc1, dc2, dc3;
  float ddc0, ddc1, ddc2, ddc3;
  
  Vertice2D result;
	Vertice2D tangent;
	Vertice2D normal;
	 
	bool end= false; 
	bool last= false; 
	bool complete;
	
	Vertice2D ptos[4];
	unsigned int first= 0;
	
	while(!last) {	 
		complete= load(ptosControl, ptos, first);
		
		for(int i= 0; !end && complete; i++) { 	 	
	 		
	 		u= dt*i;
	 		 			
			uSquared= u * u;
		  uCubed= uSquared * u;
			uSquaredLess= (1-u) * (1-u); 
			uCubedLess= uSquaredLess * (1-u); 
			
			c0= uCubedLess;
			c1= 3 * u * uSquaredLess;
			c2= 3 * uSquared * (1-u);
			c3= uCubed;
			
			dc0= 3 * uSquaredLess;
			dc1= 3 * uSquaredLess - 6 * u * (1-u);
			dc2= 6 * u * (1-u) - 3 * uSquared;
			dc3= 3 * uSquared;

			ddc0= 6 * (1-u);
			ddc1= 6 * (1-u) - 6 * (1-u) + 6 * u;
			ddc2= 6 * (1-u) - 6 * u - 6 * u;
			ddc3= 6 * u;

			result.x= c0*ptos[0].x + c1*ptos[1].x + c2*ptos[2].x + c3*ptos[3].x;
			result.y= c0*ptos[0].y + c1*ptos[1].y + c2*ptos[2].y + c3*ptos[3].y;

			tangent.x= dc0*ptos[0].x + dc1*ptos[1].x + dc2*ptos[2].x + dc3*ptos[3].x;
			tangent.y= dc0*ptos[0].y + dc1*ptos[1].y + dc2*ptos[2].y + dc3*ptos[3].y;
			
			normal.x= ddc0*ptos[0].x + ddc1*ptos[1].x + ddc2*ptos[2].x + ddc3*ptos[3].x;
			normal.y= ddc0*ptos[0].y + ddc1*ptos[1].y + ddc2*ptos[2].y + ddc3*ptos[3].y;

			ptosCurva.push_back(result);
			ptosTangente.push_back(result);
			ptosTangente.push_back(tangent);
			ptosNormal.push_back(result);
			ptosNormal.push_back(normal);
			
		 	std::cout << "result.x: " << result.x << std::endl;
		 	std::cout << "result.y: " << result.y << std::endl;
			std::cout << "tangent.x: " << tangent.x << std::endl;
			std::cout << "tangent.y: " << tangent.y << std::endl;  
			std::cout << "normal.x: " << normal.x << std::endl;
			std::cout << "normal.y: " << normal.y << std::endl;  

		 	//Llegamos al P3
		 	if(result.x == ptos[3].x && result.y == ptos[3].y)
		 		end= true;
		}
		
		if((ptos[3].x != it->x || ptos[3].y != it->y) && ((ptosControl.size() - first) >= 4))
			end= false;
		else
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

void Curva::Bspline(std::list<Vertice2D> ptosControl, VertexList *curva) {

	if (ptosControl.size() >= 4) {

		float base_u[4]; //tiene (u^3, u^2, u, 1)

		const int B[][4] = { { -1 , 3 , -3 , 1 },
							{ 3 , -6 , 3 , 0 },
							{ -3 , 0 , 3 , 0 },
							{ 1 , 4 , 1 , 0 }
						  };

		Vertice2D puntos[4];

		VertexList::iterator it = ptosControl.begin();

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

				curva->push_back(v);	//agrego el vertice a la curva

			}
		}
	}
}
