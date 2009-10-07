#ifndef CELULAR_H_
#define CELULAR_H_

#include "Boton.h"
#include "Pantalla.h"


class Celular {
private:
	Pantalla pantalla;
	Boton boton;


public:
	Celular();
	~Celular();
};

#endif /* CELULAR_H_ */
