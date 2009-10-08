#ifndef BOTONERA_H_
#define BOTONERA_H_

#include "Poligono.h"
#include "Boton.h"

class Botonera {
private:
	Poligono fondo;
	Numero **numero;
	Boton boton;
	int b_apretado; //indica el boton que esta apretado	

public:

	Botonera();
	~Botonera();

	void setNumeros(Numero **numeros);

	void dibujar(MatrizTrans2D &mat);

	/* recibe -1 si no hay botones apretados */
	void apretarBoton(int boton);

	void soltarBoton();
	
};

#endif /*BOTONERA_H_*/
