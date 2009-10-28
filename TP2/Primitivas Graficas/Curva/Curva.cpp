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
  float c0Cubed, c1Cubed, c2Cubed, c3Cubed;
  
  float c0Squared, c1Squared, c2Squared;
  float deltab0x, deltab1x, deltab2x, deltab0y, deltab1y, deltab2y;
  float ducx, ducy;  

  float c0, c1;
  float delta2b0x, delta2b1x, delta2b0y, delta2b1y;
  float dducx, dducy;  
  
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
			
			//Polinomios de Bernstein cubicos 
			c0Cubed= -uCubed + 3 * uSquared - 3 * u + 1;
			c1Cubed= 3 * uCubed - 6 * uSquared + 3 * u;
			c2Cubed= -3 * uCubed + 3 * uSquared;
			c3Cubed= uCubed;

			result.x= c0Cubed*ptos[0].x + c1Cubed*ptos[1].x + c2Cubed*ptos[2].x + c3Cubed*ptos[3].x;
			result.y= c0Cubed*ptos[0].y + c1Cubed*ptos[1].y + c2Cubed*ptos[2].y + c3Cubed*ptos[3].y;
			ptosCurva.push_back(result);

			//Derivada primera - Tangente			
			//Polinomios de Bernstein cuadraticos 
			c0Squared= uSquared - 2 * u + 1;
			c1Squared= -2 * uSquared + 2 * u;
			c2Squared= uSquared;

			deltab0x= ptos[1].x - ptos[0].x;
			deltab1x= ptos[2].x - ptos[1].x;
			deltab2x= ptos[3].x - ptos[2].x;
			deltab0y= ptos[1].y - ptos[0].y;
			deltab1y= ptos[2].y - ptos[1].y;
			deltab2y= ptos[3].y - ptos[2].y;

			ducx= 6 * ((deltab0x * c0Squared) + (deltab1x * c1Squared) + (deltab2x * c2Squared));   
			ducy= 6 * ((deltab0y * c0Squared) + (deltab1y * c1Squared) + (deltab2y * c2Squared));   

			tangent.x= ducx * (ptos[0].x + ptos[1].x + ptos[2].x + ptos[3].x);
			tangent.y= ducy * (ptos[0].y + ptos[1].y + ptos[2].y + ptos[3].y);
			ptosTangente.push_back(result);
			ptosTangente.push_back(tangent);

			//Derivada segunda - Normal
			//Polinomios de Bernstein lineal 
			c0= 1 - u;
			c1= u;

			delta2b0x= deltab1x - deltab0x;
			delta2b1x= deltab2x - deltab1x;
			delta2b0y= deltab1y - deltab0y;
			delta2b1y= deltab2y - deltab1y;

			dducx= 3 * ((delta2b0x * c0) + (delta2b1x * c1));   
			dducy= 3 * ((delta2b0y * c0) + (delta2b1y * c1));   
			
			normal.x= dducx * (ptos[0].x + ptos[1].x + ptos[2].x);
			normal.y= dducy * (ptos[0].y + ptos[1].y + ptos[2].y);

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
