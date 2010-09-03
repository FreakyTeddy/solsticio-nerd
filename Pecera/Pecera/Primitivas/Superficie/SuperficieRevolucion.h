#ifndef SUPERFICIEREVOLUCION_H_
#define SUPERFICIEREVOLUCION_H_

#include "Superficie.h"

class SuperficieRevolucion: public Superficie {

private:
	unsigned int pasos;

	void rotar(float &p1, float &p2, float angulo);
	void rotar(float &p1, float &p2, float seno, float coseno);

public:

	/* Recibe la forma de la curva, el angulo a rotar */
	SuperficieRevolucion(std::vector<Vertice> &forma, float angulo);
	~SuperficieRevolucion();
};

#endif /* SUPERFICIEREVOLUCION_H_ */
