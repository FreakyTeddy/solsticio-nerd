#include "transformacion2D.h"

Transform2D::Transform2D(int Wp, int Hp, int Wm, int Hm, Vertice leftDown): 
matTrans(NULL), matView(), matComposite() {
					
	loadMatView(Wp, Hp, Wm, Hm, leftDown);
	matComposite.preMultiply(matView);																					
}

void Transform2D::setMatTrans(MatrizTrans2D* matTrans) {
	
	this->matTrans= matTrans;	
	matComposite.loadIdentity();	
	matComposite.preMultiply(matView);
	matComposite.preMultiply(*matTrans);	
}

void Transform2D::loadMatView(int Wp, int Hp, int Wm, int Hm, Vertice leftDown) {
	
	//Estoy suponiendo que el NDC esta normalizado.
	matView.translate2D(-leftDown.x, -leftDown.y);
		
	//Escalo a la pantalla, respecto del origen
	Vertice origen;
	origen.x= 0;
	origen.y= 0;
	matView.scale2D(Wp/Wm, -Hp/Hm, origen);
	
	//Reflejo en el eje y
	matView.translate2D(0, Hp);
}	

void Transform2D::setMatView(int Wp, int Hp, int Wm, int Hm, Vertice leftDown) {
	
	loadMatView(Wp, Hp, Wm, Hm, leftDown);
	matComposite.loadIdentity();	
	matComposite.preMultiply(matView);
	if(matTrans)
		matComposite.preMultiply(*matTrans);					
}

Vertice Transform2D::transformVerts2D(Vertice vert) {

	std::cout << "x: " << vert.x << " y: " << vert.x << std::endl;

	float** matrizT= matComposite.getMatriz();
	Vertice vertTrans;
		
	vertTrans.x= matrizT[0][0]*vert.x + matrizT[0][1]*vert.y + matrizT[0][2];
	vertTrans.y= matrizT[1][0]*vert.x + matrizT[1][1]*vert.y + matrizT[1][2];
	
	std::cout << "xT: " << vertTrans.x << " yT: " << vertTrans.x << std::endl; 
	
	return vertTrans;
}