#include "callbacksTeclado.h"

void CallBacksTeclado::setCelular(Celular* celular) {
	
	this->celular= celular;
}
	
void CallBacksTeclado::pressedNumber(int number) {
	
	celular->apretarBoton(number);

	std::cout << "TIMER" << std::endl;

	//Timer
	unsigned int t= time(NULL);
  unsigned int endWait = t+SECONDS;
  while(t <= endWait) { t = time( NULL ); }

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
