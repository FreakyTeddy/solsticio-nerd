#ifndef TEXTURA_H_
#define TEXTURA_H_

#include <GL/glut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

/**************

typedef struct SDL_Surface {
	Uint32 flags;
	SDL_PixelFormat *format;
	int w, h;
	Uint16 pitch;
	void *pixels;
	SDL_Rect clip_rect;
	int refcount;
} SDL_Surface;


****************/

class Textura {
private:
	GLuint tex;	//identificador de textura
public:
	Textura();
	~Textura();

	/* carga la textura desde un bmp. Devuelve el identificador de textura */
	GLuint cargarImagen(std::string ruta);

	/* indica si hay una imagen cargada */
	bool tieneTextura();

	/* Devuelve el identificador de textura */
	GLuint getID();

};

#endif /* TEXTURA_H_ */
