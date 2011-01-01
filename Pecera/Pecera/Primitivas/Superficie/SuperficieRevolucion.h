#ifndef SUPERFICIEREVOLUCION_H_
#define SUPERFICIEREVOLUCION_H_

#include "Superficie.h"

class SuperficieRevolucion: public Superficie {

private:

	void rotar(float &p1, float &p2, float angulo);
	void rotar(float &p1, float &p2, float seno, float coseno);

public:

	/* Recibe la forma de la curva, el angulo a rotar
	 * y el eje de rotacion dado por la recta que une los vertices eje1 y eje2
	 * pasos indica el paso de discretizacion (20 por defecto) */
	SuperficieRevolucion(std::vector<Vertice> &forma, float angulo,Vertice eje1, Vertice eje2, int pasos = 20);

	~SuperficieRevolucion();

};

#endif /* SUPERFICIEREVOLUCION_H_ */
