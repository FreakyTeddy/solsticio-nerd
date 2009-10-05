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
  
  /*Variables*/
  Linea linea;
  Relleno relleno;
	
	dcPt* ptos[4];
	
	for(int i=0; i<4; i++)
		ptos[i]= new dcPt();
	
	ptos[0]->x= 300;
	ptos[0]->y= 20;

	ptos[1]->x= 300;
	ptos[1]->y= 500;	

	ptos[2]->x= 500;
	ptos[2]->y= 20;  

	ptos[3]->x= 500;
	ptos[3]->y= 500;  

   
	glBegin(GL_POINTS);
	
	
	//Dibujo rectangulo
	//linea.lineaDDA(300, 20, 500, 20);
	//linea.lineaDDA(300, 20, 300, 500);
	//linea.lineaDDA(300, 500, 500, 500);
	//linea.lineaDDA(500, 20, 500, 500);

	//Pinto rectangulo
	//relleno.scanLine(4, ptos[0]);
	
	/*PRUEBA Bresenham*/
	//PENDIENTES POSITIVAS
	glColor3f(0,1.0,1.0);
	//Pendiente 0,74
	linea.lineaBresenham(400,300,5,5);
	//Pendiente 1
	linea.lineaBresenham(5,5,400,400);
	//Pendiente 1,65
	linea.lineaBresenham(100,5,400,500);

	//PENDIENTES NEGATIVAS
	glColor3f(0.0,0.0,1.0);
	//Pendiente -0,84
	linea.lineaBresenham(400,5,50,300);
	//Pendiente -1
	linea.lineaBresenham(4,500,500,4);
	//Pendiente -1,32
	linea.lineaBresenham(400,5,100,400);
	
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
