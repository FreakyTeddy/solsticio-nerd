#ifndef CELULAR_H_
#define CELULAR_H_

#include "Boton.h"
#include "Pantalla.h"
#include "Numero.h"
#include "Poligono.h"


class Celular {
private:
	Poligono cel; //carcasa del celular
	Poligono sombra[4]; //sombras del celular
	Poligono botonera;
	Pantalla pantalla;
	Boton boton;
	Numero *numero[10]; //todo ver!

	void crearCarcasa();
	void crearSombras();

public:
	Celular();
	~Celular();

	void dibujar();
};

#endif /* CELULAR_H_ */
