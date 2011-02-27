#ifndef TEXTURA_H_
#define TEXTURA_H_


#include "../Vertice.h"
#include "ContenedorTexturas.h"

#include <GL/glut.h>
#include <iostream>
#include <vector>


class Textura {

private:

	GLuint tex;	// identificador de textura
	int modo;	// modo de aplicacion de textura
	ContenedorTexturas *contenedorTex;

public:

	Textura();

	/* crea el objeto textura con el modo especificado */
	Textura(int modo);

	/* crea el objeto textura con el modo e imagen especificada */
	Textura (std::string path_imagen, int modo);

	~Textura();

	/* carga el bmp de textura a aplicar a una superficie */
	void cargarImagen(std::string ruta);

	/* setea el modo de aplicado de textura */
	void setModoMosaico();
	void setModoExpandida();

	/* indica si hay una imagen cargada */
	bool tieneTextura();

	/* Devuelve el identificador de textura */
	GLuint getID();

	void setID(GLuint id) {
		tex = id;
	};

	/** asigna coordenadas de textura a cada vertice de la superficie
	 * recibe el la cant de vertices de la curva patron * */
	void generarCoordenadas(const std::vector<Vertice> &sup, std::vector<Vertice2D> &texCoord, uint tam);

};

#endif /* TEXTURA_H_ */
