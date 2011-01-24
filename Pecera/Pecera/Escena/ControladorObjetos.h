#ifndef CONTROLADOROBJETOS_H_
#define CONTROLADOROBJETOS_H_

#include "../Primitivas/Superficie/SuperficieBarrido.h"
#include "../Primitivas/Superficie/SuperficieRevolucion.h"
#include "../Primitivas/Curva/Curva.h"


/*
 * El Controlador de Objetos:
 *
 * crea y administra los objetos graficos de la escena,
 * Tiene una copia de cada objeto para evitar duplicados.
 * Sabe como dibujar los objetos.
 *
 *
 * */

#define MAX_DIBUJOS 9
enum _dibujos { FLORERO=0, SUELO, ALGA1, ALGA2, PEZ1, PEZ2, PEZ3, ROCA1, ROCA2};

class ContenedorObjetos {
private:
	Curva curva;

	Superficie* superficies[MAX_DIBUJOS];
	enum _dibujos _d;

	void crearSuperficies();

	/* solo se llaman una vez. saben dibujar los objetos */
	Superficie* crearAlga1();
	Superficie* crearAlga2();
	Superficie* crearSuelo();
	Superficie* crearPez1();
	Superficie* crearRoca1();
	Superficie* crearFlorero();


public:
	ContenedorObjetos();
	~ContenedorObjetos();


	// dibuja el objeto indicado por id
	void dibujarObjeto(unsigned int id, unsigned int render_mode);


};

#endif /* CONTROLADOROBJETOS_H_ */
