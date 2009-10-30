#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "../Primitivas Graficas/Curva/Curva.h"

#define PASO 1

class Controlador {
	
	private:
		Curva* curva;
		
	public:
		/* Crea un controlador.
		 * */
	  Controlador(Curva* curva);
		
		/* Aumenta el paso de Bezier.
		 * */
		void aumentarPasoBezier();

		/* Disminuye el paso de Bezier.
		 * */
		void disminuirPasoBezier();
		
		/* Aumenta el paso de Bspline.
		 * */
		void aumentarPasoBspline();

		/* Disminuye el paso de Bspline.
		 * */
		void disminuirPasoBspline();
};

#endif /*CONTROLADOR_H_*/
