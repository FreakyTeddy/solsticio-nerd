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

	//consigo los objetos animados
//	cardumen1 = objetos.getCardumen(0);
//	alga1 = new ObjetoAnimado(objetos.getAnimacion(0),false);
//	alga2 = new ObjetoAnimado(objetos.getAnimacion(0),false);//TODO
//	alga2->frame +=5;//WHAT!!!

	for (int i=0; i<10; i++) {
		burbujas[i] = new ObjetoViajero(BURBUJA, objetos.getTrayectoriaBurbujas(),1,1,1);
		for (int j=0; j<i+5; j++) { //las desplazo
			burbujas[i]->viajar();
		}
	}

	if (animando)
		ControladorEscena::animar(0);
}

ControladorEscena::~ControladorEscena() {

//	delete alga1;
//	delete alga2;
	for (int i=0; i<10; i++) {
			delete burbujas[i];
	}
	delete ContenedorObjetos::getInstancia();
	delete ContenedorTexturas::getInstancia();
}

void ControladorEscena::generarEscena() {

	glPushMatrix();

	glPushMatrix();
		glRotatef(180,0,0,1);
		glTranslatef(5,4,0);
		objetos.dibujarObjeto(FLORERO, render_mode);
		glTranslatef(0.1,0,1.6);
		objetos.dibujarObjeto(ALGA1, render_mode);
		objetos.dibujarObjeto(ALGA2, render_mode);
		glPushMatrix();
		Vertice t;
			for (int i=0; i<10; i++) {
				t= burbujas[i]->getPos();
				glTranslatef(t.x,t.y,t.z);
				t= burbujas[i]->deformacion;
				glScalef(t.x,t.y,t.z);
				objetos.dibujarObjeto(BURBUJA, render_mode);
			}
		glPopMatrix();
	glPopMatrix();

	objetos.getTrayectoriaBurbujas()->dibujarTrayecto();
//		objetos.dibujarCardumen(cardumen1, render_mode);
//		if(ver_tray){
//			glColor3f(1,1,0);
//			cardumen1->recorrido->dibujarTrayecto();
//		}
//		alga1->dibujar(render_mode);
//		glTranslatef(5,4,0);
//		alga2->dibujar(render_mode);

	glPopMatrix();
	objetos.dibujarEscenario(render_mode);
	terreno.dibujar(render_mode);

}

void ControladorEscena::animar(int n=0){
	//animar todos los objetos
	std::cout<<"animando: "<<n<<std::endl;

//	//animo las superficies
//	instancia->alga1->animar();
//	instancia->alga2->animar();
//
//
//	//muevo los cardumenes
//	instancia->cardumen1->viajar();
	for (int i=0; i<10; i++) {
		instancia->burbujas[i]->viajar();
	}
	//redibujo la escena
	glutPostRedisplay();

	//continuo con la animacion
	if (animando)
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
