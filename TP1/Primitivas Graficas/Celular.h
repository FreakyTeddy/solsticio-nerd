#ifndef CELULAR_H_
#define CELULAR_H_

#include "Boton.h"
#include "Pantalla.h"
#include "Numero.h"
#include "Poligono.h"
#include "Botonera.h"

class Celular {
private:

	Numero *numero[10]; //todo ver!

	Poligono cel; //carcasa del celular
	Poligono sombra[4]; //sombras del celular
	Poligono visagra;
	
	Botonera botonera;
	Pantalla pantalla;
	
	void crearCarcasa();
	void crearSombras();

public:
	Celular();
	~Celular();

	void dibujar();
};

#endif /* CELULAR_H_ */
