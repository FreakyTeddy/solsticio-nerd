#include "Trayectoria.h"

Trayectoria::Trayectoria(std::vector<Vertice> &puntosControl,bool cerrada=true, uint intervalo=4, bool bezier=false) {
	Curva curva;
	if (bezier){
		curva.setFactorBezier(intervalo);
		curva.BezierCubica(puntosControl,trayecto);
	}
	else {
		curva.setFactor(intervalo);
		curva.Bspline(puntosControl,trayecto);
	}

	closed = cerrada;
	actual = 0;
	tam = trayecto.size();
}

Trayectoria::~Trayectoria() {}

Vertice Trayectoria::getPosicion(){
	return trayecto[actual];
}

Vertice& Trayectoria::getPosicion(size_t act){
	return trayecto[act];
}

void Trayectoria::dibujarTrayecto(){
  glEnable(GL_COLOR_MATERIAL);
  glDisable(GL_LIGHTING);
  	glColor3fv(color);
	if (closed)
		glBegin(GL_LINE_LOOP);
	else
		glBegin(GL_LINE_STRIP);
	for (size_t pos=0 ; pos<tam ; pos++) {
		glVertex3f(trayecto[pos].x,trayecto[pos].y,trayecto[pos].z);
	}
	glEnd();
  glEnable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
}

void Trayectoria::sgtePosicion(){
	actual++;
	if (actual >= tam)
		actual = 0;
}

size_t Trayectoria::sgtePosicion(size_t act){
	act++;
	if (act >= tam)
		act = 0;
	return act;
}

Vertice Trayectoria::getDireccion() {
	return trayecto[sgtePosicion(actual)] - trayecto[actual];
}


