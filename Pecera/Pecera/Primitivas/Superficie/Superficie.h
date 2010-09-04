#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

#include "../Vertice.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class Superficie {

private:
	static unsigned int render_mode;

protected:
	std::vector<Vertice> superficie; //malla de vertices de la superficie
	std::vector<Vertice> normales;
	std::vector<GLuint> indices;
	unsigned int tam; 		 //tamanio de la curva "forma"
	//TODO faltaria malla de color/textura



	/* setea los indices para dibujado con draw elements */
	void setIndices();

	/* generar las normales de iluminacion */
	void setNormales();
	
	void setTextura();

	/* inicializa la superficie creando normales, indices y texturas */
	void init();

public:

	Superficie();
	virtual ~Superficie();

	/* cambia al siguiente modo de renderizado TRIANG -> QUAD -> LINE */
	static void nextMode();

	void dibujar();

};

#endif /* SUPERFICIE_H_ */
