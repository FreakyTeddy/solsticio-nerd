///
/// Sistemas Gráficos - 6671
/// 1er cuatrimestre 2009
///
#include "GL/glut.h" 
#include <stdlib.h>

#include "relleno.h"
#include "../Linea/linea.h"

#define ANCHO	800
#define ALTO	600

char caption[]="PRUEBAS VERO";


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
  
  /*PRUEBA LINEA*/
  Linea linea;
  
  /*PRUEBA RELLENO*/
	Relleno relleno;
	
	dcPt* pts0= new dcPt();
	dcPt* pts1= new dcPt();
	dcPt* pts2= new dcPt();
	
	pts0->x= 100;
	pts0->y= 10;
	pts1->x= 50;
	pts1->y= 300;	
	pts2->x= 300;
	pts2->y= 300;  
   
	glBegin(GL_POINTS);
	
	glColor3f(0,1.0,1.0);
	linea.lineaDDA(500, 5, 6, 750);
	relleno.scanLine(2, pts0);
	
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
