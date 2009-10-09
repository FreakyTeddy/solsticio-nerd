/*
 * testcel.cpp
 *
 *  Created on: 07/10/2009
 *      Author: luuu
 */


/////
///// Sistemas Gráficos - 6671
///// 2do cuatrimestre 2009
/////
//#include "GL/glut.h"
//#include <stdlib.h>
//
//#include <iostream>
//
//#include "Celular.h"
//
//
//
//#define ANCHO	800
//#define ALTO	600
//
//char caption[]="Solsticio Nerd";
//
//Celular celular;
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
//	glClearColor(1.0,1.0,1.0,0.0);
//}
//
//void display(void)
//{
//
//	glClear(GL_COLOR_BUFFER_BIT);
//   	glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//
//    glBegin(GL_POINTS);
//
//   celular.dibujar();
//
//
//
//
//
//	glEnd();
//
//	///
//  	glutSwapBuffers();
//	///
//}
//
//
//
//
///* x, y coordenadas mouse cuando se presiona key
//*/
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{		//toma solo las minusculas
//	case 0x30:
//		std::cout<<" 0 "<<std::endl;
//		break;
//	case 0x31:
//		std::cout<<" 1 "<<std::endl;
//		break;
//	case 0x32:
//		std::cout<<" 2 "<<std::endl;
//		break;
//	case 0x33:
//		std::cout<<" 3 "<<std::endl;
//		break;
//	case 0x34:
//		std::cout<<" 4 "<<std::endl;
//		break;
//	case 0x35:
//		std::cout<<" 5 "<<std::endl;
//		break;
//	case 0x36:
//		std::cout<<" 6 "<<std::endl;
//		break;
//	case 0x37:
//		std::cout<<" 7 "<<std::endl;
//		break;
//	case 0x38:
//		std::cout<<" 8 "<<std::endl;
//		break;
//	case 0x39:
//		std::cout<<" 9 "<<std::endl;
//		break;
//	case 0x2B:
//		std::cout<<".....+......"<<std::endl;
//		break;
//	case 0x2D:
//		std::cout<<".....-......"<<std::endl;
//		break;
//	case 0x62:
//		std::cout<<".....b......"<<std::endl;
//		break;
//	case 0x63:
//		std::cout<<".....c......"<<std::endl;//limpia la pantalla del cel
//		break;
//	case 0x64:
//		std::cout<<"......d......"<<std::endl;
//		break;
//	case 0x1b:
//		exit (1);
//		break;
//	}
//}
//
//void specialKeys(int key,int x, int y) {
//
//	switch(key) {
//	case GLUT_KEY_LEFT:
//		std::cout<<"........izquierda........"<<std::endl;
//		break;
//	case GLUT_KEY_RIGHT:
//		std::cout<<"..........derecha.........."<<std::endl;
//		break;
//	case GLUT_KEY_UP:
//		std::cout<<".........arriba........"<<std::endl;
//		break;
//	case GLUT_KEY_DOWN:
//		std::cout<<"......abajo........"<<std::endl;
//		break;
//	}
//}
//
//int main(int argc, char** argv)
//{
//   glutInit(&argc, argv);
//   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
//   
//   glutInitWindowSize (ANCHO, ALTO);
//   glutInitWindowPosition (100, 100);
//   glutCreateWindow (caption);
//   init ();
//   glutKeyboardFunc(keyboard);
//   glutSpecialFunc(specialKeys);
//   
//   glutDisplayFunc(display);
//   glutReshapeFunc(reshape);
//   glutMainLoop();
//
//   return 0;
//}

