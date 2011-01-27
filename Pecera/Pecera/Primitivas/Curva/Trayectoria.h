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


public:


	/* recibe los puntos de control, la cantidad de pasos intermedios y si la curva es bezier o bspline */
	Trayectoria(std::vector<Vertice> &puntosControl,bool cerrada,uint intervalo, bool bezier);

	~Trayectoria();

	Vertice getPosicion();

	/* dibuja la trayectoria */
	void dibujarTrayecto();

	void sgtePosicion();

};

#endif /* TRAYECTORIA_H_ */
