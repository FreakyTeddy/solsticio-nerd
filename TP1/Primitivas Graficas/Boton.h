#ifndef BOTON_H_
#define BOTON_H_

#include "Numero.h"
#include "Poligono.h"

class Boton {

private:
	bool apretado;
	bool esDDA;
	Poligono centro;
	Poligono sombra[4];

	void cargarVertices();


public:
	Boton();
	~Boton();

	void apretar();
	void soltar();

	/* dibuja el boton con su numero */
	void dibujar(Numero *numero);

	/* indica si dibujar el numero con DDA(true) o Bresenham(false) */
	void setDDA(bool dda);
};

#endif /* BOTON_H_ */
