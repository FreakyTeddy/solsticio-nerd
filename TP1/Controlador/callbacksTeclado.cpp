#include "callbacksTeclado.h"

void CallBacksTeclado::setCelular(Celular* celular) {
	
	this->celular= celular;
}
	
void CallBacksTeclado::pressedNumber(int number) {
	
	celular->apretarBoton(number);

	std::cout << "TIMER" << std::endl;

	//Timer
	clock_t endwait;
  endwait= clock () + SECONDS * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}

	std::cout << "FIN TIMER" << std::endl;
	
	celular->soltarBoton();
}

void CallBacksTeclado::changeLine(char type) {
	
	celular->cambiarLinea(type);	
}	

void CallBacksTeclado::zoom(char type) {
	
}	

void CallBacksTeclado::moveView(char orientation) {
	
}

void CallBacksTeclado::clearScreen() {
	
	celular->limpiarPantalla();
}
