#ifndef BURBUJA_H_
#define BURBUJA_H_
#include <GL/glut.h>
#include <stdlib.h>
#include "../Primitivas/Curva/Curva.h"
	static const GLfloat mat_specular[] = { 0 ,0.05, 1.0 ,0.40 };//material de la burbuja
	static const GLfloat mat_shininess[] = { 70.0 };
/*
 * Burbuja que sale de los peces
 */

class Burbuja {

private:


	float radio;
	/* tiene una curva que describe el movimiento */

public:
	Burbuja();
	~Burbuja();

	void dibujar();
};

#endif /* BURBUJA_H_ */
