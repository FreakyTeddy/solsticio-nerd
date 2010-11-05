#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

#include "../Vertice.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class Superficie {

private:
	static unsigned int render_mode;
	/* material de la superficie */
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_shininess[1];

protected:
	std::vector<Vertice> superficie; //malla de vertices de la superficie
	std::vector<Vertice> normales;
	std::vector<GLuint> indices;
	unsigned int tam; 		 //tamanio de la curva "forma"
	bool cerrada;
	//TODO faltaria malla de color/textura



	/* setea los indices para dibujado con draw elements */
	void setIndices();

	/* generar las normales de iluminacion */
	void setNormales();
	
	void setTextura();

	/* inicializa la superficie creando normales, indices y texturas */
	void init();

public:

	Superficie();
	virtual ~Superficie();

	/* cambia al siguiente modo de renderizado TRIANG -> QUAD -> LINE */
	static void nextMode();

	void dibujar();

	/* cambian el material de la superficie.. los valores son entre 0 y 1
	 * alpha = 1 -> no hay transparencia	 */
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
	void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
	void setShininess(GLfloat shine);

};

#endif /* SUPERFICIE_H_ */
