#ifndef PANTALLA_H_
#define PANTALLA_H_

#include "Numero.h"
#include "Poligono.h"
#include <queue>

class Pantalla {
private:
	Poligono pantalla;
	int max; //maximo de numeros visibles
	std::queue<Numero*> numeros; //cola con los numeros de la pantalla

	void cargarPantalla();

public:
	Pantalla();
	~Pantalla();

	/* borra todos los numeros de la pantalla */
	void limpiar();

	/* si hay lugar agrega el numero a la pantalla. */
	void agregarNumero(Numero *numero);

	/* dibuja la pantalla con los numeros */
	void dibujar();
};

#endif /* PANTALLA_H_ */
