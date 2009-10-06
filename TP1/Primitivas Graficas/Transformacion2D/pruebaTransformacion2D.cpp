#include <iostream>
#include "transformacion2D.h"

int main(int argc, char** argv) {
	
	std::cout << "-- PRUEBA TRANSFORMACION --" << std::endl;
	
	Transform2D transformacion;
	
	Vertice vert;
	vert.x= 1;
	vert.y= 0;

	MatrizTrans2D matTrans;
	
	//Traslado 
	matTrans.translate2D(0,0);
	
	//Roto
	Vertice pivPt;
	pivPt.x= 0;
	pivPt.y= 0;
	matTrans.rotate2D(0.5, pivPt);

	//Escalo
	Vertice fixedPt;
	fixedPt.x= 0;
	fixedPt.y= 0;
//	matTrans.scale2D(1, 1, fixedPt);

	//Le paso la matriz a Transformacion	
	transformacion.setMatTrans(&matTrans);
	Vertice vertT= transformacion.transformVerts2D(vert);

	std::cout << "x: " << vertT.x << " y: " << vertT.y << std::endl;

	return 0;
}