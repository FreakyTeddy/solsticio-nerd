//#include <iostream>
//#include "transformacion2D.h"
//
//#define ANCHO 800
//#define ALTO 600
//
//int main(int argc, char** argv) {
//	
//	std::cout << "-- PRUEBA TRANSFORMACION --" << std::endl;
//	
//	Vertice origen;
//	origen.x= 0;
//	origen.y= 0;
//		
//	//NDC esta normalizado
//	Transform2D transformacion(ANCHO, ALTO, 1, 1, origen);
//	
//	Vertice vert;
//	vert.x= 0.5;
//	vert.y= 0.25;
//
////	MatrizTrans2D matTrans;
////	
////	//Traslado 
////	matTrans.translate2D(0,0);
////	
////	//Roto
////	Vertice pivPt;
////	pivPt.x= 0;
////	pivPt.y= 0;
////	matTrans.rotate2D(0.5, pivPt);
////
////	//Escalo
////	Vertice fixedPt;
////	fixedPt.x= 0;
////	fixedPt.y= 0;
//////	matTrans.scale2D(1, 1, fixedPt);
////
////	//Le paso la matriz a Transformacion	
////	transformacion.setMatTrans(&matTrans);
//	Vertice vertT= transformacion.transformVerts2D(vert);
//
//	std::cout << "x: " << vertT.x << " y: " << vertT.y << std::endl;
//
//	return 0;
//}