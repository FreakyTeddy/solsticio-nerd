#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

#include "../Vertice.h"
#include <GL/glut.h>
#include <vector>

class Superficie {

protected:
	std::vector<Vertice> superficie; //malla de vertices de la superficie
	std::vector<Vertice> normales;
	unsigned int tam; //tamanio de la curva "forma"
	//TODO faltaria malla de color/textura

public:

	Superficie();
	virtual ~Superficie();

	void dibujar();
};

#endif /* SUPERFICIE_H_ */
