#ifndef BURBUJA_H_
#define BURBUJA_H_
#include <GL/glut.h>
#include <stdlib.h>
#include "../Primitivas/Curva/Curva.h"
	static const GLfloat mat_specular[] = { 0 ,0.05, 1.0 ,0.40 };//material de la burbuja
	static const GLfloat mat_shininess[] = { 70.0 };
	static Curva curva;
/*
 * Burbuja que sale de los peces?? :P
 */

class Burbuja {

private:

	float radio; //radio de la burbuja
	std::list<Vertice> trayectoria;

	/* tiene una curva que describe el movimiento */

public:
	Burbuja(float x, float y, float z);
	~Burbuja();

	void dibujar();

	Vertice* getPos(); //devuelve la posicion actual, null si ya termino su trayectoria

	void animar();
};

#endif /* BURBUJA_H_ */
