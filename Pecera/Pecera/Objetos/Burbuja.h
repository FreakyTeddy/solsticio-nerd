#ifndef BURBUJA_H_
#define BURBUJA_H_
#include <GL/glut.h>
#include <stdlib.h>
#include "../Primitivas/Curva/Curva.h"

/*
 * Burbuja que sale de los peces?? :P
 */

class Burbuja {

private:

	static const GLfloat mat_specular[];//material de la burbuja
	static const GLfloat mat_shininess[];
	static const GLfloat mat_diffuse[];
	static Curva curva;
	float radio; //radio de la burbuja
	unsigned int tramo;
	std::vector<Vertice> trayectoria;

	/* tiene una curva que describe el movimiento */

public:
	Burbuja(float x, float y, float z);
	~Burbuja();

	void dibujar();

	Vertice* getPos(); //devuelve la posicion actual, null si ya termino su trayectoria

	void animar();
};

#endif /* BURBUJA_H_ */
