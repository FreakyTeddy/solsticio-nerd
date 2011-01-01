#include "Superficie.h"

#define TEXTURA 0

unsigned int Superficie::render_mode = GL_TRIANGLE_STRIP;

Superficie::Superficie() {
	mat_diffuse[0]=0.50; mat_diffuse[1]=0.10; mat_diffuse[2]=0.70; mat_diffuse[3]=0.70;
	mat_specular[0]=0.30; mat_specular[1]=0.0; mat_specular[2]=0.90; mat_specular[3]=0.7;
	mat_shininess[0]=50.0;

}

Superficie::~Superficie() {}

void Superficie::dibujar() {

	if (render_mode == GL_LINE_LOOP) {
		dibujarMalla();
	}
	if (render_mode == GL_TRIANGLE_STRIP)	{
		dibujarTrianStrip();
	}
	if (render_mode == TEXTURA && tex.tieneTextura()) {
		dibujarTextura();
	}

	//dibujo las normales
	//dibujarNormales();

}

void Superficie::dibujarMalla() {
	std::vector<Vertice>::iterator it0, it1;

	it0 = superficie.begin();
	it1 = superficie.begin();
	it1 += tam;

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
}

void Superficie::dibujarTrianStrip() {
	//dibuja usando triangle strip y Vertex y Normal Pointers
	std::vector<Vertice>::iterator it0, it1;

	it0 = superficie.begin();
	it1 = superficie.begin();
	it1 += tam;

	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &(superficie[0]));
	glNormalPointer(GL_FLOAT,0, &(normales[0]));

	unsigned int cols = (superficie.size()/tam) -1;

	for(unsigned int i=0 ; i <  cols ; i++)
		glDrawElements(GL_TRIANGLE_STRIP, tam*2, GL_UNSIGNED_INT, &(indices[i*tam*2]));

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState (GL_VERTEX_ARRAY);
}

void Superficie::dibujarNormales() {

	std::vector<Vertice>::iterator it0;
	std::vector<Vertice>::iterator it1 = normales.begin();
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	Vertice v;
	for(it0 =superficie.begin(); it0 != superficie.end() ; it0++, it1++) {
			v = (*it0) + (*it1);
			glVertex3f(it0->x,it0->y,it0->z);
			glVertex3f(v.x,v.y,v.z);
	}
	glEnd();
	glEnable(GL_LIGHTING);

}

void Superficie::dibujarTextura() {
	GLuint it0=0, it1=0;
	GLuint longitud = superficie.size();
	indices.clear();

	glBindTexture(GL_TEXTURE_2D,tex.getID());
	glEnable(GL_TEXTURE_2D);

	for (it1 = tam; it1 < longitud; it0++, it1++) {
		glBegin(GL_TRIANGLE_STRIP);


		glTexCoord2f(0,0);
		glNormal3d(normales[it0].x, normales[it0].y, normales[it0].z);
		glVertex3d(superficie[it0].x, superficie[it0].y, superficie[it0].z);

		glTexCoord2f(0,1);
		glNormal3d(normales[it1].x, normales[it1].y, normales[it1].z);
		glVertex3d(superficie[it1].x, superficie[it1].y, superficie[it1].z);

		bool coord = 1;

		for(unsigned int pos=0 ; pos <  tam-1 ; pos++, coord= !coord) {
			it0++;
			glTexCoord2f(coord,0);
			glNormal3d(normales[it0].x, normales[it0].y, normales[it0].z);
			glVertex3d(superficie[it0].x, superficie[it0].y, superficie[it0].z);
			it1++;
			glTexCoord2f(coord,1);
			glNormal3d(normales[it1].x, normales[it1].y, normales[it1].z);
			glVertex3d(superficie[it1].x, superficie[it1].y, superficie[it1].z);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


void Superficie::nextMode() {
	if (render_mode == GL_TRIANGLE_STRIP) {
		render_mode = TEXTURA;
	}else if (render_mode == TEXTURA) {
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

void Superficie::setTextura() {
	tex.cargarImagen("res/arena.bmp");
}

void Superficie::init() {
	
	setIndices();
	setNormales();
	setTextura();
	
}

void Superficie::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
	mat_diffuse[0]=r; mat_diffuse[1]=g; mat_diffuse[2]=b; mat_diffuse[3]=alpha;

}
void Superficie::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
	mat_specular[0]=r; mat_specular[1]=g; mat_specular[2]=b; mat_specular[3]=alpha;
}
void Superficie::setShininess(GLfloat shine) {
	mat_shininess[0] = shine;
}



