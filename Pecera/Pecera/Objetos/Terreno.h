
#ifndef TERRENO_H_
#define TERRENO_H_

#include "../Primitivas/Superficie/SuperficieBarrido.h"

class Terreno {

private:
	Superficie* sup;

public:
//TODO obtener la altura en una posicion del terreno.
	Terreno();

	~Terreno();

	void dibujar(unsigned int render_mode) {
		glFrontFace( GL_CCW );
		glCullFace( GL_FRONT );
		glEnable(GL_CULL_FACE);
			sup->dibujar(render_mode);
		glDisable(GL_CULL_FACE);
	}

	/* dado un punto en el terreno devuelve su altura */
	float getAltura(float x, float y) {

//		std::vector<Vertice> &superficie = sup->getMalla();
//		unsigned int tam = sup->getTamanio();
		float altura = 0;


		return altura;
	}

};

#endif /* TERRENO_H_ */
