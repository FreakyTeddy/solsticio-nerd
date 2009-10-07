#include "matrizTrans2D.h"

MatrizTrans2D::MatrizTrans2D(): Matriz::Matriz(DIMENSION) { }
		
void MatrizTrans2D::translate2D(float tx, float ty) {
	
	Matriz matTrans(DIMENSION);
	float** matT= matTrans.getMatriz();
	matT[0][2]= tx;
	matT[1][2]= ty;
	
	preMultiply(matTrans);
}

void MatrizTrans2D::rotate2D(float theta, Vertice pivPt) {
	
	Matriz matRot(DIMENSION);
	float** matR= matRot.getMatriz();

	matR[0][0]= cos(theta);
	matR[0][1]= -sin(theta);
	matR[0][2]= pivPt.x*(1-cos(theta)) + pivPt.y*sin(theta);
	matR[1][0]= sin(theta);
	matR[1][1]= cos(theta);
	matR[1][2]= pivPt.y*(1-cos(theta)) - pivPt.x*sin(theta);	

	preMultiply(matRot);
}		

void MatrizTrans2D::scale2D(float sx, float sy, Vertice fixedPt) {
	
	Matriz matScale(DIMENSION);
	float** matS= matScale.getMatriz();

	matS[0][0]= sx;
	matS[0][2]= (1-sx)*fixedPt.x;
	matS[1][1]= sy;
	matS[1][2]= (1-sy)*fixedPt.y;
	
	preMultiply(matScale);
}	