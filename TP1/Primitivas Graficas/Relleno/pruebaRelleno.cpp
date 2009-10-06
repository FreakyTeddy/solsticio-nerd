///
/// Sistemas Gráficos - 6671
/// 1er cuatrimestre 2009
///
#include "GL/glut.h" 
#include <stdlib.h>

#include "relleno.h"
#include "../Linea/linea.h"
#include "../Numero.h"

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
	
	//dcPt* ptos[3];
	dcPt* ptos;
	
	//for(int i=0; i<3; i++)
	//	ptos[i]= new dcPt();
		
	// OJO, los puntos tienen que estar contiguos en memoria!!!!!
	ptos = new dcPt[10];
	
	ptos[0].x= 50;
	ptos[0].y= 50;

	ptos[1].x= 350;
	ptos[1].y= 50;	

	ptos[2].x= 350;
	ptos[2].y= 350;  

	ptos[3].x= 300;
	ptos[3].y= 350;  

	ptos[4].x= 300;
	ptos[4].y= 100;  

 	ptos[5].x= 100;
	ptos[5].y= 100;  

 	ptos[6].x= 100;
	ptos[6].y= 150;  

 	ptos[7].x= 400;
	ptos[7].y= 0;  

 	ptos[8].x= 100;
	ptos[8].y= 350;
  
 	ptos[9].x= 150;
	ptos[9].y= 0;
  

	Numero n(6);
	glBegin(GL_POINTS);
	
	//Dibujo triangulo
	glColor3f(0,1.0,0);
	
	glVertex2i(300, 40);
	glVertex2i(100, 500);
	glVertex2i(500, 500);	

//	linea.lineaDDA(300, 40, 100, 500);
	linea.lineaBresenham(300, 40, 100, 500);
//	linea.lineaDDA(300, 40, 500, 500);
	linea.lineaBresenham(300, 40, 500, 500);
	
//	linea.lineaDDA(100, 500, 500, 500);
	linea.lineaBresenham(100, 500, 500, 500);

	//Pinto rectangulo
	glColor3f(1.0,0,0);
	
	relleno.scanLine(10, ptos);

	glColor3f(1.0,1.0,0);
	n.setRelleno(1);
	n.dibujar();
	
//	/*PRUEBA Bresenham*/
//	//PENDIENTES POSITIVAS
//	glColor3f(0,1.0,1.0);
//	//Pendiente 0,74
//	linea.lineaBresenham(400,300,5,5);
//	//Pendiente 1
//	linea.lineaBresenham(5,5,400,400);
//	//Pendiente 1,65
//	linea.lineaBresenham(100,5,400,500);
//
//	//PENDIENTES NEGATIVAS
//	glColor3f(0.0,0.0,1.0);
//	//Pendiente -0,84
//	linea.lineaBresenham(400,5,50,300);
//	//Pendiente -1
//	linea.lineaBresenham(4,500,500,4);
//	//Pendiente -1,32
//	linea.lineaBresenham(400,5,100,400);
	
	glEnd();
	
	///
  	glutSwapBuffers();
	///
	delete[] ptos;
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
