#include "ControladorEscena.h"

#include <GL/glut.h>
#include <stdlib.h>

ControladorEscena::ControladorEscena() {
	render_mode = RM_INICIAL;

}

ControladorEscena::~ControladorEscena() {
	ContenedorTexturas::getInstancia()->vaciarContenedor();
}

void ControladorEscena::generarEscena() {
	cam.lookAt();

	glPushMatrix();

		glRotatef(180,0,0,1);
		objetos.dibujarObjeto(ALGA1, render_mode);
		objetos.dibujarObjeto(ALGA2, render_mode);

		glTranslatef(5,4,0);
		objetos.dibujarObjeto(FLORERO, render_mode);
//		objetos.dibujarObjeto(ROCA1,render_mode);
	glPopMatrix();
	objetos.dibujarEscenario(render_mode);

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

Camara* ControladorEscena::getCamara() {
	return &cam;
}
