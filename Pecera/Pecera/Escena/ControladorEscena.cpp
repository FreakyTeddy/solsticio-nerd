#include "ControladorEscena.h"

#include <GL/glut.h>
#include <stdlib.h>

bool ControladorEscena::animando = ANIMACION_INICIAL;
ControladorEscena* ControladorEscena::instancia = 0;

ControladorEscena::ControladorEscena():objetos(*(ContenedorObjetos::getInstancia())){

	//inicializo la escena
	render_mode = RM_INICIAL;
	ver_tray = VER_TRAYECTORIAS;
	instancia = this;

	//inicializo la luz de la escena

	glEnable(GL_LIGHTING);

	glEnable(GL_FOG);
	{
	   GLfloat fogColor[4] = {0, 0.05, 0.10, 1.0};

	   glFogi (GL_FOG_MODE, GL_EXP2);
	   glFogfv (GL_FOG_COLOR, fogColor);
	   glFogf (GL_FOG_DENSITY, 0.01);
	   glHint (GL_FOG_HINT, GL_DONT_CARE);
	   glFogf (GL_FOG_START, 20.0);
	   glFogf (GL_FOG_END, 50.0);
	}

/*	BURBUJAS

	//radio = (float)((rand()%19)+1)/20.0;
	size_t ubicacion = objetos.getTrayectoriaBurbujas()->cantPosiciones() / CANT_BURBUJAS;
	for (size_t i=0; i<CANT_BURBUJAS; i++) {
		burbujas[i] = new ObjetoViajero(BURBUJA, objetos.getTrayectoriaBurbujas(),1,1,1);
		for (size_t j=0; j<(i*ubicacion); j++) { //las desplazo
			burbujas[i]->viajar();
		}
	}
*/

	if (animando)
		ControladorEscena::animar(0);
}

ControladorEscena::~ControladorEscena() {

/* BURBUJAS
	for (int i=0; i<CANT_BURBUJAS; i++) {
			delete burbujas[i];
	}
*/
	delete ContenedorObjetos::getInstancia();
	delete ContenedorTexturas::getInstancia();
}

void ControladorEscena::generarEscena() {

/* FLORERO Y ALGAS
*/
	glPushMatrix();
		glRotatef(180,0,0,1);
		glTranslatef(5,4,0);
		objetos.dibujarObjeto(FLORERO, render_mode);
		glTranslatef(1.5,0,1.7);
		objetos.getAnimacion(ALGA1)->dibujar(render_mode);
		objetos.getAnimacion(ALGA2)->dibujar(render_mode);
	glPopMatrix();

/*	BURBUJAS
		Vertice t;
		for (int i=0; i<CANT_BURBUJAS; i++) {
			glPushMatrix();
				glEnable(GL_RESCALE_NORMAL);
				t= burbujas[i]->getPos();
				glTranslatef(t.x,t.y,t.z);
				t= burbujas[i]->deformacion;
				glScalef(t.x,t.y,t.z);
				objetos.dibujarObjeto(BURBUJA, render_mode);
				glDisable(GL_RESCALE_NORMAL);
			glPopMatrix();
		}
		if (ver_tray)
			objetos.getTrayectoriaBurbujas()->dibujarTrayecto();

*/



	/* CARDUMEN DORI */
//	objetos.dibujarCardumen(objetos.getCardumen(0), render_mode);
//	if (ver_tray)
//		objetos.getCardumen(0)->recorrido->dibujarTrayecto();


	objetos.dibujarEscenario(render_mode);
	terreno.dibujar(render_mode);

	/* KOI */
	glTranslated(0,0,10);
	objetos.dibujarPez(PEZ2,render_mode,1);

}

void ControladorEscena::animar(int n=0){
	//animar todos los objetos

//	//animo las superficies

//	//muevo los cardumenes
	instancia->objetos.animarPeces();
//	instancia->objetos.getCardumen(0)->viajar();
	instancia->objetos.getAnimacion(ALGA1)->animar();
	instancia->objetos.getAnimacion(ALGA2)->animar();
	instancia->objetos.getAnimacion(BIGOTE)->animar();

/* BURBUJAS
	for (int i=0; i<CANT_BURBUJAS; i++) {
		instancia->burbujas[i]->viajar();
	}
*/
	//redibujo la escena
	glutPostRedisplay();

	//continuo con la animacion
	if (animando && (n >= 0))
		glutTimerFunc(50,animar,++n);
}

void ControladorEscena::nextRenderMode() {
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

void ControladorEscena::nextAnimationMode() {
	animando = !animando;
	if (animando){
		ControladorEscena::animar();
	}
}

void ControladorEscena::nextTrackDisplayMode(){
	ver_tray = !ver_tray;
}
