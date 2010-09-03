#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

#include "../Vertice.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class Superficie {

protected:
	std::vector<Vertice> superficie; //malla de vertices de la superficie
	std::vector<Vertice> normales;
	std::vector<GLuint> indices;
	unsigned int tam; 		 //tamanio de la curva "forma"
	//TODO faltaria malla de color/textura

	void setIndices();

private:
	static unsigned int render_mode;

	/* generar las normales de iluminacion */
	void setNormales(std::vector<Vertice> &ptosCurva, std::vector<Vertice> &ptosNormal);

public:

	Superficie();
	virtual ~Superficie();

	/* cambia al siguiente modo de renderizado TRIANG -> QUAD -> LINE */
	static void nextMode();

	void dibujar();

};

#endif /* SUPERFICIE_H_ */
