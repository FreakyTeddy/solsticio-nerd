#include "matriz.h"

Matriz::Matriz(int dim): dim(dim) { 

	matriz= new float*[dim];
	for(int i= 0; i < dim; i++) 
		matriz[i] = new float[dim];

	loadIdentity();
}

Matriz::~Matriz() {
	
	if(matriz) {
		for(int i = 0; i<dim; i++) 
			delete[] matriz[i]; 
		delete[] matriz;
	} 
}

void Matriz::loadIdentity() {
	
	for(int row= 0; row<dim; row++) {
		for(int col= 0; col<dim; col++)
			matriz[row][col]= (row == col);
	}
}
		
float** Matriz::getMatriz() {
	
	return matriz;
}

void Matriz::preMultiply(Matriz &mat) {
		
	float** m1= mat.getMatriz();
	
	Matriz matComposite(dim);
	float** matTemp= matComposite.getMatriz();
	
	for(int row= 0; row<dim; row++) {
		for(int col= 0; col<dim; col++)
			matTemp[row][col]= m1[row][0]*matriz[0][col] +
												 m1[row][1]*matriz[1][col] +
												 m1[row][2]*matriz[2][col] ;
	}
	
	for(int row= 0; row<dim; row++) {
		for(int col= 0; col<dim; col++)
			matriz[row][col]= matTemp[row][col] ;
	}
}

void Matriz::postMultiply(Matriz &mat) {
	
	float** m1= mat.getMatriz();
	
	Matriz matComposite(dim);
	float** matTemp= matComposite.getMatriz();
	
	for(int row= 0; row<dim; row++) {
		for(int col= 0; col<dim; col++)
			matTemp[row][col]= matriz[row][0] * m1[0][col] +
												 matriz[row][1] * m1[1][col] +
												 matriz[row][2] * m1[2][col];
	}
	
	for(int row= 0; row<dim; row++) {
		for(int col= 0; col<dim; col++)
			matriz[row][col]= matTemp[row][col] ;
	}
}
