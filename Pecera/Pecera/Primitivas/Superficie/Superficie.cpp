#include "Superficie.h"

Superficie::Superficie() {
	material.setDiffuse(0.85,0.85, 0.85, 1);
	material.setSpecular(1, 1, 1, 1);
	material.setAmbient(0.0, 0.05, 0.1, 1);
	material.setShininess(70.0);
}

Superficie::~Superficie() {
	normales.clear();
	superficie.clear();
	glDeleteLists(dl_handle, 2);
}

void Superficie::dibujar(unsigned int render_mode) {

	material.usarMaterial();

	if ((render_mode != GL_TEXTURE) || (render_mode == GL_TEXTURE && !tex.tieneTextura())) {
		glPolygonMode( GL_FRONT_AND_BACK, render_mode);
		glFrontFace( GL_CCW );
		glCullFace(cull);
		//llamo a la display list
		 glCallList(dl_handle);
	}

	if (render_mode == GL_TEXTURE && tex.tieneTextura()) {
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
		glBindTexture(GL_TEXTURE_2D,tex.getID());
		glEnable(GL_TEXTURE_2D);
		glFrontFace( GL_CCW );
		glCullFace(cull);
		//llamo a la display list
		 glCallList(dl_handle+1);
		glDisable(GL_TEXTURE_2D);
	}


	//dibujo las normales
//	dibujarNormales();

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

void Superficie::aplicarTextura(std::string ruta) {
	tex.cargarImagen(ruta);
}

void Superficie::generarDisplayList() {
	dl_handle = glGenLists(2);
	glNewList(dl_handle, GL_COMPILE);

		std::vector<Vertice>::iterator it0, it1;

		it0 = superficie.begin();
		it1 = superficie.begin();
		it1 += tam;

		//activar estado
		glEnableClientState (GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glNormalPointer(GL_FLOAT,0, &(normales[0]));
		glVertexPointer(3, GL_FLOAT, 0, &(superficie[0]));

		//dibujar
		unsigned int cols = (superficie.size()/tam) -1;
		for(unsigned int i=0 ; i <  cols ; i++)
			glDrawElements(GL_TRIANGLE_STRIP, tam*2, GL_UNSIGNED_INT, &(indices[i*tam*2]));

		//desactivar estados
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState (GL_VERTEX_ARRAY);

	glEndList();
}

void Superficie::generarDisplayListTextura() {
	glNewList(dl_handle+1, GL_COMPILE);

		GLuint it0=0, it1=0;
		GLuint longitud = superficie.size();

		for (it1 = tam; it1 < longitud; it0++, it1++) {

			glBegin(GL_TRIANGLE_STRIP);

			glTexCoord2f(texCoord[it0].x,texCoord[it0].y);
			glNormal3d(normales[it0].x, normales[it0].y, normales[it0].z);
			glVertex3d(superficie[it0].x, superficie[it0].y, superficie[it0].z);

			glTexCoord2f(texCoord[it1].x,texCoord[it1].y);
			glNormal3d(normales[it1].x, normales[it1].y, normales[it1].z);
			glVertex3d(superficie[it1].x, superficie[it1].y, superficie[it1].z);

			for(unsigned int pos=0 ; pos <  tam-1 ; pos++) {
				it0++;
				glTexCoord2f(texCoord[it0].x,texCoord[it0].y);
				glNormal3d(normales[it0].x, normales[it0].y, normales[it0].z);
				glVertex3d(superficie[it0].x, superficie[it0].y, superficie[it0].z);

				it1++;
				glTexCoord2f(texCoord[it1].x,texCoord[it1].y);
				glNormal3d(normales[it1].x, normales[it1].y, normales[it1].z);
				glVertex3d(superficie[it1].x, superficie[it1].y, superficie[it1].z);
			}
			glEnd();
		}

	glEndList();
}

void Superficie::init() {
	
	cull = GL_FRONT;

	setIndices();
	setNormales();
	tex.generarCoordenadas(superficie, texCoord, tam);

	generarDisplayList();
	generarDisplayListTextura();

	indices.clear();
	texCoord.clear();
	if(!keep)
		superficie.clear();
}

Material* Superficie::getMaterial() {
	return &material;
}

void Superficie::setMaterial(Material &m) {
	material = m;
}

