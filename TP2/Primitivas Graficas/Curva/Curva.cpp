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
                         std::map<int, Ubicacion> &distancia, int factor) {

  float dt=(float) 1.0 / factorBezier;

  longitudBezier= 0.0;
  Vertice last;
  bool begin= true;

  float uSquared, uCubed;
  float c0Cubed, c1Cubed, c2Cubed, c3Cubed;
  
  float c0Squared, c1Squared, c2Squared;
  float deltab0x, deltab1x, deltab2x, deltab0y, deltab1y, deltab2y, deltab0z, deltab1z, deltab2z;
  float ducx, ducy, ducz;  

  float c0, c1;
  float delta2b0x, delta2b1x, delta2b0y, delta2b1y, delta2b0z, delta2b1z;
  float dducx, dducy, dducz;  
  
  Vertice result;
  Vertice tangent;
  Vertice normal;
  Ubicacion ubicacion;

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
      deltab0z= ptos[1].z - ptos[0].z;
      deltab1z= ptos[2].z - ptos[1].z;
      deltab2z= ptos[3].z - ptos[2].z;

      ducx= 6 * ((deltab0x * c0Squared) + (deltab1x * c1Squared) + (deltab2x * c2Squared));
      ducy= 6 * ((deltab0y * c0Squared) + (deltab1y * c1Squared) + (deltab2y * c2Squared));
      ducz= 6 * ((deltab0z * c0Squared) + (deltab1z * c1Squared) + (deltab2z * c2Squared));

      tangent.x= ducx * (ptos[0].x + ptos[1].x + ptos[2].x + ptos[3].x);
      tangent.y= ducy * (ptos[0].y + ptos[1].y + ptos[2].y + ptos[3].y);
      tangent.z= ducz * (ptos[0].z + ptos[1].z + ptos[2].z + ptos[3].z);


      //Derivada segunda - Normal
      //Polinomios de Bernstein lineal
      c0= 1 - u;
      c1= u;

      delta2b0x= deltab1x - deltab0x;
      delta2b1x= deltab2x - deltab1x;
      delta2b0y= deltab1y - deltab0y;
      delta2b1y= deltab2y - deltab1y;
      delta2b0z= deltab1z - deltab0z;
      delta2b1z= deltab2z - deltab1z;

      dducx= 3 * ((delta2b0x * c0) + (delta2b1x * c1));
      dducy= 3 * ((delta2b0y * c0) + (delta2b1y * c1));
      dducz= 3 * ((delta2b0z * c0) + (delta2b1z * c1));

      normal.x= dducx * (ptos[0].x + ptos[1].x + ptos[2].x);
      normal.y= dducy * (ptos[0].y + ptos[1].y + ptos[2].y);
      normal.z= dducz * (ptos[0].z + ptos[1].z + ptos[2].z);

      if(!begin) {
        longitudBezier+= sqrtf(powf(result.x-last.x, 2) + powf(result.y-last.y, 2));
        //ver!!!
        normal.x -= last.x;
        normal.y -= last.y;
        normal.z -= last.z;
        tangent.x -=last.x;
        tangent.y -=last.y;
        tangent.z -=last.z;
        ubicacion.punto_curva = last;
        ubicacion.punto_normal = normal;
        ubicacion.punto_tangente = tangent; //guardo la tg y la normal asociada al punto de la curva
        distancia.insert( std::pair<int,Ubicacion>(longitudBezier*factor,ubicacion) );
      } else
        begin= !begin;

      //acumulo para calcular la diferencia
      last= result;
    }
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

//  float Bn1Squared, B0Squared, B1Squared;
//  float deltab0x, deltab1x, deltab2x, deltab0y, deltab1y, deltab2y, deltab0z, deltab1z, deltab2z;
//  float ducx, ducy, ducz;
//
//  float B0, B1;
//  float delta2b0x, delta2b1x, delta2b0y, delta2b1y, delta2b0z, delta2b1z;
//  float dducx, dducy, dducz;

  Vertice curve;
//  Vertice tangent;
//  Vertice normal;

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

//      //Derivada primera - Tangente
//      //Bases cuadraticas
//      Bn1Squared= ( uSquared - 2 * u + 1)/2;
//      B0Squared= ( -2 * uSquared + 2 * u + 1 )/2;
//      B1Squared= ( uSquared )/2;
//
//      deltab0x= ptos[1].x - ptos[0].x;
//      deltab1x= ptos[2].x - ptos[1].x;
//      deltab2x= ptos[3].x - ptos[2].x;
//      deltab0y= ptos[1].y - ptos[0].y;
//      deltab1y= ptos[2].y - ptos[1].y;
//      deltab2y= ptos[3].y - ptos[2].y;
//      deltab0z= ptos[1].z - ptos[0].z;
//      deltab1z= ptos[2].z - ptos[1].z;
//      deltab2z= ptos[3].z - ptos[2].z;
//
//      ducx= 6 * ((deltab0x * Bn1Squared) + (deltab1x * B0Squared) + (deltab2x * B1Squared));
//      ducy= 6 * ((deltab0y * Bn1Squared) + (deltab1y * B0Squared) + (deltab2y * B1Squared));
//      ducz= 6 * ((deltab0z * Bn1Squared) + (deltab1z * B0Squared) + (deltab2z * B1Squared));
//
//      tangent.x= ducx * (ptos[0].x + ptos[1].x + ptos[2].x + ptos[3].x);
//      tangent.y= ducy * (ptos[0].y + ptos[1].y + ptos[2].y + ptos[3].y);
//      tangent.z= ducz * (ptos[0].z + ptos[1].z + ptos[2].z + ptos[3].z);
//      ptosTangente.push_back(curve);
//      ptosTangente.push_back(tangent);
//
//      //Derivada segunda - Normal
//      //Bases lineales
//      B0= 1 - u;
//      B1= u;
//
//      delta2b0x= deltab1x - deltab0x;
//      delta2b1x= deltab2x - deltab1x;
//      delta2b0y= deltab1y - deltab0y;
//      delta2b1y= deltab2y - deltab1y;
//      delta2b0z= deltab1z - deltab0z;
//      delta2b1z= deltab2z - deltab1z;
//
//      dducx= 3 * ((delta2b0x * B0) + (delta2b1x * B1));
//      dducy= 3 * ((delta2b0y * B0) + (delta2b1y * B1));
//      dducz= 3 * ((delta2b0z * B0) + (delta2b1z * B1));
//
//      normal.x= dducx * (ptos[0].x + ptos[1].x + ptos[2].x);
//      normal.y= dducy * (ptos[0].y + ptos[1].y + ptos[2].y);
//      normal.z= dducz * (ptos[0].z + ptos[1].z + ptos[2].z);
//
//      ptosNormal.push_back(curve);
//      ptosNormal.push_back(normal);
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
