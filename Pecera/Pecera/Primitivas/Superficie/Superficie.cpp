/*
 * Superficie.cpp
 *
 *  Created on: 28/08/2010
 *      Author: luuu
 */

#include "Superficie.h"

unsigned int Superficie::render_mode = GL_TRIANGLE_STRIP;

Superficie::Superficie() {}

Superficie::~Superficie() {}

void Superficie::dibujar() {
//VER optimizacion con arrayvertex :)
	std::vector<Vertice>::iterator it0;
	std::vector<Vertice>::iterator it1;

	it0 = superficie.begin();
	it1 = superficie.begin();
	it1 += tam;

	if (render_mode == GL_LINE_LOOP) {
		while (it1 != superficie.end()) {
			for(unsigned int pos=0 ; pos <  tam-1 ; pos++) {
				glBegin(GL_LINE_LOOP);
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

				glEnd();
			}
			it1++; it0++;
		}
	} else {
		while (it1 != superficie.end()) {
			glBegin(render_mode);
			glVertex3f(it0->x,it0->y,it0->z);
			glVertex3f(it1->x,it1->y,it1->z);
			for(unsigned int pos=0 ; pos <  tam-1 ; pos++) {
				glColor3f(0,(float)pos/tam,(float)pos/tam);
				it0++;
				glVertex3f(it0->x,it0->y,it0->z);
				it1++;
				glVertex3f(it1->x,it1->y,it1->z);
			}
			glEnd();
			it1++; it0++;
		}
	}
}

void Superficie::nextMode() {
	if (render_mode == GL_TRIANGLE_STRIP) {
		render_mode = GL_QUAD_STRIP;
	}else if (render_mode == GL_QUAD_STRIP) {
		render_mode = GL_LINE_LOOP;
	}else if (render_mode == GL_LINE_LOOP) {
		render_mode = GL_TRIANGLE_STRIP;
	}
}

void Superficie::getNormales(std::vector<Vertice> &ptosCurva, std::vector<Vertice> &ptosNormal) {
	 /* normales */
	  if (ptosCurva.size() > 2) {
		  ptosNormal.clear();
		  std::vector<Vertice>::iterator prev = ptosCurva.begin();
		  std::vector<Vertice>::iterator it = ptosCurva.begin();
		  std::vector<Vertice>::iterator next = ptosCurva.begin();
		  Vertice v;
		  //primer punto
		  next++;
		  //resta (next - prev)
		  v.x = next->x - prev->x;
		  v.y = next->y - prev->y;

		  // z x resta -->producto vectorial
		  float aux = 0 - v.y;
		  v.y = v.x;
		  v.x = aux;

		  //push it, push normal
		  ptosNormal.push_back(*it);
		  ptosNormal.push_back(v);

		  //caso general
		  do {
			  next++;
			  it++;

			  //resta (next - prev)
			  v.x = next->x - prev->x;
			  v.y = next->y - prev->y;

			  // z x resta -->producto vectorial
			  aux = 0 - v.y;
			  v.y = v.x;
			  v.x = aux;

			  //push it, push normal
			  ptosNormal.push_back(*it);
			  ptosNormal.push_back(v);

			  prev++;
		  } while (next != ptosCurva.end());

		  //ultimo punto
		  it++;

		  //resta (next - prev)
		  v.x = next->x - prev->x;
		  v.y = next->y - prev->y;

		  // z x resta -->producto vectorial
		  aux = 0 - v.y;
		  v.y = v.x;
		  v.x = aux;

		  //push it, push normal
		  ptosNormal.push_back(*it);
		  ptosNormal.push_back(v);
	  }
}





