#include "Superficie.h"

unsigned int Superficie::render_mode = GL_TRIANGLE_STRIP;

Superficie::Superficie() {}

Superficie::~Superficie() {}

void Superficie::dibujar() {

	std::vector<Vertice>::iterator it0;
	std::vector<Vertice>::iterator it1;

	it0 = superficie.begin();
	it1 = superficie.begin();
	it1 += tam;

	if (render_mode == GL_LINE_LOOP) {
		glDisable(GL_LIGHTING);
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
		glEnable(GL_LIGHTING);
	} else {
		glColor3f(1,1,1);
		glEnableClientState (GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT,0,&(superficie[0]));
		//glNormalPointer();
		unsigned int cols = (superficie.size()/tam) -1;
		for(unsigned int i=0 ; i <  cols ; i++)
			glDrawElements(render_mode, tam*2, GL_UNSIGNED_INT, &(indices[i*tam*2]));
		glDisableClientState (GL_VERTEX_ARRAY);
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

void Superficie::setIndices() {

	GLuint it0=0, it1=0;
	GLuint longitud = superficie.size();
	indices.clear();

	for (it1 = tam; it1 < longitud; it0++, it1++) {
		indices.push_back(it0);
		indices.push_back(it1);
		for(unsigned int pos=0 ; pos <  tam-1 ; pos++) {
			it0++;
			indices.push_back(it0);
			it1++;
			indices.push_back(it1);
		}
	}
}

void Superficie::setNormales() {
/*
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
*/
	




}

void Superficie::setTextura() {//TODO
}

void Superficie::init() {
	
	setIndices();
	//setNormales();
	//setTextura();	
	
}



