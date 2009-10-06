#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <iostream>

class Matriz {                      
	
	private:
		float** matriz;
		int dim;
	
	protected:
		void preMultiply(Matriz &mat);
					
	public:
		Matriz(int dim);
		~Matriz();
		void loadIdentity();
		float** getMatriz();
};

#endif /*MATRIZ_H_*/
