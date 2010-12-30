#include "Camara.h"
#include <math.h>

Camara::Camara() {
	reset();
}

Camara::~Camara() {}


void Camara::lookAt() {
	glLoadIdentity();
	gluLookAt (eye.x/zoom, eye.y/zoom, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);
}

void Camara::reset() {
	eye.set(5.0,15.0,4.0);	//camara
	at.set(0.0,0.0,5.0);	//centro
	up.set(0.0,0.0,1.0);	//vector normal

	zoom = 1;
}

void Camara::zoom_in(float p) {
	zoom += p;
	if (zoom <= 0 ) {
		zoom -=p;
	}
}

void Camara::trasladar_f(float cant) {
	Vertice temp = (at-eye).normalizar()*cant;
	eye +=temp;
	at +=temp;
}

void Camara::trasladar_s(float cant) {
	Vertice temp = (eye-at).prodVectorial(up).normalizar()*cant;
	eye +=temp;
	at +=temp;
}

void Camara::trasladar_u(float cant) {
	//no me convence
	eye += (up*cant);
	at += (up*cant);
}


void Camara::rotar_h(float cant) {
	//TODO! mucho error... se va la imagen :P
	Vertice temp = (eye-at).prodVectorial(up).normalizar()*cant;
	temp.z=0;
	eye +=temp;

}

void Camara::rotar_v(float cant) {
	//TODO! mucho error... se va la imagen :P
	Vertice temp = eye.prodVectorial(at).prodVectorial(eye).normalizar()*cant;
	eye += temp;
}
