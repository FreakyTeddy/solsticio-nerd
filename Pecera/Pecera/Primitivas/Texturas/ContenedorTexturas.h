#ifndef CONTENEDORTEXTURAS_H_
#define CONTENEDORTEXTURAS_H_

#define PATH_TEX "./Escena/res/"

#include <iostream>
#include <vector>
#include <GL/glut.h>

/*
 * Administra las texturas que se utilizan
 * Evita que se carge mas de una vez la misma textura
 *
 * */

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>


class ContenedorTexturas {

private:
	std::vector<std::string> nombreTex;	// nombre de la imagen bmp
	std::vector<GLuint>	idTex;			// identificador de la textura correspondiente a la imagen
	std::vector<SDL_Surface*> bitmaps;	// estructura que contiene los pixels de textura
	static ContenedorTexturas *instancia;

	ContenedorTexturas();


	/* carga una imagen desde el archivo bmp especificado. Devuelve su identificador de textura */
	GLuint cargarImagenDesdeArchivo(std::string &nombre);

	void liberarImagenesCargadas();

public:

	~ContenedorTexturas();

	static ContenedorTexturas* getInstancia();

	/* Devuelve el identificador de la textura ubicada en la ruta especificada */
	GLuint cargarImagen(std::string ruta);

	/* muestra por pantalla las imagenes cargadas en memoria */
	void mostrarImagenesCargadas();

	/* DANGER! solo se llama en el exit.. */
	void vaciarContenedor();

};

#endif /* CONTENEDORTEXURAS_H_ */
