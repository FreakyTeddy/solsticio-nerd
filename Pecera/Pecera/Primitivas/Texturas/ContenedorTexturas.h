#ifndef CONTENEDORTEXTURAS_H_
#define CONTENEDORTEXTURAS_H_


#include <iostream>
#include <vector>
#include <GL/glut.h>

/*
 * Administra las texturas que se utilizan
 * Evita que se carge mas de una vez la misma textura
 *
 * */

// TODO!!! eliminar instancia e imagenes?!?!?



class ContenedorTexturas {

private:
	std::vector<std::string> nombreTex;	// nombre de la imagen bmp
	std::vector<GLuint>	idTex;			// identificador de la textura correspondiente a la imagen

	static ContenedorTexturas *instancia;

	ContenedorTexturas();
	~ContenedorTexturas();

	/* carga una imagen desde el archivo bmp especificado. Devuelve su identificador de textura */
	GLuint cargarImagenDesdeArchivo(std::string &ruta);

public:

	static ContenedorTexturas* getInstancia();

	/* Devuelve el identificador de la textura ubicada en la ruta especificada */
	GLuint cargarImagen(std::string ruta);

	/* muestra por pantalla las imagenes cargadas en memoria */
	void mostrarImagenesCargadas();

};

#endif /* CONTENEDORTEXURAS_H_ */
