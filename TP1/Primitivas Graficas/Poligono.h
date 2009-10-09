#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "Linea/linea.h"
#include "Vertice.h"
#include "Transformacion2D/transformacion2D.h"
#include <list>

class Poligono {
private:
	std::list<Vertice> vertices; //vertices del poligono
	//dimensiones
	int ancho;
	int alto;

public:

	/* poligono por defecto sin relleno, con contorno y linea DDA de 100x100*/
	Poligono();

	Poligono(const Poligono &p);

	virtual ~Poligono();

	/* dibuja el poligono relleno */
	void dibujarConRelleno(MatrizTrans2D &matTrans);

	/* dibuja el contorno del poligono con linea DDA o Bresenham */
	void dibujarContorno(bool esDDA, MatrizTrans2D &matTrans);

	void agregarVertice(float x, float y);
	
	std::list<Vertice>& obtenerVertices();
	
	/* especificar las dimensiones del poligono */
	void setDimensiones(int ancho, int alto);
	
};

#endif /* POLIGONO_H_ */
