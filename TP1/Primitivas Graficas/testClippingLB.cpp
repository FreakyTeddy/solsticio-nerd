
#include "GL/glut.h"
#include <stdlib.h>

#include <iostream>
#include "Poligono.h"
#include "Linea/linea.h"
#include "liang-barsky.h"

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

	glClear(GL_COLOR_BUFFER_BIT);
  	glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();

   Poligono cuadrado;
	cuadrado.agregarVertice(20.0,40.0);
	cuadrado.agregarVertice(20.0,60.0);
	cuadrado.agregarVertice(40.0,60.0);
	cuadrado.agregarVertice(40.0,40.0);
	
	Poligono* triangulo = new Poligono();;
	// triangulo->agregarVertice(35.0,54.0);
	// triangulo->agregarVertice(32,45);
	// triangulo->agregarVertice(16,57);


	// triangulo->agregarVertice(70.0,54.0);
	// triangulo->agregarVertice(32,45);
	// triangulo->agregarVertice(16,57);

	// triangulo->agregarVertice(35.0,54.0);
	// triangulo->agregarVertice(3,45);
	// triangulo->agregarVertice(16,57);

	triangulo->agregarVertice(35.0,54.0);
	triangulo->agregarVertice(3,45);
	triangulo->agregarVertice(15,90);


        MatrizTrans2D matTrans;
   Vertice fixed;  /* escala del celular */
        fixed.x = 80;
        fixed.y = 80;

matTrans.scale2D(1,1, fixed);
        matTrans.translate2D(0,0);

   
   ClippingPoligonos clippeador;
   Poligono* clip = new Poligono();
   clip = clippeador.clippingLB(60,40,20,40,triangulo);
   // clip = clippeador.clippingLB(10,200,20,200,clip,1);
   // clip = clippeador.clippingLB(10,200,20,200,clip,2);  
   glBegin(GL_POINTS);

   glColor3f(0,1.0,0);
   cuadrado.dibujarContorno(true, matTrans);
   glColor3f(1.0,1.0,0);
   triangulo->dibujarContorno(true, matTrans);

   glColor3f(1.0,0,0);
   clip->dibujarContorno(true, matTrans);



	glEnd();

	///
 	glutSwapBuffers();
	///
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (ANCHO, ALTO);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (caption);
  init ();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 0;
}
