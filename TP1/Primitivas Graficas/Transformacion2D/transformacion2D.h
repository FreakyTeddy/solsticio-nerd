#ifndef TRANSFORMACION2D_H_
#define TRANSFORMACION2D_H_

#include "Matriz/matrizTrans2D.h"
#include "../Vertice.h"

class Transform2D {
	
	private:
		MatrizTrans2D* matTrans;
	
	public:
		Transform2D();
		void setMatTrans(MatrizTrans2D* matTrans);
		Vertice transformVerts2D(Vertice vert);
};

#endif /*TRANSFORMACION2D_H_*/
