#include "callbacksTeclado.h"

void CallBacksTeclado::setCelular(Celular* celular) {
	
	this->celular= celular;
}
	
void CallBacksTeclado::pressedNumber(int number) {
	
	glBegin(GL_POINTS);

		celular->apretarBoton(number);
		celular->dibujar();

	glEnd();

	glutSwapBuffers();

	//Timer
	unsigned int t= time(NULL);
	unsigned int endWait = t+SECONDS;
	while(t <= endWait) { t = time( NULL ); }

	glBegin(GL_POINTS);

		celular->soltarBoton();
		celular->dibujar();

	glEnd();
	glutSwapBuffers();
	
}

void CallBacksTeclado::changeLine(char type) {
	
	celular->cambiarLinea(type);
	glBegin(GL_POINTS);

		celular->dibujar();

	glEnd();

	glutSwapBuffers();
}	

void CallBacksTeclado::zoom(char type) {
	//hacer zoom
	glBegin(GL_POINTS);

		celular->dibujar();

	glEnd();

	glutSwapBuffers();
}	

void CallBacksTeclado::moveView(char orientation) {
	//mover vista
	
	glBegin(GL_POINTS);

		celular->dibujar();

	glEnd();

	glutSwapBuffers();
}

void CallBacksTeclado::clearScreen() {
	
	celular->limpiarPantalla();
	glBegin(GL_POINTS);

		celular->dibujar();

	glEnd();

	glutSwapBuffers();
}
