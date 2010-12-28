#ifndef CAMARA_H_
#define CAMARA_H_

#include <GL/glut.h>
#include <stdlib.h>
#include "../Primitivas/Vertice.h"


/*
 * Clase que controla la camara
 * Por ejemplo, controla el seguimiento de peces, rotaciones, posicion
 */

class Camara {
private:
	Vertice eye;//posicion
	Vertice at;	//centro
	Vertice up;	//vector normal
	float zoom;	//zoom realizado



public:
	Camara();
	~Camara();

	/* se llama ante cada cambio en la camara */
	void lookAt();

	/* vuelve a la configuracion inicial */
	void reset();

	/* porcentaje para hacer zoom */
	void zoom_in (float p);

	/* mueve la camara tantas unidades en esa direccion */
	void trasladar_f(float cant);	//forward
	void trasladar_s(float cant);	//sideways
	void trasladar_u(float cant);	//upward

	/* rotar la camara en la direccion vertical y horizontal*/
	void rotar_h(float cant);
	void rotar_v(float cant);
};

#endif
