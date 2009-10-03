#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "Linea/linea.h"
#include "Vertice.h"
#include <list>

class Poligono {
private:
	bool relleno; //indica si el poligono es relleno o solo contorno
	bool esDDA;
	std::list<Vertice> vertices; //vertices del poligono TODO ver si sirve esta implementacion :P

public:

	/* poligono por defecto sin relleno y linea DDA*/
	Poligono();

	Poligono(bool relleno);

	virtual ~Poligono();

	/* indica si el poligono es relleno */
	void setRelleno(bool relleno);

	/* indica que el contorno es linea DDA */
	void setDDA();

	/* indica que el contorno es linea Bresenham */
	void setBresenham();

	void dibujar();

	void agregarVertice(int x, int y);
};

#endif /* POLIGONO_H_ */
