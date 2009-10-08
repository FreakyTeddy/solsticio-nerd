#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <iostream>

class Matriz {                      
	
	private:
		float** matriz;
		int dim;
					
	public:
		Matriz(int dim);
		~Matriz();
		void loadIdentity();
		void preMultiply(Matriz &mat);
		void postMultiply(Matriz &mat);
		float** getMatriz();
};

#endif /*MATRIZ_H_*/
