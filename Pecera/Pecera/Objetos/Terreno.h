
#ifndef TERRENO_H_
#define TERRENO_H_

#include "../Primitivas/Superficie/SuperficieBarrido.h"

class Terreno {

private:
	Superficie* sup;

public:

	Terreno();

	~Terreno();

	void dibujar(unsigned int render_mode) {
		glFrontFace( GL_CCW );
		glCullFace( GL_FRONT );
		glEnable(GL_CULL_FACE);
			sup->dibujar(render_mode);
		glDisable(GL_CULL_FACE);
	}

};

#endif /* TERRENO_H_ */
