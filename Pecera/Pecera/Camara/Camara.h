#ifndef CAMARA_H_
#define CAMARA_H_

#include <GL/glut.h>
#include <stdlib.h>

/*
 * Clase que controla la camara
 * Por ejemplo, controla el seguimiento de peces, rotaciones, posicion
 */

class Camara {
private:
	float eye[3];	//posicion
	float at[3];	//centro
	float up[3];	//vector normal
	int tras[3];	//traslacion de la camara

	float rotate_cam_x;
	float rotate_cam_y;
	float zoom;



public:
	Camara();
	~Camara();

	/* se llama ante cada cambio en la camara */
	void lookAt();

	/* mueve la camara tantas unidades en esa direccion */
	void trasladar(float x, float y, float z);

	/* porcentaje para hacer zoom */
	void zoom_in (float p);

	/* vuelve a la configuracion inicial */
	void reset();

	void rotar();
};

#endif
