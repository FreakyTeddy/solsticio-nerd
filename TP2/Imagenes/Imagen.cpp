#include "Imagen.h"

Imagen::Imagen()
{
	
}

SDL_Surface* Imagen::cargarImagen(std::string ruta)
{
	SDL_Surface* imagen = IMG_Load(ruta.c_str());
	if (!imagen){
		std::cerr << "No Se Pudo Abrir El Archivo De Imagen : " << ruta << std::endl;
		return NULL;
	}
	std::cout << "Se Abrio y Se Cargo La Imagen : " << ruta << std::endl;
	return imagen;
		
}

Imagen::~Imagen()
{
	
}
