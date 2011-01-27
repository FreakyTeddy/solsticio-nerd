#include "Camara.h"
#include <math.h>

Camara::Camara() {
	reset();
}

Camara::~Camara() {}


void Camara::lookAt() {
	glLoadIdentity();
	gluLookAt (eye.x/zoom, eye.y/zoom, eye.z, (eye.x+ at.x)/zoom, (eye.y + at.y)/zoom, eye.z + at.z, up.x, up.y, up.z);
}

void Camara::reset() {
	eye.set(2,15,10.0);	//posicion camara
	at.set(0,-1.0,0);	//direccion mira
	up.set(0.0,0.0,1.0);//vector normal

	zoom = 1;
}

void Camara::zoom_in(float p) {
	if (zoom > p ) {
		zoom -=p;
		Vertice temp(eye.x/zoom,eye.y/zoom,eye.z);
		if (!fueraDeEscena(temp))
			eye = temp;
	}//chekear dentro de escena
}

void Camara::trasladar_f(float cant) {
	Vertice temp = at*cant;
	eye +=temp;
	if (fueraDeEscena(eye)) {
		eye -=temp;
	}
}

void Camara::trasladar_s(float cant) {
	Vertice temp = at.prodVectorial(up).normalizar()*cant;
	eye +=temp;

	if (fueraDeEscena(eye))
		eye -=temp;
}

void Camara::trasladar_u(float cant) {
	eye += (up*cant);
	if (fueraDeEscena(eye))
		eye -=(up*cant);
}


void Camara::rotar_h(float cant) {
	Vertice origen;
	at.rotar(origen,up,cant).normalizar();
}

void Camara::rotar_v(float cant) {
	Vertice t = at.prodVectorial(up);
	Vertice origen;
	at.rotar(origen,t,cant).normalizar();
	//at.print();//creo que el problema es, que al rotar, el mismo prodvect da ejes opuestos
	//VER! bajo que condicion hay que calcular el opuesto

}

bool Camara::fueraDeEscena(Vertice &t) {
	return ((t.x<X_INF) || (t.x>X_SUP) || (t.y<Y_INF) || (t.y>Y_SUP) || (t.z<Z_INF) || (t.z>Z_SUP));
}

bool Camara::anguloValido(Vertice at) {
	return true;
}

