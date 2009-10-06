#ifndef MATRIZTRANS2D_H_
#define MATRIZTRANS2D_H_

#include <math.h>
#include "matriz.h"
#include "../../Vertice.h"

#define DIMENSION 3

class MatrizTrans2D: public Matriz {

	public:
		MatrizTrans2D();
		
		/* Premultiplica la matrizTrans2D por una matriz de translacion
		 * construida a partir de los parametro tx, ty.
		 * */
		void translate2D(float tx, float ty);

		/* Premultiplica la matrizTrans2D por una matriz de rotacion
		 * construida a partir del angulo theta. Se controla la 
		 * localizacion del objeto eligiendo un punto pivote, sobre el
		 * cual el objeto va hacer rotado.
		 * */
		void rotate2D(float theta, Vertice pivPt);		

		/* Premultiplica la matrizTrans2D por una matriz de escalado
		 * construida a partir de los parametro sx, sy. Se controla
		 * la localizacion del objeto eligiendo un punto fijo, que
		 * permanece sin cambios luego de la transformacion de escala.
		 * */
		void scale2D(float sx, float sy, Vertice fixedPt);		
}; 

#endif /*MATRIZTRANS2D_H_*/
