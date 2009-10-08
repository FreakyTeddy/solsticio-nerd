#include "callbacksTeclado.h"

CallBacksTeclado::CallBacksTeclado(Celular celular): celular(celular) {}
	
void CallBacksTeclado::pressedNumber(int number) {
	
	celular.apretarBoton(number);

	//Timer
	clock_t endwait;
  endwait= clock () + SECONDS * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
	
	celular.soltarBoton();
}

void CallBacksTeclado::changeLine(char type) {
	
	celular.cambiarLinea(type);	
}	

void CallBacksTeclado::zoom(char type) {
	
}	

void CallBacksTeclado::moveView(char orientation) {
	
}

void CallBacksTeclado::clearScreen() {
	
	celular.limpiarPantalla();
}
