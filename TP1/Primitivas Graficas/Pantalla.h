#ifndef PANTALLA_H_
#define PANTALLA_H_

#include "Numero.h"
#include "Poligono.h"

class Pantalla {
private:
	Poligono pantalla;


public:
	Pantalla();
	~Pantalla();

	/* borra todos los numeros de la pantalla */
	void limpiar();

	/* si hay lugar agrega el numero a la pantalla. */
	void agregarNumero(Numero *numero);

	/* dibuja la pantalla con los numeros VER!!!*/
	void dibujar();
};

#endif /* PANTALLA_H_ */
