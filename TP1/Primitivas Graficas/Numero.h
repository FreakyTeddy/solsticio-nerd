#ifndef NUMERO_H_
#define NUMERO_H_

#include "Poligono.h"

enum NUMERO {
	CERO = 0,
	UNO = 1,
	DOS = 2,
	TRES = 3,
	CUATRO = 4,
	CINCO = 5,
	SEIS = 6,
	SIETE = 7,
	OCHO = 8,
	NUEVE = 9
};

class Numero: public Poligono {

private:
	/* crean los vertices correspondientes al numero */
	void crearUno();
	void crearDos();
	void crearTres();
	void crearCuatro();
	void crearCinco();
	void crearSeis();
	void crearSiete();
	void crearOcho();
	void crearNueve();
	void crearCero();
public:

	/* se crea un numero con la forma especificada por num */
	Numero(int num);

	~Numero();
};

#endif /* NUMERO_H_ */
