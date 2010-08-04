#include "Burbuja.h"
#include <cstdlib>
#include <iostream>

Burbuja::Burbuja() {
	// TODO

	radio = (float)((rand()%19)+1)/20.0; //ver el tamaño que corresponda :)
}

Burbuja::~Burbuja() {
	// TODO Auto-generated destructor stub
}

void Burbuja::dibujar() {
//TODO

	glEnable(GL_BLEND);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE);	//transparencia
	    glutSolidSphere (radio, 20, 16);
	glDisable(GL_BLEND);
}
