#ifndef SUPERFICIEBARRIDO_H_
#define SUPERFICIEBARRIDO_H_

#include <GL/glut.h>
#include <vector>
#include "../Vertice.h"


class SuperficieBarrido {

private:
	std::vector<Vertice> superficie;//malla de vertices de la superficie
	std::vector<Vertice> normales;
	unsigned int tam; //tamanio de la curva "forma"
	//TODO faltaria malla de color/textura


public:

	/* Crea una superficie de barrido en base a una curva, aplicando la traslacion
	 * y deformacion correspondiente a cada paso */
	SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl);

	~SuperficieBarrido();

	void dibujar();
};

#endif /* SUPERFICIEBARRIDO_H_ */
