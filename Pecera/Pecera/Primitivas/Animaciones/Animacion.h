#ifndef ANIMACION_H_
#define ANIMACION_H_

#include "../Superficie/Superficie.h"

/**
 * Modela Superficies animadas
 */

class Animacion {

private:

	short f_next;		//indica cual es el siguiente frame
	bool m_ciclico;		//modo de transicion de frames


protected:
	Superficie** frame;	//contiene los frames de la animacion


public:
	u_short f_cant; 	//cant de frames
	u_short f_act; 		//frame actual

	/* crea una animacion con una superficie de Barrido donde Cambia la traslacion
	 * WARNING! deben pasarse unicamente los puntos de control :) */
	Animacion(std::vector<Vertice> &forma, std::vector<Vertice> &trasl_inicial, std::vector<Vertice> &trasl_final, std::vector<Vertice> &defo, u_int intervalo);


	/* crea una animacion senoidal para una superficie de barrido */
	/* inicial: vertice a partir del cual se aplica la funcion */
	Animacion(std::vector<Vertice> &forma, std::vector<Vertice> &trasl, std::vector<Vertice> &defo,Vertice &dir, uint inicial, uint cant_frames, bool ciclico);

	~Animacion();

	/* dibuja el frame correspondiente a la animacion y pasa al frame siguiente */
	void animaryDibujar(unsigned int render_mode);

	/* pasa al siguiente frame */
	void animar();

	/* dibuja el frame actual */
	void dibujar(unsigned int render_mode);


/* Metodos para usar animaciones de forma "externa" con ObjetoAnimado */

	/* pasa al frame siguiente de f_num segun el modo y el intervalo */
	void animar(u_short &f_num, short &f_int, bool modo);

	/* dibuja el frame indicado */
	void dibujar(unsigned int render_mode, u_short f_num);

	/* indica si la transicion de frames es ciclica o "ida y vuelta" */
	void setModoTransicion(bool ciclico);

	void setMaterial(Material &m);

	void setCull(GLenum x){
		for (u_short i=0; i < f_cant; i++)
			frame[i]->setCullFace(x);
	};

	void setTextura(std::string name);

};

#endif /* ANIMACION_H_ */
