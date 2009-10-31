#ifndef IMAGEN_H_
#define IMAGEN_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

class Imagen{
	private:
	
	public:
		Imagen();
		void* cargarImagen(std::string ruta);
		~Imagen();
	
};


#endif /*IMAGEN_H_*/
