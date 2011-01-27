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
	bool ver_tray;


	Cardumen* cardumen1;



	static ControladorEscena* instancia;	//quiero un timeeeeeeeeeer!!
	static bool animando; //mutex?????

	/* realiza la transicion de frames y redibuja la escena */
	static void animar(const int n);

	void dibujarCardumen(Cardumen* car);
	void crearCardumen();


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

	void nextTrackDisplayMode();

};

#endif /* CONTROLADORESCENA_H_ */
