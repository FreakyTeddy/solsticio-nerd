#include "Imagen.h"

Imagen::Imagen()
{
	
}

SDL_Surface* Imagen::cargarImagen(std::string ruta)
{
	SDL_Surface* imagen = IMG_Load(ruta.c_str());
//	SDL_Surface* imagenRGB = NULL;
	if (!imagen){
		std::cerr << "No Se Pudo Abrir El Archivo De Imagen : " << ruta << std::endl;
		return NULL;
	}
	std::cout << "Se Abrio y Se Cargo La Imagen : " << ruta << std::endl;
//	SDL_LockSurface(imagen);
//	imagenRGB = SDL_CreateRGBSurfaceFrom(imagen->pixels,imagen->w,imagen->h,3,imagen->w*sizeof(uint32_t),0,0,0,0);
//	if(!imagenRGB){
//		std::cerr << "Error al convertir la imagen a RGB !!! " << std::endl;
//		return NULL;
//	}
//	SDL_UnlockSurface(imagen);
//	return imagenRGB;
	return imagen;
		
}

Imagen::~Imagen()
{
	
}
