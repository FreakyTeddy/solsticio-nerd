#include "Superficie.h"
unsigned int Superficie::render_mode = GL_TRIANGLE_STRIP;

GLfloat mat_diffuse[] = { 1.0, 0.50, 0.0,0.70 };
GLfloat mat_specular[] = { 1.0, 0.90, 0.0,0.7 };//material de la esfera
GLfloat mat_shininess[] = { 100.0 };

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
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //material
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glEnableClientState (GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &(superficie[0]));
		glNormalPointer(GL_FLOAT,0, &(normales[0]));
		unsigned int cols = (superficie.size()/tam) -1;
		for(unsigned int i=0 ; i <  cols ; i++)
			glDrawElements(render_mode, tam*2, GL_UNSIGNED_INT, &(indices[i*tam*2]));
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState (GL_VERTEX_ARRAY);

	}
//	it1 = normales.begin();
//	//dibujo las normales
//	glDisable(GL_LIGHTING);
//	glBegin(GL_LINES);
//	glColor3f(1,1,1); Vertice v;
//	for(it0 =superficie.begin(); it0 != superficie.end() ; it0++, it1++) {
//			v = (*it0) + (*it1);
//			glVertex3f(it0->x,it0->y,it0->z);
//			glVertex3f(v.x,v.y,v.z);
//	}
//	glEnd();
//	glEnable(GL_LIGHTING);
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

	normales.clear();
	unsigned int curr=0;
	Vertice normal, v, q;

	/**************** primer curva **********************/

	/* Primer vertice */
	v = superficie[curr+tam] - superficie[curr];
	q = superficie[curr+1] - superficie[curr];
	normales.push_back(v.normal(q));

	/* Vertices intermedios */

	for (curr = 1; curr < tam-1; curr++) {
		v = superficie[curr-1] - superficie[curr];
		q = superficie[curr+tam] - superficie[curr];
		normal = v.normal(q);
		v = superficie[curr+1] - superficie[curr];
		normal += q.normal(v);
		normales.push_back(normal.normalizar());
	}

	/* ultimo vertice */
	v = superficie[curr-1] - superficie[curr];
	q = superficie[curr+tam] - superficie[curr];
	normal = v.normal(q);
	normales.push_back(normal.normalizar());

	/**************** curvas intermedias **********************/

	if (superficie.size()/tam >2) {
		//para todas las curvas intermedias:

		for (unsigned int curva = 1; curva < (superficie.size()/tam)-1; curva++) {
			curr++;
			/* Primer vertice */
			v = superficie[curr+tam] - superficie[curr];
			q = superficie[curr+1] - superficie[curr];
			normal = v.normal(q);
			v = superficie[curr-tam] - superficie[curr];
			normales.push_back(normal.normalizar());

			/* Vertices intermedios */
			for (curr += 1; curr < ((curva+1)*tam)-1; curr++ ) {
				v = superficie[curr-1] - superficie[curr]; //arriba
				q = superficie[curr+tam] - superficie[curr];//izq
				normal = v.normal(q);
				v = superficie[curr+1] - superficie[curr];//abajo
				normal += q.normal(v);
				q = superficie[curr-tam] - superficie[curr];//der
				normal += v.normal(q);
				v = superficie[curr-1] - superficie[curr]; //arriba
				normal += q.normal(v);
				normales.push_back(normal.normalizar());
			}
			/* ultimo vertice */
			v = superficie[curr-1] - superficie[curr];
			q = superficie[curr-tam] - superficie[curr];
			normal = q.normal(v);
			q = superficie[curr+tam] - superficie[curr];
			normal += v.normal(q);
			normales.push_back(normal.normalizar());
		}
	}

	/******************** ultima curva ***********************/
	if (superficie.size()/tam >1) {
		curr++;
		/* Primer vertice */
		v = superficie[curr-tam] - superficie[curr];
		q = superficie[curr+1] - superficie[curr];
		normal = q.normal(v);
		normales.push_back(normal.normalizar());

		/* Vertices intermedios */

		for (curr = superficie.size()-tam+1; curr < superficie.size()-1; curr++) {
			v = superficie[curr-1] - superficie[curr];
			q = superficie[curr-tam] - superficie[curr];
			normal = q.normal(v);
			v = superficie[curr+1] - superficie[curr];
			normal += v.normal(q);
			normales.push_back(normal.normalizar());
		}

		/* ultimo vertice */
		v = superficie[curr-1] - superficie[curr];
		q = superficie[curr-tam] - superficie[curr];
		normales.push_back(q.normal(v));
	}

	if (cerrada) {
		for (unsigned int i=0; i<tam; i++){
			v = (normales[i]+normales[normales.size()-tam+i]).normalizar();
			normales[i] = v;
			normales[normales.size()-tam+i] = v;
		}
	}

}

void Superficie::setTextura() {//TODO
}

void Superficie::init() {
	
	setIndices();
	setNormales();
	//setTextura();	
	
}



