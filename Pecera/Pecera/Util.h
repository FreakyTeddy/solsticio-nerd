#ifndef UTIL_H_
#define UTIL_H_

//#include "Primitivas/Vertice.h"
//#include <vector>

#include <math.h>

/*****************  CONSTANTES  *********************/
#define PI 3.14159265359

/*****************  CONFIGURACION  *********************/

#define RM_INICIAL GL_LINE /* render mode inicial */

#define CX_INF -128	/* limites del cubo de escena */
#define CX_SUP 128
#define CY_INF -128
#define CY_SUP 128
#define CZ_INF 0
#define CZ_SUP 128

#define X_INF -126	/* limites de la camara */
#define X_SUP 126
#define Y_INF -126
#define Y_SUP 126
#define Z_INF 2
#define Z_SUP 126


//void rotar(Vertice &eje, float angulo, std::list<Vertice> &puntos) {
//
//}




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
