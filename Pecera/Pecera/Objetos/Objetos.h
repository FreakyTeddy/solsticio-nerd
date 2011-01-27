#ifndef OBJETOS_H_
#define OBJETOS_H_
#include "../Primitivas/Curva/Trayectoria.h"


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

	/* WARNING! hay que asignarle una trayectoria antes de viajar!  el destructor hace delete!!!*/
	Cardumen(uint id=0, uint cant=1) {
		IDobjeto = id;
		cantidad = cant;
		init();
	}

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


#endif /* OBJETOS_H_ */
