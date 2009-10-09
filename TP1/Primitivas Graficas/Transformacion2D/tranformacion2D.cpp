#include "transformacion2D.h"

Transform2D::Transform2D(): 
matTrans(NULL), matView(), matComposite() {

	matView.loadIdentity();						
	matComposite.loadIdentity();	
}

void Transform2D::setIdentity() {

	matView.loadIdentity();						
	matComposite.loadIdentity();		
}

void Transform2D::setMatTrans(MatrizTrans2D* matTrans) {
	
	this->matTrans= matTrans;	
	matComposite.loadIdentity();	
	matComposite.preMultiply(matView);	
	matComposite.preMultiply(*matTrans);
}

void Transform2D::loadMatView(int Wp, int Hp, int Wm, int Hm, Vertice leftDown) {
	//Reflejo en el eje y

	//Escalo a la pantalla, respecto del origen
	Vertice origen;
	origen.x= 0;
	origen.y= 0;
	matView.scale2D((float)Wp/Wm, (float)-Hp/Hm, origen);

	//Estoy suponiendo que el NDC esta normalizado.
	matView.translate2D(ANCHO/2,ALTO/2);/*(400,300);*///-leftDown.x, -leftDown.y);500,400
}	

void Transform2D::setMatView(int Wp, int Hp, int Wm, int Hm, Vertice leftDown) {
	
	loadMatView(Wp, Hp, Wm, Hm, leftDown);
	matComposite.loadIdentity();	

	if(matTrans)
	     matComposite.preMultiply(*matTrans);		
	matComposite.preMultiply(matView);
}

Vertice Transform2D::transformVerts2D(Vertice vert) {

	float** matrizT= matComposite.getMatriz();
	Vertice vertTrans;
		
	vertTrans.x= matrizT[0][0]*vert.x + matrizT[0][1]*vert.y + matrizT[0][2];
	vertTrans.y= matrizT[1][0]*vert.x + matrizT[1][1]*vert.y + matrizT[1][2];
	
	return vertTrans;
}
