#ifndef TRANSFORMACION2D_H_
#define TRANSFORMACION2D_H_

#include "Matriz/matrizTrans2D.h"
#include "../Vertice.h"
#include "../../Constantes.h"
class Transform2D {
	
	private:
		MatrizTrans2D* matTrans;
		MatrizTrans2D matView;
		MatrizTrans2D matComposite;
		
		/* Carga la matriz de vista.
		 */
		void loadMatView(int Wp, int Hp, int Wm, int Hm, Vertice leftDown);
	
	public:
		/* Construye una transformacion 2D
		 * */
		Transform2D();
		
		/* Convierte la matriz total de transformacion y la de vista en matriz identidad	
		 * */
		void setIdentity();

		/* Modifica la matriz de transformacion	
		 * */
		void setMatTrans(MatrizTrans2D* matTrans);

		/* Modifica la matriz de vista
		 *
		 * @param Wp El ancho de la pantalla
		 * @param Hp El alto de la pantalla
		 * @param Wm El ancho del mundo 2D
		 * @param Hm El alto del mundo 2D
		 * @param leftDown El vertice inferior izquiero del mundo 2D.
		 * */
		void setMatView(int Wp, int Hp, int Wm, int Hm, Vertice leftDown);
		
		/* Con las matrices de vista y transformacion calcula la transformacion
		 * desde el mundo real a la pantalla
		 * */
		Vertice transformVerts2D(Vertice vert);
};

#endif /*TRANSFORMACION2D_H_*/
