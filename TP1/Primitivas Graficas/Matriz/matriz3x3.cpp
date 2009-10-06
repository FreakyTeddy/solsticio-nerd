#include "matriz3x3.h"

Matriz3x3::Matriz3x3() {

	loadIdentity(matTrans2D);	
}

void Matriz3x3::loadIdentity(float matrix[3][3]) {
	
	for(int row= 0; row<3; row++) {
		for(int col= 0; col<3; col++)
			matrix[row][col]= (row == col);
	}
}

void Matriz3x3::preMultiply(float mat1[3][3], float mat2[3][3]) {

	float matTemp[3][3];

	for(int row= 0; row<3; row++) {
		for(int col= 0; col<3; col++)
			matTemp[row][col]= (row == col);
	}
	
	for(int row= 0; row<3; row++) {
		for(int col= 0; col<3; col++)
			mat2[row][col]= matTemp[row][col];
	}	
}

void Matriz3x3::translate2D(float tx, float ty) {
	
	float matTrans[3][3];
	loadIdentity(matTrans);
	
	matTrans[0][2]= tx;
	matTrans[1][2]= ty;
	
	preMultiply(matTrans, matTrans2D);
}		

void Matriz3x3::rotate2D(float pivot, float theta) {
	
	float matRot[3][3];
	loadIdentity(matRot);

	matRot[0][0]= cos(theta);
	matRot[0][1]= -sin(theta);
	matRot[0][2]= pivot*(1-cos(theta)) + pivot*sin(theta);
	matRot[1][0]= sin(theta);
	matRot[1][1]= cos(theta);
	matRot[1][2]= pivot*(1-cos(theta)) - pivot*sin(theta);	

	preMultiply(matRot, matTrans2D);
}		

void Matriz3x3::scale2D(float sx, float sy, float fixedPt) {

	float matScale[3][3];
	loadIdentity(matScale);

	matScale[0][0]= sx;
	matScale[0][2]= (1-sx)*fixedPt;
	matScale[1][1]= sy;
	matScale[1][2]= (1-sx)*fixedPt;
	
	preMultiply(matScale, matTrans2D);
}		


		