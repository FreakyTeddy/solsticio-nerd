#include "ContenedorTexturas.h"


#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

ContenedorTexturas* ContenedorTexturas::instancia = 0;

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


ContenedorTexturas::ContenedorTexturas() {
	nombreTex.clear();
	idTex.clear();
}

ContenedorTexturas::~ContenedorTexturas() {}

ContenedorTexturas* ContenedorTexturas::getInstancia() {
	if (!instancia)
		instancia = new ContenedorTexturas();
	return instancia;
}

GLuint ContenedorTexturas::cargarImagen(std::string ruta) {
		GLuint tex = 0;

		// busco si la imagen ya esta cargada
		for (size_t pos=0; pos < nombreTex.size(); pos++) {
			if (nombreTex[pos] == ruta)
				return idTex[pos];
		}
		// La imagen no esta en la lista, la cargo desde archivo
		tex = cargarImagenDesdeArchivo(ruta);

		//si se pudo cargar la agrego a la lista
		if (tex) {
			nombreTex.push_back(ruta);
			idTex.push_back(tex);
		}

		return tex;
}

GLuint ContenedorTexturas::cargarImagenDesdeArchivo(std::string &ruta) {

	SDL_Surface *imagen = IMG_Load(ruta.c_str());
	if(!imagen) {
		std::cerr << "Error al cargar la imagen " << std::endl;
		return 0;
	}

	GLuint tex = 0;
	int numColores = 0, formatoTextura = 0;

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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	//mezcla la informacion de textura con la de color
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//crea en mipmap
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,imagen->w,
		  imagen->h,formatoTextura,
		  GL_UNSIGNED_BYTE,imagen->pixels);

	return tex;
}

void ContenedorTexturas::mostrarImagenesCargadas() {
	std::cout<<"Imagenes Cargadas"<<std::endl<<std::endl;
	for(size_t pos=0; pos < nombreTex.size(); pos++){
		std::cout<<nombreTex[pos]<<"\t"<<idTex[pos]<<std::endl;
	}
}


