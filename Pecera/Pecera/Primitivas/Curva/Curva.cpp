#include "Curva.h"


Curva::Curva(): factorBezier(FACTOR_INICIAL), factorBspline(FACTOR_INICIAL) { }

Vertice& find(std::vector<Vertice> vertices, unsigned int position) {

  std::vector<Vertice>::iterator it= vertices.begin();

  for(unsigned int i= 0; it != vertices.end(); i++, it++) {
    if(i == position)
      break;
  }

  return *it;
} 

bool load(std::vector<Vertice> ptosControl, Vertice ptos[4], unsigned int &first) {

  Vertice last;
  bool complete= false;
  unsigned int position= 0;
  unsigned int size= ptosControl.size();

  ptos[position].x= find(ptosControl, first).x;
  ptos[position].y= find(ptosControl, first).y;
  ptos[position].z= find(ptosControl, first).z;
  last= ptos[position];
  position++;
  first++;

  while(!complete && first<size) {

    ptos[position].x= find(ptosControl, first).x;
    ptos[position].y= find(ptosControl, first).y;
    ptos[position].z= find(ptosControl, first).z;

    if(last.x != ptos[position].x || last.y != ptos[position].y || last.z != ptos[position].z) {
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

void Curva::BezierCubica(std::vector<Vertice> &ptosControl, std::vector<Vertice> &ptosCurva) {

  float dt=(float) 1.0 / factorBezier;
  float uSquared, uCubed;
  float c0Cubed, c1Cubed, c2Cubed, c3Cubed;
  
  Vertice result;
  Vertice normal;
  Vertice last;
  Vertice ptos[4];

  bool complete;
  unsigned int first= 0;

  while((ptosControl.size() - first) >= 4) {
    complete= load(ptosControl, ptos, first);

    for(float u= 0; u<1 && complete; u+=dt) {
      uSquared= u * u;
      uCubed= uSquared * u;

      //Polinomios de Bernstein cubicos
      c0Cubed= -uCubed + 3 * uSquared - 3 * u + 1;
      c1Cubed= 3 * uCubed - 6 * uSquared + 3 * u;
      c2Cubed= -3 * uCubed + 3 * uSquared;
      c3Cubed= uCubed;

      result.x= c0Cubed*ptos[0].x + c1Cubed*ptos[1].x + c2Cubed*ptos[2].x + c3Cubed*ptos[3].x;
      result.y= c0Cubed*ptos[0].y + c1Cubed*ptos[1].y + c2Cubed*ptos[2].y + c3Cubed*ptos[3].y;
      result.z= c0Cubed*ptos[0].z + c1Cubed*ptos[1].z + c2Cubed*ptos[2].z + c3Cubed*ptos[3].z;
      ptosCurva.push_back(result);

      //acumulo para calcular la diferencia
      last= result;
    }
  } //fin while



}

void Curva::setFactorBezier(int cantidad) {

        factorBezier= cantidad;

        if(factorBezier <= FACTOR_MIN)
                factorBezier= FACTOR_MIN;
        if(factorBezier > FACTOR_MAX)
                factorBezier= FACTOR_MAX;
}

bool loadBspline(std::vector<Vertice> ptosControl, Vertice ptos[4], unsigned int first) {

  unsigned int size= ptosControl.size();

  for(unsigned int i= 0; (i < 4) && ((size-first) > 3); i++) {
    ptos[i].x= find(ptosControl, first+i).x;
    ptos[i].y= find(ptosControl, first+i).y;
    ptos[i].z= find(ptosControl, first+i).z;
  }

  return ((size-first) > 3);
}

void Curva::Bspline(std::vector<Vertice> &ptosControl, std::vector<Vertice> &ptosCurva) {

	 ptosCurva.clear();
	 double dt=(float) 1.0 / factorBspline;

	 double uSquared, uCubed;
	 double Bn2Cubed, Bn1Cubed, B0Cubed, B1Cubed;

	 Vertice curve;
	 Vertice ptos[4];
	 unsigned int size = ptosControl.size();

//mientras haya 4 puntos para procesar
	 for ( unsigned int first = 0; size - first >=4; first++) {
		 for (int i=0; i<4; i++)
			 ptos[i] = ptosControl[first+i];  //cargo el vector con el que trabajo

		 for(double u= 0; u<1; u+=dt) {

		   uSquared= u * u;
		   uCubed= uSquared * u;

		   //Bases cubicas
		   Bn2Cubed= (-uCubed + 3 * uSquared - 3 * u + 1 )/6;
		   Bn1Cubed= ( 3 * uCubed - 6 * uSquared + 4 )/6;
		   B0Cubed= ( -3 * uCubed + 3 * uSquared + 3 * u + 1 )/6;
		   B1Cubed= uCubed/6;

		   curve = ptos[0] * Bn2Cubed + ptos[1] * Bn1Cubed + ptos[2] * B0Cubed + ptos[3] * B1Cubed;
		   ptosCurva.push_back(curve);

		 }
	 }
}

void Curva::Bspline(std::vector<float> &ptosControl, std::vector<float> &ptosCurva) {

	ptosCurva.clear();
	float dt=(float) 1.0 / factorBspline;

	float uSquared, uCubed;
	float Bn2Cubed, Bn1Cubed, B0Cubed, B1Cubed;

	float curve;

  	float ptos[4];
  	unsigned int size = ptosControl.size();;
  	for ( unsigned int first = 0; size - first >=4; first++) {

		for(unsigned int i= 0; i < 4; i++)
				 ptos[i] = ptosControl[first+i];

		for(float u= 0; u<1; u+=dt) {

		  uSquared= u * u;
		  uCubed= uSquared * u;

		  //Bases cubicas
		  Bn2Cubed= (-uCubed + 3 * uSquared - 3 * u + 1 )/6;
		  Bn1Cubed= ( 3 * uCubed - 6 * uSquared + 4 )/6;
		  B0Cubed= ( -3 * uCubed + 3 * uSquared + 3 * u + 1 )/6;
		  B1Cubed= uCubed/6;

	      curve = ptos[0] * Bn2Cubed + ptos[1] * Bn1Cubed + ptos[2] * B0Cubed + ptos[3] * B1Cubed;
		  ptosCurva.push_back(curve);

		}
	}
}

void Curva::setFactor(int cantidad) {
/* 4 es el parametro por default */
  factorBspline = cantidad;

  if(factorBspline < FACTOR_MIN)
    factorBspline= FACTOR_MIN;
  if(factorBspline > FACTOR_MAX)
    factorBspline= FACTOR_MAX;
}
