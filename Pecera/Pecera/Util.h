#ifndef UTIL_H_
#define UTIL_H_

//#include "Primitivas/Vertice.h"
//#include <vector>

#include <math.h>

/*****************  CONSTANTES  *********************/
#define PI 3.14159265359

/*****************  CONFIGURACION  *********************/

#define RM_INICIAL GL_TEXTURE /* render mode inicial */
#define ANIMACION_INICIAL true	/* estado inicial de la animacion */
#define VER_TRAYECTORIAS false
#define PANTALLA_FULLSCREEN true
#define CANT_BURBUJAS 20

#define CX_INF -178	/* limites del cubo de escena */
#define CX_SUP 178
#define CY_INF -178
#define CY_SUP 178
#define CZ_INF 0
#define CZ_SUP 178

#define X_INF -126	/* limites de la camara */
#define X_SUP 126
#define Y_INF -126
#define Y_SUP 126
#define Z_INF 2
#define Z_SUP 126


/****************** DEFINICION DE OBJETOS ******************/

#define CANT_DORI 5
#define CANT_KOI 3
#define CANT_PLATEADO 10

#define MAX_DIBUJOS 4
#define MAX_ANIMACIONES 4
#define MAX_CARDUMEN 3
#define MAX_TIPO_PECES 3


/* Superficies */
#define FLORERO 0
#define ROCA0 1
#define ROCA1 2
#define ROCA2 3
#define BURBUJA 4

/* Animaciones */
#define ALGA0 0
#define ALGA1 1
#define ALGA2 2
#define BIGOTE 3

/* Peces */
#define PEZ0 0
#define PEZ1 1
#define PEZ2 2
#define PEZLUZ 3

/* Cardumen */
#define CAR0 0
#define CAR1 1
#define CAR2 2

class Util {

public:

	static void rotar(float &p1, float &p2, float angulo) {

		double alfa = 0;
		alfa = angulo*PI/180;
		float aux = p1;
		p1 = aux * cos(alfa) - p2 * sin(alfa);
		p2 = aux * sin(alfa) + p2 * cos(alfa);

	}

	static void rotar(float &p1, float &p2, float seno, float coseno) {

		float aux = p1;
		p1 = aux * coseno - p2 * seno;
		p2 = aux * seno + p2 * coseno;

	}

};


#endif /* UTIL_H_ */
