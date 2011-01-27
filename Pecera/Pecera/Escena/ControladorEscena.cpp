#include "ControladorEscena.h"

#include <GL/glut.h>
#include <stdlib.h>

bool ControladorEscena::animando = ANIMACION_INICIAL;
ControladorEscena* ControladorEscena::instancia = 0;

ControladorEscena::ControladorEscena():objetos(*(ContenedorObjetos::getInstancia())){

	render_mode = RM_INICIAL;
	ver_tray = VER_TRAYECTORIAS;
	instancia = this;
	crearCardumen();

	if (animando)
		ControladorEscena::animar(0);
}

ControladorEscena::~ControladorEscena() {

	delete cardumen1;

	ContenedorTexturas::getInstancia()->vaciarContenedor();
}

void ControladorEscena::generarEscena() {

	glPushMatrix();

		glRotatef(180,0,0,1);
		objetos.dibujarObjeto(ALGA1, render_mode);
		objetos.dibujarObjeto(ALGA2, render_mode);

//		glTranslatef(5,4,0);
//		objetos.dibujarObjeto(FLORERO, render_mode);
//		objetos.dibujarObjeto(ROCA1,render_mode);

		//test
		dibujarCardumen(cardumen1);

	glPopMatrix();
	objetos.dibujarEscenario(render_mode);

}

void ControladorEscena::animar(int n=0){
	//animar todos los objetos
	std::cout<<"animando: "<<n<<std::endl;

	instancia->cardumen1->recorrido->sgtePosicion();
	glutPostRedisplay();

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

void ControladorEscena::dibujarCardumen(Cardumen* car) {
	glPushMatrix();

		float escala;
		Vertice pos = car->recorrido->getPosicion();

		glTranslatef(pos.x, pos.y, pos.z);	//ubico al cardumen en su trayectoria

		//TODO!!! tendrian que rotar para mirar siempre hacia adelante!

		glEnable(GL_RESCALE_NORMAL);	//habilito el reescalado de normales

		for (uint i=0; i < car->cantidad; i++){

			glPushMatrix();
				pos = car->ubicacion[i];
				escala = car->volumen[i];
				glTranslatef(pos.x, pos.y, pos.z);	//ubico al objeto en su posicion dentro del cardumen
				glScalef(escala,escala,escala);		//reesccalo el objeto
				objetos.dibujarObjeto(car->IDobjeto, render_mode);
			glPopMatrix();
		}

		glDisable(GL_RESCALE_NORMAL);

	glPopMatrix();
}


void ControladorEscena::crearCardumen(){

	//puntos control trayecto
	std::vector<Vertice> control;
	Vertice t;
	control.push_back(t);
	control.push_back(t);
	control.push_back(t);
	t.set(10,2,0);
	control.push_back(t);
	t.set(5,-2,4);
	control.push_back(t);
	t.set(-2,-12,6);
	control.push_back(t);
	t.set(0,0,0);
	control.push_back(t);
	control.push_back(t);
	control.push_back(t);


	cardumen1 = new Cardumen(FLORERO,1,control,true,5,false);

}






