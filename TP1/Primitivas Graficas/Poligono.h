#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "Linea/linea.h"
#include "Vertice.h"
#include "Transformacion2D/transformacion2D.h"
#include <list>

class Poligono {
private:
	std::list<Vertice> vertices; //vertices del poligono TODO ver si sirve esta implementacion :P

public:

	/* poligono por defecto sin relleno, con contorno y linea DDA*/
	Poligono();

	virtual ~Poligono();

	/* dibuja el poligono relleno */
	void dibujarConRelleno();

	/* dibuja el contorno del poligono con linea DDA o Bresenham */
	void dibujarContorno(bool esDDA);

	void agregarVertice(int x, int y);
};

#endif /* POLIGONO_H_ */
