#include "ControladorEscena.h"

#include <GL/glut.h>
#include <stdlib.h>

ControladorEscena::ControladorEscena() {
	render_mode = GL_TEXTURE;

}

ControladorEscena::~ControladorEscena() {
	// TODO Auto-generated destructor stub
}

void ControladorEscena::generarEscena() {

	glPushMatrix();
		glTranslatef(-5,-4,0);
		objetos.dibujarObjeto(FLORERO, render_mode);
	glPopMatrix();
		objetos.dibujarObjeto(ALGA1, render_mode);
		objetos.dibujarObjeto(ALGA2, render_mode);

}

void ControladorEscena::nextMode() {
	if (render_mode == GL_FILL) {
		render_mode = GL_TEXTURE;
	}else if (render_mode == GL_TEXTURE) {
		render_mode = GL_LINE;
	}else if (render_mode == GL_LINE) {
		render_mode = GL_FILL;
	}
}

unsigned int ControladorEscena::getRenderMode() {
	return render_mode;
}


