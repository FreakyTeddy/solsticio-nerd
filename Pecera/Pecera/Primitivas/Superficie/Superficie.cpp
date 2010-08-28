/*
 * Superficie.cpp
 *
 *  Created on: 28/08/2010
 *      Author: luuu
 */

#include "Superficie.h"

Superficie::Superficie() {
	// TODO Auto-generated constructor stub

}

Superficie::~Superficie() {
	// TODO Auto-generated destructor stub
}

void Superficie::dibujar() {

	std::vector<Vertice>::iterator it0;
	std::vector<Vertice>::iterator it1;

	it0 = superficie.begin();
	it1 = superficie.begin();
	it1 += tam;

	while (it1 != superficie.end()) {
		glBegin(GL_TRIANGLE_STRIP);

		for(unsigned int pos=0 ; pos <  tam-1 ; pos++) {
			glColor3f(0,(float)pos/tam,(float)pos/tam);
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


