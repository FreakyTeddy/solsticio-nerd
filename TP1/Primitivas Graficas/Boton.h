#ifndef BOTON_H_
#define BOTON_H_

#include "Numero.h"
#include "Poligono.h"

class Boton {

private:
	bool apretado;
	Numero *numero; //TODO no tengo mucha idea de como hacer esta parte XD
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
};

#endif /* BOTON_H_ */
