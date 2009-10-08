#ifndef PANTALLA_H_
#define PANTALLA_H_

#include "Numero.h"
#include "Poligono.h"
#include <queue>

class Pantalla {
private:
	Poligono pantalla;
	unsigned int max; //maximo de numeros visibles todo ver que cantidad de numeros
	std::queue<Numero*> numeros; //cola con los numeros de la pantalla

	void cargarPantalla();

public:
	Pantalla();
	~Pantalla();

	/* borra todos los numeros de la pantalla */
	/* para mostrar la pantalla limpia llamar a dibujar */
	void limpiar();

	/* si hay lugar agrega el numero a la pantalla. */
	/* para ver el numero hay que llamar a dibujar */
	void agregarNumero(Numero *numero);

	/* dibuja la pantalla con los numeros */
	void dibujar(MatrizTrans2D &matTrans);
};

#endif /* PANTALLA_H_ */
