#include "ContenedorTexturas.h"


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

ContenedorTexturas::~ContenedorTexturas() {
	vaciarContenedor();
}

ContenedorTexturas* ContenedorTexturas::getInstancia() {
	if (!instancia)
		instancia = new ContenedorTexturas();
	return instancia;
}

GLuint ContenedorTexturas::cargarImagen(std::string ruta) {
		GLuint tex = 0;

		// busco si la imagen ya esta cargada
		for (size_t pos=0; pos < nombreTex.size(); pos++) {
			if (ruta == nombreTex[pos])
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

GLuint ContenedorTexturas::cargarImagenDesdeArchivo(std::string &nombre) {

	std::string path(PATH_TEX);
	path += nombre;
	SDL_Surface *imagen = IMG_Load(path.c_str());
	if((!imagen) || (!imagen->pixels) ) {
		std::cerr << "Error al cargar la imagen "<<path << std::endl;
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
		SDL_FreeSurface(imagen);
		std::cerr << "Advertencia!!!! la imagen que intenta cargar no es true color "<< std::endl;
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D,tex);	//indica con que textura estoy trabajando

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //repeat o clamp
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	//mezcla la informacion de textura con la de color
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	//crea en mipmap
	gluBuild2DMipmaps(GL_TEXTURE_2D,numColores,imagen->w,
		  imagen->h,formatoTextura,
		  GL_UNSIGNED_BYTE,imagen->pixels);

	return tex;
}

void ContenedorTexturas::mostrarImagenesCargadas() {
	std::cout<<"Imagenes Cargadas"<<std::endl<<std::endl;
	for(size_t pos=0; pos < nombreTex.size(); pos++){
		std::cout<<nombreTex[pos]<<"\t"<<idTex[pos]<<std::endl;
	}
	std::cout.flush();
}

void ContenedorTexturas::liberarImagenesCargadas() {
	while ( ! bitmaps.empty() ) {
		 SDL_FreeSurface(bitmaps.back());
		 bitmaps.pop_back();
	}

		glDeleteTextures(idTex.size(),&(idTex[0]));
		idTex.clear();
		nombreTex.clear();
}

void ContenedorTexturas::vaciarContenedor() {
	mostrarImagenesCargadas();
	liberarImagenesCargadas();
}



