#include "Imagen.h"

Imagen::Imagen()
{
	
}

void* Imagen::cargarImagen(std::string ruta)
{
	SDL_Surface* imagen = IMG_Load(ruta.c_str());
	if (!imagen){
		std::cerr << "No Se Pudo Abrir El Archivo De Imagen : " << ruta << std::endl;
		return NULL;
	}
	std::cout << "Se Abrio y Se Cargo La Imagen : " << ruta << std::endl;
	//convertir de SDL_Surface a el formato que necesita Open GL para
	//manejar la textura.
	return imagen;
		
}

Imagen::~Imagen()
{
	
}
