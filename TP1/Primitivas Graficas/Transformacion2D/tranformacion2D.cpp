#include "transformacion2D.h"

Transform2D::Transform2D(): matTrans(NULL) {}

void Transform2D::setMatTrans(MatrizTrans2D* matTrans) {
		
		this->matTrans= matTrans;
}

Vertice Transform2D::transformVerts2D(Vertice vert) {
	
	Vertice vertTrans;
	
	if(matTrans) {
		float** matrizT= matTrans->getMatriz();
		
		vertTrans.x= matrizT[0][0]*vert.x + matrizT[0][1]*vert.y + matrizT[0][2];
		vertTrans.y= matrizT[1][0]*vert.x + matrizT[1][1]*vert.y + matrizT[1][2];
	}
	return vertTrans;
}