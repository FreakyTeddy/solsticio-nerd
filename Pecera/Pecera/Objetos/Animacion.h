#ifndef ANIMACION_H_
#define ANIMACION_H_

#include "../Primitivas/Superficie/Superficie.h"

/**
 * Modela Superficies animadas
 */

class Animacion {

private:
	u_short f_act; 		//frame actual

protected:
	Superficie* frame;	//contiene los frames de la animacion
	u_short f_cant; 	//cant de frames

public:

	Animacion();

	virtual ~Animacion();

	/* dibuja el frame correspondiente a la animacion */
	void animar();
};

#endif /* ANIMACION_H_ */
