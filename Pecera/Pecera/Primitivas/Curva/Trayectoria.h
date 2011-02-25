#ifndef TRAYECTORIA_H_
#define TRAYECTORIA_H_

#include "Curva.h"
#include <GL/gl.h>

/***
 * Describe una trayectoria
 *
 *
 */


class Trayectoria {

	std::vector<Vertice> trayecto;
	size_t actual;
	size_t tam;
	GLfloat color[3];
	bool closed;

public:


	/* recibe los puntos de control, la cantidad de pasos intermedios y si la curva es bezier o bspline */
	Trayectoria(std::vector<Vertice> &puntosControl,bool cerrada,uint intervalo, bool bezier);

	~Trayectoria();

	Vertice getPosicion();
	Vertice& getPosicion(size_t act);

	/* dibuja la trayectoria */
	void dibujarTrayecto();

	size_t cantPosiciones() {
		return trayecto.size();
	};

	/* devuelve un vertice NO normalizado en la direccion del movimiento */
	Vertice getDireccion();

	void sgtePosicion();
	size_t sgtePosicion(size_t act);

	void setColor(GLfloat r, GLfloat g, GLfloat b) {
		color[0]=r;color[1]=g;color[2]=b;
	}

};

#endif /* TRAYECTORIA_H_ */
