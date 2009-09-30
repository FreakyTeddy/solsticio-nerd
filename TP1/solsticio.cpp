///
/// Sistemas Gráficos - 6671
/// 2do cuatrimestre 2009
///
#include "GL/glut.h"
#include <stdlib.h>

#include "Primitivas Graficas/Linea/linea.h"
#include "Primitivas Graficas/Poligono.h"


#define ANCHO	800
#define ALTO	600

char caption[]="Solsticio Nerd";

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
}

void init(void)
{
}


void display(void)
{
	Poligono p;  //TODO esta para testear :P
	p.agregarVertice(10,10);
	p.agregarVertice(200,100);
	p.agregarVertice(150,300);
	//Linea linea;
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    glBegin(GL_POINTS);
//		glColor3f(0,1.0,1.0);
//		linea.lineaBresenham(10,10,300,200);
//
		glColor3f(255.0,0,6.0);
//		linea.lineaDDA(500, 5, 6, 750);

    p.dibujar();

	glEnd();
	
	///
  	glutSwapBuffers();
	///
}




/* x, y coordenadas mouse cuando se presiona key
*/
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1b:
		exit (1);
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
   init ();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();

   return 0;
}
