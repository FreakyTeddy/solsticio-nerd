#ifndef CONTROLADOROBJETOS_H_
#define CONTROLADOROBJETOS_H_

#include "../Primitivas/Superficie/SuperficieBarrido.h"
#include "../Primitivas/Superficie/SuperficieRevolucion.h"
#include "../Primitivas/Curva/Curva.h"
#include "../Primitivas/Texturas/Textura.h"

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
enum _dibujos { FLORERO=0, ALGA1, ALGA2, ALGA3, PEZ1, PEZ2, PEZ3, ROCA1, ROCA2};

class ContenedorObjetos {
private:
	Curva curva;
	Material mat_escenario;

	Superficie* superficies[MAX_DIBUJOS];
	enum _dibujos _d;

	Textura textura[8];	//texturas del escenario
//	GLuint dl_handle;	//handle de la Display list del Escenario


	void crearSuperficies();

	/* solo se llaman una vez. saben dibujar los objetos */
	Superficie* crearAlga1();
	Superficie* crearAlga2();
	Superficie* crearPez1();
	Superficie* crearRoca1();
	Superficie* crearFlorero();

	void crearEscenario();


public:
	ContenedorObjetos();
	~ContenedorObjetos();


	// dibuja el objeto indicado por id
	void dibujarObjeto(unsigned int id, unsigned int render_mode);

	void dibujarEscenario(unsigned int render_mode);


};

#endif /* CONTROLADOROBJETOS_H_ */
