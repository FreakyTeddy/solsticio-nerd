#ifndef OBJETOS_H_
#define OBJETOS_H_
#include "../Primitivas/Curva/Trayectoria.h"
#include "../Primitivas/Animaciones/Animacion.h"


/* objeto que sigue una trayectoria */

struct ObjetoViajero {
	uint IDobjeto;	//id del objeto que se quiere dibujar
	Trayectoria* recorrido;	//puntos que recorre el objeto

	ObjetoViajero(){
		IDobjeto = 0;
		recorrido = 0;
	}
	void viajar(){
		recorrido->sgtePosicion(); //todo NULLLLLS!!
	}
};


/* Conjunto de objetos iguales que siguen la misma trayectoria trayectoria */

struct Cardumen {
	uint IDobjeto;	//id del objeto que se quiere dibujar
	uint cantidad; 	//cantidad de objetos a dibujar
	float* volumen;	//escala de cada objeto (de 1 a 4)
	Vertice* ubicacion;	//ubicacion de cada objeto en el grupo
	Trayectoria* recorrido;	//puntos que recorre el objeto

	Cardumen(uint id, uint cant, std::vector<Vertice> &puntosControl,bool cerrada,uint intervalo, bool bezier){
		recorrido = new Trayectoria(puntosControl,cerrada,intervalo,bezier);
		IDobjeto = id;
		cantidad = cant;
		init();
	}

//	/* WARNING! hay que asignarle una trayectoria antes de viajar!  el destructor hace delete!!!*/
//	Cardumen(uint id=0, uint cant=1) {
//		IDobjeto = id;
//		cantidad = cant;
//		init();
//	}

	~Cardumen(){
		delete[] volumen;
		delete[] ubicacion;
		delete recorrido;
	}

	void viajar(){
		recorrido->sgtePosicion();
	}
private:
	void init(){
		volumen = new float [cantidad];
		ubicacion = new Vertice [cantidad];
		for(uint i=0;i<cantidad;i++){
			volumen[i] = (rand()%3)+0.5;
			//generar posiciones aleatorias
		}
	}
};


/* Objeto que utiliza una animacion
 * Sirve para tener una sola vez el objeto en memoria
 * y duplicar solamente los datos sobre el frame que se debe dibujar */

struct ObjetoAnimado {
	Animacion* animacion;
	u_short frame;
	short nextFrame;
	bool modo;

	ObjetoAnimado(Animacion* ani, bool ciclico=false){
		animacion = ani;
		frame=0;
		nextFrame=1;	//WARNING! nulls y nextFrame
		modo=ciclico;
	};

	void animar() {
		animacion->animar(frame, nextFrame, modo);
	};

	void dibujar(uint render_mode) {
		animacion->dibujar(render_mode, frame);
	}

};

//TODO ver por que la textura hace efecto raro .. se ve el color pero no las rayitas en el alga.. probar en otro objeto

#endif /* OBJETOS_H_ */
