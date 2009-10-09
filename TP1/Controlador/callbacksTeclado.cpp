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
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	extern int anchoventanaM;
	extern int altoventanaM;

	switch(type){
		case '+':
			anchoventanaM -= 0.1 * anchoventanaM;
			altoventanaM -= 0.1 * altoventanaM;
			break;
		case '-':
			anchoventanaM += 0.1 * anchoventanaM;
			altoventanaM += 0.1 * altoventanaM;
			break;
		default:
			break;
	}
		celular->dibujar();

	glEnd();

	glutSwapBuffers();
}	

void CallBacksTeclado::moveView(char orientation) {
	//mover vista
	extern int desplazamientoX;
	extern int desplazamientoY;
	
	switch (orientation) {
	case 'L' :
		desplazamientoX -= 20;
		break;
	case 'R' :
		desplazamientoX += 20;
		break;
	case 'D' :
		desplazamientoY += 20;
		break;
	case 'U' :
		desplazamientoY -= 20;
		break;
	}

	glClear(GL_COLOR_BUFFER_BIT);
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
