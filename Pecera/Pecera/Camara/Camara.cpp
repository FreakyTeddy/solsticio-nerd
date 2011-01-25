#include "Camara.h"
#include <math.h>

Camara::Camara() {
	reset();
}

Camara::~Camara() {}


void Camara::lookAt() {
	glLoadIdentity();
	gluLookAt (eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);
}

void Camara::reset() {
	eye.set(2,15,3.0);	//camara
	at.set(0.0,0,5.0);	//centro
	up.set(0.0,0.0,1.0);	//vector normal

	zoom = 1;
}

void Camara::zoom_in(float p) {
	if (zoom > p ) {
		eye.x /= zoom;
		eye.y /= zoom;
	}//chekear dentro de escena
}

void Camara::trasladar_f(float cant) {
	Vertice temp = (at-eye).normalizar()*cant;
	eye +=temp;
	at +=temp;
	if (fueraDeEscena(eye)) {
		eye -=temp;
		at -=temp;
	}
}

void Camara::trasladar_s(float cant) {
	Vertice temp = (eye-at).prodVectorial(up).normalizar()*cant;
	eye +=temp;
	at +=temp;
	if (fueraDeEscena(eye)) {
		eye -=temp;
		at -=temp;
	}
}

void Camara::trasladar_u(float cant) {
	//no me convence
	eye += (up*cant);
	at += (up*cant);
}


void Camara::rotar_h(float cant) {
	Vertice fin = eye + up;
	at.rotar(eye,fin,cant);
}

void Camara::rotar_v(float cant) {
//	Vertice t = (eye-at).prodVectorial(up);
//	at.rotar(eye,t+eye,cant);  ->> deberia ser asi! no se por que falla
}

bool Camara::fueraDeEscena(Vertice &t) {
	return ((t.x<X_INF) || (t.x>X_SUP) || (t.y<Y_INF) || (t.y>Y_SUP) || (t.z<Z_INF) || (t.z>Z_SUP));
}

bool Camara::anguloValido(Vertice at) {
	return true;
}

