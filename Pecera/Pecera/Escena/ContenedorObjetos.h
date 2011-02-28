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

	Superficie* superficies[MAX_DIBUJOS];		//rocas y otros
	Animacion* animaciones[MAX_ANIMACIONES];	//algas
	Cardumen* cardumen[MAX_CARDUMEN];			//conj de peces
	Superficie* cuerpos[MAX_TIPO_PECES];	//cuerpo de los peces
	Animacion* colas[MAX_TIPO_PECES];		//cola de los peces
	Animacion* aletas[MAX_TIPO_PECES];		//aleta de los peces
	Vertice2D longitud[MAX_TIPO_PECES];			//y =longitud del centro a la cola del pez; x = ancho del pez en el 000;

	Trayectoria *tray_burbujas;	//burbujas
	GLuint handle_burbuja;

	GLuint handle_agua;
	GLuint idTexAgua;

	void crearSuperficies();
	void crearAnimaciones();
	void crearCardumenes();

	void crearBurbuja();

	/* solo se llaman una vez. saben dibujar los objetos */
	Superficie* crearPez0();
	Superficie* crearPez1();
	Superficie* crearPez2();

	Superficie* crearRoca0();
	Superficie* crearRoca1();
	Superficie* crearRoca2();
	Superficie* crearFlorero();

	Animacion* crearAlga0();
	Animacion* crearAlga1();
	Animacion* crearAlga2();

	Animacion* crearAletaPez0();
	Animacion* crearAletaPez1();
	Animacion* crearAletaPez2();

	Animacion* crearColaPez0();
	Animacion* crearColaPez1();
	Animacion* crearColaPez2();

	Animacion* crearBigote();

	Cardumen* crearCardumen0();
	Cardumen* crearCardumen1();
	Cardumen* crearCardumen2();
	void crearAgua();

	ContenedorObjetos();

public:

	~ContenedorObjetos();

	static ContenedorObjetos* getInstancia();

	// dibuja el objeto indicado por id
	void dibujarObjeto(unsigned int id, unsigned int render_mode);

	void dibujarAgua(unsigned int render_mode);

	void dibujarCardumen(Cardumen* car, unsigned int render_mode);

	Animacion* getAnimacion(unsigned int id);

	Cardumen* getCardumen(unsigned int id);

	void dibujarPez( uint id, uint render_mode, float escala);

	void dibujarFlorero(uint render_mode){
		superficies[FLORERO]->dibujar(render_mode);
	}

	void cambiarTexturaRoca(GLuint id) {
		superficies[ROCA0]->aplicarTextura(id);
		superficies[ROCA1]->aplicarTextura(id);
		superficies[ROCA2]->aplicarTextura(id);
	}

	void animarPeces(){
		for(uint i=0; i< MAX_TIPO_PECES; i++){
			aletas[i]->animar();
			colas[i]->animar();
		}
		for(uint i=0; i< MAX_CARDUMEN; i++){
			cardumen[i]->viajar();
		}
	};

	void animarAlgas(){
		for(uint i=0; i< MAX_ANIMACIONES; i++){
			animaciones[i]->animar();
		}
	};

	Trayectoria* getTrayectoriaBurbujas() {
		return tray_burbujas;
	}

};

#endif /* CONTROLADOROBJETOS_H_ */
