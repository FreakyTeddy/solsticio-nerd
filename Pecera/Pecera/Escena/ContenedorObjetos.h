#ifndef CONTROLADOROBJETOS_H_
#define CONTROLADOROBJETOS_H_

#include "../Primitivas/Superficie/SuperficieBarrido.h"
#include "../Primitivas/Superficie/SuperficieRevolucion.h"
#include "../Primitivas/Curva/Curva.h"
#include "../Primitivas/Texturas/Textura.h"
#include "../Primitivas/Animaciones/Animacion.h"
#include "../Objetos/Objetos.h"

/*
 * El Controlador de Objetos:
 *
 * crea y administra los objetos graficos de la escena,
 * Tiene una copia de cada objeto para evitar duplicados.
 * Sabe como dibujar los objetos.
 *
 *
 * */

#define MAX_DIBUJOS 10
#define MAX_ANIMACIONES 1
#define MAX_CARDUMEN 1



enum _dibujos { FLORERO=0, ALGA1, ALGA2, ALGA3, PEZ1, PEZ2, PEZ3, ROCA1, ROCA2, ROCA3, BURBUJA};

class ContenedorObjetos {

private:

	static ContenedorObjetos *instancia;

	Curva curva;
	Material mat_escenario;

	Superficie* superficies[MAX_DIBUJOS];
	Animacion* animaciones[MAX_ANIMACIONES];
	Cardumen* cardumen[MAX_CARDUMEN];

	Trayectoria *tray_burbujas;

	enum _dibujos _d;

	Textura textura[5];	//texturas del escenario
	GLuint handle_burbuja;

	void crearSuperficies();
	void crearAnimaciones();
	void crearCardumenes();

	void crearBurbuja();

	/* solo se llaman una vez. saben dibujar los objetos */
	Superficie* crearAlga1();
	Superficie* crearAlga2();
	Superficie* crearPez1();
	Superficie* crearRoca1();
	Superficie* crearFlorero();



	Animacion* crearAlga3();
	Animacion* crearAletaPez1();
	Cardumen* crearCardumen1();

	void crearEscenario();

	ContenedorObjetos();

public:

	Trayectoria* getTrayectoriaBurbujas() {
		return tray_burbujas;
	}

	~ContenedorObjetos();

	static ContenedorObjetos* getInstancia();

	// dibuja el objeto indicado por id
	void dibujarObjeto(unsigned int id, unsigned int render_mode);

	void dibujarEscenario(unsigned int render_mode);

	void dibujarCardumen(Cardumen* car, unsigned int render_mode);

	Animacion* getAnimacion(unsigned int id);

	Cardumen* getCardumen(unsigned int id);

};

#endif /* CONTROLADOROBJETOS_H_ */
