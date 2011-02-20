#ifndef CONTROLADORESCENA_H_
#define CONTROLADORESCENA_H_

#include "ContenedorObjetos.h"
#include "../Camara/Camara.h"
#include "../Objetos/Objetos.h"
#include "../Objetos/Terreno.h"
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
	bool ver_tray;

	Terreno terreno;

	Cardumen* cardumen1;
	ObjetoAnimado* alga1;
	ObjetoAnimado* alga2;
	//Animacion* alga1;
	ObjetoViajero* burbujas[10];

	static ControladorEscena* instancia;	//quiero un timeeeeeeeeeer!!
	static bool animando; //mutex?????

	/* realiza la transicion de frames y redibuja la escena */
	static void animar(const int n);

public:
	ControladorEscena();
	~ControladorEscena();

	/* dibuja la escena */
	void generarEscena();

	/* cambia al siguiente modo de renderizado COLOR -> TEXTURA -> MALLA */
	void nextRenderMode();

	/* devuelve el modo de renderizado de escena */
	unsigned int getRenderMode();

	/* devuelve un puntero a la camara de la escena */
	Camara* getCamara();

	/* cambia el estado de animacion: activa/inactiva
	 * No requiere ReDesplay */
	void nextAnimationMode();

	/* avanza la animacion 1 frame */
	void nextFrame(){
		animar(0);
	}

	void nextTrackDisplayMode();

};

#endif /* CONTROLADORESCENA_H_ */
