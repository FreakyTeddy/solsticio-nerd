#include "Camara.h"
#include <math.h>
#include "../Primitivas/rotacion_3d.h"

Camara::Camara() {
	reset();
}

Camara::~Camara() {}


void Camara::lookAt() {
	glLoadIdentity();
	gluLookAt (eye.x, eye.y, eye.z, eye.x+ at.x, eye.y + at.y, eye.z + at.z, up.x, up.y, up.z);
}

void Camara::reset() {
	eye.set(2,15,10.0);	//posicion camara
	at.set(0,-1.0,0);	//direccion mira
	up.set(0.0,0.0,1.0);//vector normal
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
	Rotacion3d rot(origen, up, cant);
	rot.rotar(at);
}

void Camara::rotar_v(float cant) {
	if ( anguloValido(cant)) {
		Vertice t = at.prodVectorial(up);
		Vertice origen;
		Rotacion3d rot(origen, t, cant);
		rot.rotar(at);
	}
}

bool Camara::fueraDeEscena(Vertice &t) {
	return ((t.x<X_INF) || (t.x>X_SUP) || (t.y<Y_INF) || (t.y>Y_SUP) || (t.z<Z_INF) || (t.z>Z_SUP));
}

bool Camara::anguloValido(float angulo) {
	//calcular el angulo entre up y at, ver que este entre 0 y 180
	return true;
}

