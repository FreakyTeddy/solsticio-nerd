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
	agregarVertice(0,50);
	agregarVertice(10,40);
	agregarVertice(40,80);
	agregarVertice(40,10);
	agregarVertice(20,10);
	agregarVertice(20,0);
}

inline void Numero::crearDos()
{
}

inline void Numero::crearTres()
{
}

inline void Numero::crearOcho()
{
}

inline void Numero::crearCinco()
{
}

inline void Numero::crearCuatro()
{
}

inline void Numero::crearSiete()
{
}

inline void Numero::crearNueve()
{
}

inline void Numero::crearSeis()
{
}

inline void Numero::crearCero()
{
}
