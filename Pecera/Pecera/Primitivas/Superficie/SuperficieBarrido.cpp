#include "SuperficieBarrido.h"
#include <iostream>
SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl) {

	tam = forma.size(); //guardo la long de la curva patron

	//guardo la malla de vertices de la superficie formada
	Vertice v;
	for(unsigned int pos=0 ; pos <  tam ; pos++) {
		v.x = forma[pos].x;
		v.y = forma[pos].y;
		v.z = forma[pos].z;
		superficie.push_back(v);
	}
	//aplico traslacion
	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v.x = forma[pos].x + trasl[i].x;
			v.y = forma[pos].y + trasl[i].y;
			v.z = forma[pos].z + trasl[i].z;
			superficie.push_back(v);
		}
	}
//calculo de normales


}

SuperficieBarrido::~SuperficieBarrido() {
	// TODO Auto-generated destructor stub
}


void SuperficieBarrido::dibujar() {

	std::vector<Vertice>::iterator it0;
	std::vector<Vertice>::iterator it1;

	it0 = superficie.begin();
	it1 = superficie.begin();
	it1 += tam;

	while (it1 != superficie.end()) {
		std::cout<<"while - "<<std::endl;
		glBegin(GL_TRIANGLE_STRIP);

		for(unsigned int pos=0 ; pos <  tam-1 ; pos++) {
		//	std::cout<<pos<<" - ";
			glColor3f((float)pos/tam,0,(float)pos/tam);
			glVertex3f(it0->x,it0->y,it0->z);
			glVertex3f(it1->x,it1->y,it1->z);
			it1++;
			glVertex3f(it1->x,it1->y,it1->z);

			glColor3f((float)pos/tam,1,(float)pos/tam);
			glVertex3f(it0->x,it0->y,it0->z);
			glVertex3f(it1->x,it1->y,it1->z);
			it0++;
			glVertex3f(it0->x,it0->y,it0->z);
		}
		glEnd();
		it1++; it0++;
	}
}

