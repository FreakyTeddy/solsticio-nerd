#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

#include "../Vertice.h"
#include "../Texturas/Textura.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class Superficie {

private:

	/* material de la superficie */
	GLfloat mat_diffuse[4];
	GLfloat mat_ambient[4];
	GLfloat mat_specular[4];
	GLfloat mat_shininess[1];

protected:
	std::vector<Vertice> superficie;	// malla de vertices 3D de la superficie
	std::vector<Vertice> normales;		// normales de iluminacion en cada vertice 3D
	std::vector<Vertice2D> texCoord;	// coordenadas de textura de cada vertice 3D
	std::vector<GLuint> indices;		// recorrido de la malla

	Textura	tex;		// contiene la textura de la superficie

	unsigned int tam;	// cantidad de vertices de la curva "forma"
	bool cerrada;		//indica si la curva es cerrada

	/* setea los indices para dibujado con draw elements */
	void setIndices();

	/* generar las normales de iluminacion */
	void setNormales();

	/* inicializa la superficie creando normales, indices y texturas */
	void init();

private:

	void dibujarTrianStrip(unsigned int render_mode);
	void dibujarMalla();
	void dibujarTextura();
	void dibujarNormales();


public:

	Superficie();
	virtual ~Superficie();

	/* dibuja la superficie segun el modo de renderizado */
	void dibujar(unsigned int render_mode);

	/* aplica la textura especificada a la superficie */
	void aplicarTextura (std::string ruta);

	/* cambian el material de la superficie.. los valores son entre 0 y 1
	 * alpha = 1 -> no hay transparencia	 */
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
	void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
	void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);

	/* menor shine hace el brillo mas "grande" */
	void setShininess(GLfloat shine);

};

#endif /* SUPERFICIE_H_ */
