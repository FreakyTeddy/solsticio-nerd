#ifndef BOTON_H_
#define BOTON_H_

#include "Numero.h"
#include "Poligono.h"

class Boton {

private:
	bool apretado;
	bool esDDA;
	Numero *numero;
	Poligono centro;
	Poligono sombra[4];

	void cargarVertices();


public:
	Boton();
	~Boton();

	void apretar();
	void soltar();

	/* dibuja el boton con su numero */
	/* se debe setear el numero antes de dibujar */
	void dibujar();

	/* Numero del boton */
	void setNumero(Numero *num);

	/* indica si dibujar el numero con DDA o Bresenham */
	void esDDA(bool dda);
};

#endif /* BOTON_H_ */
