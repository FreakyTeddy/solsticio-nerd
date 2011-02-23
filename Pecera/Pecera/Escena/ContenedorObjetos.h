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

class ContenedorObjetos {

private:

	static ContenedorObjetos *instancia;

	Curva curva;

	Material mat_escenario;	// Material del Escenario
	Textura textura[5];		// Texturas del escenario

	Superficie* superficies[MAX_DIBUJOS];		//rocas y otros
	Animacion* animaciones[MAX_ANIMACIONES];	//algas
	Cardumen* cardumen[MAX_CARDUMEN];			//conj de peces
	Superficie* cuerpos[MAX_TIPO_PECES];	//cuerpo de los peces
	Animacion* colas[MAX_TIPO_PECES];		//cola de los peces
	Animacion* aletas[MAX_TIPO_PECES];		//aleta de los peces
	Vertice2D longitud[MAX_TIPO_PECES];			//y =longitud del centro a la cola del pez; x = ancho del pez en el 000;

	Trayectoria *tray_burbujas;	//burbujas
	GLuint handle_burbuja;

	void crearSuperficies();
	void crearAnimaciones();
	void crearCardumenes();

	void crearBurbuja();

	/* solo se llaman una vez. saben dibujar los objetos */
	Superficie* crearPez1();
	Superficie* crearPez1();
	Superficie* crearPez2();
	Superficie* crearRoca1();
	Superficie* crearFlorero();

	Animacion* crearAlga3();
	Animacion* crearAlga4();
	Animacion* crearAletaPez1();
	Animacion* crearAletaPez2();
	Animacion* crearColaPez1();
	Animacion* crearColaPez2();
	Animacion* crearBigote();


	Cardumen* crearCardumen1();
	Cardumen* crearCardumen2();
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

	void dibujarPez( uint id, uint render_mode, float escala);

	void animarPeces(){
//		for(uint i=0; i< MAX_TIPO_PECES; i++){
//			aletas[i]->animar();
//			colas[i]->animar();
//		}
//		for(uint i=0; i< MAX_CARDUMEN; i++){
//			cardumen[i]->viajar();
//		}

//		colas[PEZ1]->animar();
//		aletas[PEZ1]->animar();
//		cardumen[CAR1]->viajar();
//		cardumen[CAR0]->viajar();
//
//		colas[PEZ2]->animar();
//		aletas[PEZ2]->animar();
//		animaciones[BIGOTE]->animar();
	};

};

#endif /* CONTROLADOROBJETOS_H_ */
