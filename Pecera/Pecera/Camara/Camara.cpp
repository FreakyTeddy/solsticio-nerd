#include "Camara.h"



Camara::Camara() {
	reset();
}

Camara::~Camara() {}


void Camara::lookAt() {
	glLoadIdentity();
	gluLookAt (eye[0]/zoom, eye[1]/zoom, eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
}

void Camara::trasladar(float x, float y, float z) {
	eye[0]+=x; eye[1]+=y; eye[2]+=z;
//	at[0]+=x; at[1]+=y; at[2]+=z;
}

void Camara::zoom_in(float p) {
	zoom += p;
	if (zoom <= 0 ) {
		zoom -=p;
	}
}

void Camara::reset() {
	eye[0]=0.0; eye[1]=20.0; eye[2]=5.0;	//camara
	at[0]=0.0; at[1]=0.0; at[2]=5.0;	//centro
	up[0]=0.0; up[1]=0.0; up[2]=1.0;	//vector normal
	tras[0]=0; tras[1]=0; tras[2]=0; //traslacion de la camara

	rotate_cam_x = 0;
	rotate_cam_y = 0;
	zoom = 1;
}

