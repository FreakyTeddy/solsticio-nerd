#include "Numero.h"

Numero::Numero(int num) {
	switch (num) {
	case UNO:
		crearUno();
		break;
	case DOS:
		crearDos();
		break;
	case TRES:
		crearTres();
		break;
	case CUATRO:
		crearCuatro();
		break;
	case CINCO:
		crearCinco();
		break;
	case SEIS:
		crearSeis();
		break;
	case SIETE:
		crearSiete();
		break;
	case OCHO:
		crearOcho();
		break;
	case NUEVE:
		crearNueve();
		break;
	case CERO:
		crearCero();
		break;
	}
}


Numero::~Numero() {}


inline void Numero::crearUno() {
	agregarVertice(20,0);
	agregarVertice(80,0);
	agregarVertice(80,10);
	agregarVertice(60,10);
	agregarVertice(60,100);
	agregarVertice(40,100);
	agregarVertice(20,70);
	agregarVertice(20,50);
	agregarVertice(40,80);
	agregarVertice(40,10);
	agregarVertice(20,10);
	agregarVertice(20,0);
}

inline void Numero::crearDos() {
	agregarVertice(10,0);
	agregarVertice(80,0);
	agregarVertice(80,20);
	agregarVertice(30,20);
	agregarVertice(80,60);
	agregarVertice(80,80);
	agregarVertice(60,100);
	agregarVertice(30,100);
	agregarVertice(10,80);
	agregarVertice(10,60);
	agregarVertice(30,60);
	agregarVertice(30,70);
	agregarVertice(40,80);
	agregarVertice(60,80);
	agregarVertice(60,60);
	agregarVertice(10,20);

}

inline void Numero::crearTres() {

//	agregarVertice(20,100);
//	agregarVertice(20,90);
//	agregarVertice(50,90);
//	agregarVertice(60,80);
//	agregarVertice(60,70);
//	agregarVertice(50,60);
//	agregarVertice(30,60);
//	agregarVertice(30,50);
//	agregarVertice(50,50);
//	agregarVertice(60,40);
//	agregarVertice(60,20);
//	agregarVertice(20,20);
//	agregarVertice(20,0);
//	agregarVertice(60,0);
//	agregarVertice(80,20);
//	agregarVertice(80,40);
//	agregarVertice(60,60);
//	agregarVertice(70,70);
//	agregarVertice(70,90);
//	agregarVertice(60,100);
//quedo horrible!! XD

	agregarVertice(20,100);
	agregarVertice(20,80);
	agregarVertice(60,80);
	agregarVertice(70,70);
	agregarVertice(60,60);
	agregarVertice(30,60);
	agregarVertice(30,40);
	agregarVertice(60,40);
	agregarVertice(70,30);
	agregarVertice(60,20);
	agregarVertice(20,20);
	agregarVertice(20,0);
	agregarVertice(70,0);
	agregarVertice(90,20);
	agregarVertice(90,40);
	agregarVertice(80,50);
	agregarVertice(90,60);
	agregarVertice(90,80);
	agregarVertice(70,100);

}

inline void Numero::crearCuatro() {
	agregarVertice(10,50);
	agregarVertice(10,40);
	agregarVertice(50,40);
	agregarVertice(50,0);
	agregarVertice(70,0);
	agregarVertice(70,40);
	agregarVertice(90,40);
	agregarVertice(90,50);
	agregarVertice(10,50);
	agregarVertice(50,100);
	agregarVertice(70,100);
	agregarVertice(70,50);
	agregarVertice(50,50);
	agregarVertice(50,80);
	agregarVertice(30,50);
}
inline void Numero::crearCinco() {
	agregarVertice(80,100);
	agregarVertice(20,100);
	agregarVertice(20,50);
	agregarVertice(50,50);
	agregarVertice(60,40);
	agregarVertice(60,30);
	agregarVertice(50,20);
	agregarVertice(20,20);
	agregarVertice(20,0);
	agregarVertice(60,0);
	agregarVertice(80,20);
	agregarVertice(80,50);
	agregarVertice(60,70);
	agregarVertice(40,70);
	agregarVertice(40,80);
	agregarVertice(80,80);
}

inline void Numero::crearSeis() {
}

inline void Numero::crearSiete() {
	agregarVertice(20,100);
	agregarVertice(20,80);
	agregarVertice(60,80);
	agregarVertice(20,0);
	agregarVertice(40,0);
	agregarVertice(80,80);
	agregarVertice(80,100);
}

inline void Numero::crearOcho() {
}

inline void Numero::crearNueve() {
}


inline void Numero::crearCero() {
}
