///
/// Sistemas Gráficos - 6671
/// 1er cuatrimestre 2009
///
#include "GL/glut.h" 
#include <stdlib.h>
#include "Curva.h"

#define ANCHO	800
#define ALTO	600

char caption[]= "-- Curvas --";


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
	///
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	///
    
  Curva curva;  
  
  int numberOfPoints= 4;
  
  Vertice2D* cp;
  cp= new Vertice2D[numberOfPoints];
  
 		cp[0].x= 100;
		cp[0].y= 100;  
		
 		cp[1].x= 200;
		cp[1].y= 200;

 		cp[2].x= 300;
		cp[2].y= 100;

 		cp[3].x= 400;
		cp[3].y= 200;
    
  Vertice2D* curve;
  curve= new Vertice2D[numberOfPoints];   

	glBegin(GL_LINE_STRIP);
	
	glColor3f(1.0,0,0);
		glVertex2i(cp[0].x, cp[0].y);
		glVertex2i(cp[1].x, cp[1].y);
		glVertex2i(cp[2].x, cp[2].y);
    glVertex2i(cp[3].x, cp[3].y);

	glColor3f(0,0,1.0);
	curva.Bezier(cp, numberOfPoints, curve);
	
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
