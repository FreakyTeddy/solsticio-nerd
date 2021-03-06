///
/// Sistemas Gráficos - 6671
/// 2do cuatrimestre 2009
///
#include "GL/glut.h"
#include <stdlib.h>

#include "Primitivas Graficas/Celular.h"
#include "Controlador/callbacksTeclado.h"

#define ANCHO	800
#define ALTO	600

char caption[]= "El Celular";

Celular celular;
CallBacksTeclado callbacks;

//dimensiones de la ventana del mundo
int anchoventanaM = 160;
int altoventanaM = 160;
int desplazamientoX = 0;
int desplazamientoY = 0;

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
}

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	callbacks.setCelular(&celular);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
 	glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	glBegin(GL_POINTS);

	celular.dibujar();

	glEnd();

 	glutSwapBuffers();
}

/* x, y coordenadas mouse cuando se presiona key
*/
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{		//toma solo las minusculas
	case 0x30:
		callbacks.pressedNumber(0);
		break;
	case 0x31:
		callbacks.pressedNumber(1);
		break;
	case 0x32:
		callbacks.pressedNumber(2);
		break;
	case 0x33:
		callbacks.pressedNumber(3);
		break;
	case 0x34:
		callbacks.pressedNumber(4);
		break;
	case 0x35:
		callbacks.pressedNumber(5);
		break;
	case 0x36:
		callbacks.pressedNumber(6);
		break;
	case 0x37:
		callbacks.pressedNumber(7);
		break;
	case 0x38:
		callbacks.pressedNumber(8);
		break;
	case 0x39:
		callbacks.pressedNumber(9);
		break;
	case 0x2B:
		callbacks.zoom('+');
		break;
	case 0x2D:
		callbacks.zoom('-');
		break;
	case 0x62:
		callbacks.changeLine('B');
		break;
	case 0x63:
		//limpia la pantalla del cel
		callbacks.clearScreen();
		break;
	case 0x64:
		callbacks.changeLine('D');
		break;
	case 0x1b:
		exit (1);
		break;
	}
}

void specialKeys(int key,int x, int y) {

	switch(key) {
	case GLUT_KEY_LEFT:
		callbacks.moveView('L');
		break;
	case GLUT_KEY_RIGHT:
		callbacks.moveView('R');
		break;
	case GLUT_KEY_UP:
		callbacks.moveView('U');
		break;
	case GLUT_KEY_DOWN:
		callbacks.moveView('D');
		break;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   
   glutInitWindowSize (ANCHO, ALTO);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (caption);
   init();
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeys);
   
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();

   return 0;
}
