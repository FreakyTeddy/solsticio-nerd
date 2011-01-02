#include "Textura.h"

#define M_MOSAICO	1
#define M_EXPANDIDA	2


Textura::Textura() {
	tex = 0;
	modo = M_MOSAICO;
	contenedorTex = ContenedorTexturas::getInstancia();
}

Textura::~Textura() {}

void Textura::cargarImagen(std::string ruta) {
	tex = contenedorTex->cargarImagen(ruta);
}

void Textura::generarCoordenadas(const std::vector<Vertice> &sup, std::vector<Vertice2D> &texCoord){
	//TODO! generar coordenadas en base al modo
}

bool Textura::tieneTextura() {
	return (tex!=0);
}

GLuint Textura::getID() {
	return tex;
}

void Textura::setModoMosaico() {
	modo = M_MOSAICO;
}

void Textura::setModoExpandida() {
	modo = M_EXPANDIDA;
}
