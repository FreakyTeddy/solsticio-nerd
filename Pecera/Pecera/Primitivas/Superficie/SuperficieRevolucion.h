#ifndef SUPERFICIEREVOLUCION_H_
#define SUPERFICIEREVOLUCION_H_

#include "Superficie.h"

class SuperficieRevolucion: public Superficie {

private:
	unsigned int pasos;

public:

	/* Recibe la forma de la curva, el angulo a rotar */
	SuperficieRevolucion(std::vector<Vertice> &forma, float angulo);
	~SuperficieRevolucion();
};

#endif /* SUPERFICIEREVOLUCION_H_ */
