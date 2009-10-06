#ifndef MATRIZ3X3_H_
#define MATRIZ3X3_H_

#include <math.h>

class Matriz3x3 {

	private:
		float matTrans2D[3][3];
	
		void loadIdentity(float matrix[3][3]);
		void preMultiply(float mat1[3][3], float mat2[3][3]);
	
	public:
		
		Matriz3x3();
		
		void translate2D(float tx, float ty);
		void rotate2D(float pivot, float theta);		
		void scale2D(float sx, float sy, float fixedPt);		
		
		float** getMatTrans2D();
};

#endif /*MATRIZ3X3_H_*/
