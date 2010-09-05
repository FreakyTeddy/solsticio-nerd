#ifndef SUPERFICIEREVOLUCION_H_
#define SUPERFICIEREVOLUCION_H_

#include "Superficie.h"

class SuperficieRevolucion: public Superficie {

private:
	unsigned int pasos;

	void rotar(float &p1, float &p2, float angulo);
	void rotar(float &p1, float &p2, float seno, float coseno);

public:

	/* Recibe la forma de la curva, el angulo a rotar
	 * y el eje de rotacion dado por los vertices eje1 y eje2 */
	SuperficieRevolucion(std::vector<Vertice> &forma, float angulo,Vertice eje1, Vertice eje2);
	~SuperficieRevolucion();
};

#endif /* SUPERFICIEREVOLUCION_H_ */
