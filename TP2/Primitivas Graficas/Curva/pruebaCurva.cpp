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
  
  std::list<Vertice2D> ptosControl;

  Vertice2D cp0;  
 		cp0.x= 100;
		cp0.y= 400;  
		ptosControl.push_back(cp0);
 	
 	 Vertice2D cp1;  	
 		cp1.x= 200;
		cp1.y= 100;
		ptosControl.push_back(cp1);

	 Vertice2D cp2;  
 		cp2.x= 600;
		cp2.y= 100;
		ptosControl.push_back(cp2);

	 Vertice2D cp3;   
 		cp3.x= 700;
		cp3.y= 400;
		ptosControl.push_back(cp3);

	glColor3f(1.0,0,0);    
	glBegin(GL_POINTS);
		glVertex2i(cp0.x, cp0.y);
		glVertex2i(cp1.x, cp1.y);
		glVertex2i(cp2.x, cp2.y);
    glVertex2i(cp3.x, cp3.y);
	glEnd();

	glColor3f(0,0,1.0);
	glBegin(GL_LINE_STRIP);
		curva.BezierCubica(ptosControl);
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
