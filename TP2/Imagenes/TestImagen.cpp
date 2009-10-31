// Test Basico De Cargar Imagenes
// Simplemente prueba la funcionalidad de la libreria SDL

#include <iostream>
#include "Imagen.h"

int main(int argc,char** argv){

	Imagen image;
	void* retorno = NULL;
	retorno = image.cargarImagen("Imagenes/ubuntu-logo.png");
	std::cout << "retorno: " << retorno << std::endl;
	
	return 0;
}