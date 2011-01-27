#ifndef CONTROLADORESCENA_H_
#define CONTROLADORESCENA_H_

#include "ContenedorObjetos.h"
#include "../Camara/Camara.h"
#include "../Objetos/Objetos.h"
/**
 *  Arma la escena: ubica la camara, los objetos, realiza animaciones.
 *
 *
 *
 */


class ControladorEscena {

private:
	ContenedorObjetos &objetos;
	Camara cam;
	unsigned int render_mode;



public:
	ControladorEscena();
	~ControladorEscena();

	/* dibuja la escena */
	void generarEscena();

	/* cambia al siguiente modo de renderizado COLOR -> TEXTURA -> MALLA */
	void nextMode();

	unsigned int getRenderMode();

	Camara* getCamara();
};

#endif /* CONTROLADORESCENA_H_ */
