#ifndef OBJETOS_H_
#define OBJETOS_H_
#include "../Primitivas/Curva/Trayectoria.h"


/* objeto que sigue una trayectoria */

typedef struct ObjetoViajero {
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




typedef struct Cardumen {
	uint IDobjeto;	//id del objeto que se quiere dibujar
	uint cantidad; 	//cantidad de objetos a dibujar
	uint* volumen;	//tamaño de cada objeto
	Vertice* ubicacion;	//ubicacion de cada objeto en el grupo
	Trayectoria* recorrido;	//puntos que recorre el objeto

	Cardumen(uint cant, uint id,std::vector<Vertice> &puntosControl,bool cerrada,uint intervalo, bool bezier){
		recorrido = new Trayectoria(puntosControl,cerrada,intervalo,bezier);
		IDobjeto = id;
		cantidad = cant;
		init();
	}

	~Cardumen(){
		delete volumen;
		delete ubicacion;
		delete recorrido;
	}

	void viajar(){
		recorrido->sgtePosicion();
	}
private:
	void init(){
		volumen = new uint [cant];
		ubicacion = new Vertice [cant];
		for(uint i=0;i<cant;i++){
			volumen[i] = (rand()%4)+0.5;
			//asignar posicion
		}
	}
};


#endif /* OBJETOS_H_ */
