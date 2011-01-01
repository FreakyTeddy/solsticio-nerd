#include "Textura.h"

Textura::Textura() {
	tex = 0;

}

Textura::~Textura() {
	// TODO Auto-generated destructor stub
}

GLuint Textura::cargarImagen(std::string ruta) {


		SDL_Surface* imagen = IMG_Load(ruta.c_str());
		if(!imagen) {
			std::cerr << "Error al cargar la imagen " << std::endl;
			return 0;
		}
		/* VER que es estooo */
		//	SDL_LockSurface(imagen);
		//	imagenRGB = SDL_CreateRGBSurfaceFrom(imagen->pixels,imagen->w,imagen->h,3,imagen->w*sizeof(uint32_t),0,0,0,0);
		//	if(!imagenRGB){
		//		std::cerr << "Error al convertir la imagen a RGB !!! " << std::endl;
		//		return NULL;
		//	}
		//	SDL_UnlockSurface(imagen);


		int numColores = 0;
		int formatoTextura = 0;

		glPixelStorei(GL_UNPACK_ALIGNMENT,4);
		glGenTextures(1, &tex);

		//De acuerdo al formato de la imagen, chequeo y seteo
		// el formato de textura correspondiente.
		//en caso de no ser una imagen "true color" muestra el error
		// por cerr informando que probablemente la imagen no se
		//observe correctamente

		numColores = imagen->format->BytesPerPixel;
		if (numColores == 4){     //Posee transparencias

				if (imagen->format->Rmask == 0x000000ff)
						formatoTextura = GL_RGBA;
				else
						formatoTextura = GL_BGRA;
		} else if (numColores == 3){     // no posee transparencias

				if (imagen->format->Rmask == 0x000000ff)
						formatoTextura = GL_RGB;
				else
						formatoTextura = GL_BGR;
		} else {
				std::cerr << "Advertencia!!!! la imagen que intenta cargar no es true color "<< std::endl;
				std::cerr << " Es probable que no se visualice correctamente esta imagen. " << std::endl;
		}

		glBindTexture(GL_TEXTURE_2D,tex);	//indica con que textura estoy trabajando

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //TODO !! cambiar el decal!

		gluBuild2DMipmaps(GL_TEXTURE_2D,4,imagen->w,
			  imagen->h,formatoTextura,
			  GL_UNSIGNED_BYTE,imagen->pixels);

		return tex;
}

bool Textura::tieneTextura() {
	return (tex!=0);
}

GLuint Textura::getID() {
	return tex;
}

