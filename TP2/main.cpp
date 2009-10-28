//
// Sistemas Gráficos - 6671
// 1er cuatrimestre 2009
//
#include "GL/glut.h" 
#include <stdlib.h>
#include <iostream>
#include "Primitivas Graficas/Curva/Curva.h"
#include "Controlador/Controlador.h"

#define ANCHO	800
#define ALTO	600

Curva curva;
Controlador controlador(&curva);

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
	//
	glClear(GL_COLOR_BUFFER_BIT);
   	glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
	//
    
//	/*PRUEBA CURVA BSPLINE*/ 
//	/*--------------------*/ 
//  std::list<Vertice2D> ptosControl;
//
//  Vertice2D cp0;  
// 		cp0.x= 100;
//		cp0.y= 400;  
//		ptosControl.push_back(cp0);
// 	
// 	 Vertice2D cp1;  	
// 		cp1.x= 150;
//		cp1.y= 200;
//		ptosControl.push_back(cp1);
//
//	 Vertice2D cp2;  
// 		cp2.x= 200;
//		cp2.y= 200;
//		ptosControl.push_back(cp2);
//
//	 Vertice2D cp3;   
// 		cp3.x= 250;
//		cp3.y= 400;
//		ptosControl.push_back(cp3);
//
//	Vertice2D cp4;
//		cp4.x= 350;
//		cp4.y= 200;
//		ptosControl.push_back(cp4);
//
//	Vertice2D cp5;
//		cp5.x= 400;
//		cp5.y= 200;
//		ptosControl.push_back(cp5);
//		ptosControl.push_back(cp5);
//		ptosControl.push_back(cp5);
//
//	glColor3f(0,0,1.0);    
//	glBegin(GL_POINTS);
//		glVertex2i(cp0.x, cp0.y);
//		glVertex2i(cp1.x, cp1.y);
//		glVertex2i(cp2.x, cp2.y);
//		glVertex2i(cp3.x, cp3.y);
//		glVertex2i(cp4.x, cp4.y);
//		glVertex2i(cp5.x, cp5.y);
//	glEnd();
//
//	glBegin(GL_LINE_STRIP);
//		curva.Bspline(ptosControl);
//	glEnd();

	/*-------------------*/ 
	/*PRUEBA CURVA BEZIER*/ 
	/*-------------------*/ 
  std::list<Vertice2D> ptosControlBezier;
	std::list<Vertice2D> ptosCurva;
	std::list<Vertice2D> ptosTangente;
	std::list<Vertice2D> ptosNormal;
	
  Vertice2D cp00;  
 		cp00.x= 50;
		cp00.y= 400;  
		ptosControlBezier.push_back(cp00);
 	
 	 Vertice2D cp01;  	
 		cp01.x= 100;
		cp01.y= 200;
		ptosControlBezier.push_back(cp01);

	 Vertice2D cp02;  
 		cp02.x= 200;
		cp02.y= 200;
		ptosControlBezier.push_back(cp02);

	 Vertice2D cp03;   
 		cp03.x= 250;
		cp03.y= 400;
		ptosControlBezier.push_back(cp03);

	 Vertice2D cp04;   
 		cp04.x= 400;
		cp04.y= 200;
		ptosControlBezier.push_back(cp04);

	 Vertice2D cp05;   
 		cp05.x= 500;
		cp05.y= 200;
		ptosControlBezier.push_back(cp05);

	Vertice2D cp06;   
 		cp06.x= 600;
		cp06.y= 400;
		ptosControlBezier.push_back(cp06);

	glColor3f(1.0,0,0);    
	glBegin(GL_POINTS);
		glVertex2i(cp00.x, cp00.y);
		glVertex2i(cp01.x, cp01.y);
		glVertex2i(cp02.x, cp02.y);
		glVertex2i(cp03.x, cp03.y);
		glVertex2i(cp04.x, cp04.y);
		glVertex2i(cp05.x, cp05.y);
		glVertex2i(cp06.x, cp06.y);		
	glEnd();

	curva.BezierCubica(ptosControlBezier, ptosCurva, ptosTangente, ptosNormal);

	std::list<Vertice2D>::iterator it;
	glColor3f(0,1.0,0);    
	glBegin(GL_LINE_STRIP);
	
		for(it= ptosCurva.begin(); it != ptosCurva.end(); it++) { 
			glVertex2f(it->x, it->y);
		}
		
	glEnd();
	
	glColor3f(0,0,1.0);    
	glBegin(GL_LINE_STRIP);
	
		for(it= ptosTangente.begin(); it != ptosTangente.end(); it++) { 
			glVertex2f(it->x, it->y);
		}
		
	glEnd();

	glColor3f(1.0,1.0,1.0);    
	glBegin(GL_LINE_STRIP);
	
		for(it= ptosNormal.begin(); it != ptosNormal.end(); it++) { 
			glVertex2f(it->x, it->y);
		}
		
	glEnd();
	
	/*-------------------*/ 
	
	
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
	case 0x71:
		std::cout << "Q: aumenta el paso bezier" << std::endl;
		controlador.aumentarPasoBezier();
		glutPostRedisplay();
		break;
	case 0x77:
		std::cout << "w: disminuye el paso bezier" << std::endl;
		controlador.disminuirPasoBezier();
		glutPostRedisplay();
		break;
	case 0x1b:
		exit(1);
		break;
	}
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(ANCHO, ALTO); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow(caption);
   init();
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   
   return 0;
}
