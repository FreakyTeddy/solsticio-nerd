//#include <iostream>
//#include "liang-barsky.h"
//
//
////int main (int argc, char** argv){
////	ClippingPoligonos clipper;
////	float x0 = 30.0;
////	float y0 = 30.0;
////	float x1 = 65.0;
////	float y1 = 0.0;
////	int Vtop = 40;
////	int Vbottom = 5;
////	int Vleft = 5;
////	int Vright = 70;
////
////	std::cout << "Linea original: x0 = " << x0 << "x1 = " << x1 << "y0 = " << y0 << "y1 = " << y1 << std::endl;
////	std::cout << "Viewport: Vleft = " << Vleft << "Vright = " << Vright << "Vtop = " << Vtop << "Vbottom = " << Vbottom << std::endl;
////
////	clipper.clippingLB(Vtop,Vbottom,Vleft,Vright,x0,x1,y0,y1);
////
////	std::cout << "Linea clippeada: x0 = " << x0 << "x1 = " << x1 << "y0 = " << y0 << "y1 = " << y1 << std::endl;
////
////	return 0;
////}
////
//
//#include "GL/glut.h"
//#include <stdlib.h>
//
//#include <iostream> //TODO sacar
//
//#include "Poligono.h"
//#include "Linea/linea.h"
//#include "liang-barsky.h"
//
//#define ANCHO	800
//#define ALTO	600
//
//char caption[]="Solsticio Nerd";
//
//void reshape(int w, int h)
//{
//   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);
//}
//
//void init(void)
//{
//}
////
////
////void display(void)
////{
////
////	glClear(GL_COLOR_BUFFER_BIT);
////   	glMatrixMode(GL_MODELVIEW);
////        glLoadIdentity();
////
////    Poligono cuadrado;
////	cuadrado.agregarVertice(20.0,40.0);
////	cuadrado.agregarVertice(20.0,60.0);
////	cuadrado.agregarVertice(40.0,60.0);
////	cuadrado.agregarVertice(40.0,40.0);
////	
////	Poligono* triangulo = new Poligono();;
////	triangulo->agregarVertice(35.0,5.0);
////	triangulo->agregarVertice(5.0,60.0);
////	triangulo->agregarVertice(75.0,60.0);
////    
////    ClippingPoligonos clippeador;
////    Poligono* clip = new Poligono();
////    clip = clippeador.clippingLB(40,60,20,40,triangulo,0);
//////    clip = clippeador.clippingLB(10,200,20,200,clip,1);
//////    clip = clippeador.clippingLB(10,200,20,200,clip,2);  
////    glBegin(GL_POINTS);
////
////    cuadrado.dibujarContorno(true);
////
////	clip->dibujarContorno(true);
////
////
////
////	glEnd();
////
////	///
////  	glutSwapBuffers();
////	///
////}
////
////
////int main(int argc, char** argv)
////{
////   glutInit(&argc, argv);
////   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
////   glutInitWindowSize (ANCHO, ALTO);
////   glutInitWindowPosition (100, 100);
////   glutCreateWindow (caption);
////   init ();
////   glutDisplayFunc(display);
////   glutReshapeFunc(reshape);
////   glutMainLoop();
////
////   return 0;
////}
