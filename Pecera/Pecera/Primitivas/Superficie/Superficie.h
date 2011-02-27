#ifndef SUPERFICIE_H_
#define SUPERFICIE_H_

#include "../Vertice.h"
#include "../Texturas/Textura.h"
#include "../Materiales/Material.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

class Superficie {

private:

	Material material;	//material con el que se dibuja la sup

protected:
	GLuint dl_handle;	//display list que dibuja con triangulos. dl_handle+1 dibuja con texturas.
	GLenum cull;

	std::vector<Vertice> superficie;	// malla de vertices 3D de la superficie
	std::vector<Vertice> normales;		// normales de iluminacion en cada vertice 3D
	std::vector<Vertice2D> texCoord;	// coordenadas de textura de cada vertice 3D
	std::vector<GLuint> indices;		// recorrido de la malla

	Textura	tex;		// contiene la textura de la superficie

	unsigned int tam;	// cantidad de vertices de la curva "forma"
	bool cerrada;		//indica si la curva es cerrada
	bool keep; 			//false-> borra los puntos de la superficie

	/* setea los indices para dibujado con triangle strip*/
	void setIndices();

	/* generar las normales de iluminacion para una superficie regular*/
	void setNormales();

	/* inicializa la superficie creando normales, indices y texturas */
	void init();

private:

	void generarDisplayList();
	void generarDisplayListTextura();


protected:
	Superficie();

public:

	virtual ~Superficie();

	/* dibuja la superficie segun el modo de renderizado */
	void dibujar(unsigned int render_mode);

	void dibujarNormales();

	/* aplica la textura especificada a la superficie */
	void aplicarTextura (std::string ruta);

	void aplicarTextura (GLuint id) {
		tex.setID(id);
	}

	Material* getMaterial();

	std::vector<Vertice>& getMalla() {
		return superficie;
	}
	unsigned int getTamanio(){
		return tam;
	};

	void setMaterial(Material &m);

	void setCullFace(GLenum x) {
		cull=x;
	}

};

#endif /* SUPERFICIE_H_ */
