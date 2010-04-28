#include "Curva.h"


Curva::Curva(): factorBezier(FACTOR_INICIAL), factorBspline(FACTOR_INICIAL) { };

Vertice& find(std::list<Vertice> vertices, unsigned int position) {

  std::list<Vertice>::iterator it= vertices.begin();

  for(unsigned int i= 0; it != vertices.end(); i++, it++) {
    if(i == position)
      break;
  }

  return *it;
} 

bool load(std::list<Vertice> ptosControl, Vertice ptos[4], unsigned int &first) {

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

void Curva::BezierCubica(std::list<Vertice> ptosControl, std::list<Vertice> &ptosCurva,
						std::list<Vertice> &ptosNormal,	std::map<int, Vertice> &distancia, int factor) {

  float dt=(float) 1.0 / factorBezier;

  longitudBezier= 0.0;
  Vertice last;
  bool begin= true;

  float uSquared, uCubed;
  float c0Cubed, c1Cubed, c2Cubed, c3Cubed;
  
  Vertice result;
  Vertice tangent;
  Vertice normal;

  bool complete;

  Vertice ptos[4];
  unsigned int first= 0;

  while((ptosControl.size() - first) >= 4) {
    complete= load(ptosControl, ptos, first);

    for(float u= 0; u<=1 && complete; u+=dt) {
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

      if(!begin) {
        longitudBezier+= sqrtf(powf(result.x-last.x, 2) + powf(result.y-last.y, 2));
        distancia.insert( std::pair<int,Vertice>(longitudBezier*factor,last) );
      } else
        begin= !begin;

      //acumulo para calcular la diferencia
      last= result;
    }
  } //fin while


  /* normales */
  if (ptosCurva.size() > 2) {
	  ptosNormal.clear();
	  std::list<Vertice>::iterator prev = ptosCurva.begin();
	  std::list<Vertice>::iterator it = ptosCurva.begin();
	  std::list<Vertice>::iterator next = ptosCurva.begin();
	  Vertice v;
	  //primer punto
	  next++;
	  //resta (next - prev)
	  v.x = next->x - prev->x;
	  v.y = next->y - prev->y;

	  // z x resta -->producto vectorial
	  float aux = 0 - v.y;
	  v.y = v.x;
	  v.x = aux;

	  //push it, push normal
	  ptosNormal.push_back(*it);
	  ptosNormal.push_back(v);

	  //caso general
	  do {
		  next++;
		  it++;

		  //resta (next - prev)
		  v.x = next->x - prev->x;
		  v.y = next->y - prev->y;

		  // z x resta -->producto vectorial
		  aux = 0 - v.y;
		  v.y = v.x;
		  v.x = aux;

		  //push it, push normal
		  ptosNormal.push_back(*it);
		  ptosNormal.push_back(v);

		  prev++;
	  } while (next != ptosCurva.end());

	  //ultimo punto
	  it++;

	  //resta (next - prev)
	  v.x = next->x - prev->x;
	  v.y = next->y - prev->y;

	  // z x resta -->producto vectorial
	  aux = 0 - v.y;
	  v.y = v.x;
	  v.x = aux;

	  //push it, push normal
	  ptosNormal.push_back(*it);
	  ptosNormal.push_back(v);
  }
}

void Curva::modificarFactorBezier(int cantidad) {

        factorBezier+= cantidad;

        if(factorBezier <= FACTOR_MIN)
                factorBezier= 1;
        if(factorBezier > FACTOR_MAX)
                factorBezier= FACTOR_MAX;
}

bool loadBspline(std::list<Vertice> ptosControl, Vertice ptos[4], unsigned int first) {

  unsigned int size= ptosControl.size();

  for(unsigned int i= 0; (i < 4) && ((size-first) > 3); i++) {
    ptos[i].x= find(ptosControl, first+i).x;
    ptos[i].y= find(ptosControl, first+i).y;
    ptos[i].z= find(ptosControl, first+i).z;
  }

  return ((size-first) > 3);
}

void Curva::Bspline(std::list<Vertice> ptosControl, std::list<Vertice> &ptosCurva) {

  float dt=(float) 1.0 / factorBspline;

  float uSquared, uCubed;
  float Bn2Cubed, Bn1Cubed, B0Cubed, B1Cubed;

  Vertice curve;
  Vertice tangent;
  Vertice normal;

  bool complete;

  Vertice ptos[4];
  unsigned int first= 0;

  while((ptosControl.size() - first) >= 4) {
    complete= loadBspline(ptosControl, ptos, first);
    first++;

    for(float u= 0; u<=1 && complete; u+=dt) {

      uSquared= u * u;
      uCubed= uSquared * u;

      //Bases cubicas
      Bn2Cubed= (-uCubed + 3 * uSquared - 3 * u + 1 )/6;
      Bn1Cubed= ( 3 * uCubed - 6 * uSquared + 4 )/6;
      B0Cubed= ( -3 * uCubed + 3 * uSquared + 3 * u + 1 )/6;
      B1Cubed= uCubed/6;

      curve.x= Bn2Cubed*ptos[0].x + Bn1Cubed*ptos[1].x + B0Cubed*ptos[2].x + B1Cubed*ptos[3].x;
      curve.y= Bn2Cubed*ptos[0].y + Bn1Cubed*ptos[1].y + B0Cubed*ptos[2].y + B1Cubed*ptos[3].y;
      curve.z= Bn2Cubed*ptos[0].z + Bn1Cubed*ptos[1].z + B0Cubed*ptos[2].z + B1Cubed*ptos[3].z;
      ptosCurva.push_back(curve);

    }
  }
}

void Curva::modificarFactorBspline(int cantidad) {

  factorBspline+= cantidad;

  if(factorBspline <= FACTOR_MIN)
    factorBspline= 1;
  if(factorBspline > FACTOR_MAX)
    factorBspline= FACTOR_MAX;
}
