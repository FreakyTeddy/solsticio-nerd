#include <GL/glut.h>
#include <stdlib.h>
#include "Primitivas/Curva/Curva.h"
#include "Primitivas/Superficie/SuperficieBarrido.h"
#include "Primitivas/Superficie/SuperficieRevolucion.h"
#include "Escena/ControladorEscena.h"
#include <iostream>
#include <vector>

/* Variables Globales
 * */
ControladorEscena* escena;

/************************************/


/* LUZ */

float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_specular[4] = {1.0, 1.0, 1.0, 1.0};
float light_position[3] = {10.0f, 10.0f, 100.0f};
float light_ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float linterna_pos[3];
float linterna_dir[3];



/* Mouse */
int xprev = 0; //posicion anterior del mouse
int yprev = 0;
int zprev = 0;

// Variables de control
bool view_grid = false;
bool view_axis = true;
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool niebla = true;
bool linterna = LUZ_INICIAL;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)

// Tamaño de la ventana
GLfloat window_size[2];

void posicionarLinterna() {
	linterna_pos[0] = escena->getCamara()->getEye().x;
	linterna_pos[1] = escena->getCamara()->getEye().y;
	linterna_pos[2] = escena->getCamara()->getEye().z;
	linterna_dir[0] = escena->getCamara()->getAt().x;
	linterna_dir[1] = escena->getCamara()->getAt().y;
	linterna_dir[2] = escena->getCamara()->getAt().z;
}

void DrawAxis() {
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    // X
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(15.0, 0.0, 0.0);
    // Y
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 15.0, 0.0);
    // Z
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 15.0);
  glEnd();
  glEnable(GL_LIGHTING);
}

void DrawXYGrid() {
  int i;
  glDisable(GL_LIGHTING);
  glColor3f(0.1, 0.1, 0.15);
  glBegin(GL_LINES);
    for(i=-20; i<21; i++) {
      glVertex3f(i, -20.0, 0.0);
      glVertex3f(i,  20.0, 0.0);
      glVertex3f(-20.0, i, 0.0);
      glVertex3f( 20.0, i, 0.0);
    }
  glEnd();
  glEnable(GL_LIGHTING);
}

void Set3DEnv() {
	glViewport (0, 0, (GLsizei) window_size[0], (GLsizei) window_size[1]);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) window_size[0]/(GLfloat) window_size[1], 0.30, 363.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void) {
  dl_handle = glGenLists(2);

  glClearColor (0, 0.05, 0.10, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  /* iluminacion */
  Set3DEnv();
  	  //luz ambiental
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	//linterna
	posicionarLinterna();
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, linterna_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, linterna_dir);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.005);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.010);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.05);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100);

	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);



  // Generación de las Display Lists
  glNewList(DL_AXIS, GL_COMPILE);
  DrawAxis();
  glEndList();
  glNewList(DL_GRID, GL_COMPILE);
  DrawXYGrid();
  glEndList();

  glDisable(GL_COLOR_MATERIAL);
}

void salir() {

	/* destruir todos los objetos */
	glDeleteLists(dl_handle,2);
	delete escena;
	std::cout<<"Fin =]"<<std::endl;
	std::cout.flush();
	exit(0);
}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
//	glPushMatrix();
	escena->getCamara()->lookAt();

	if (linterna){
			posicionarLinterna();
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, linterna_dir);
			glLightfv(GL_LIGHT1, GL_POSITION, linterna_pos);
	}
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);

	if (view_axis)
		 glCallList(DL_AXIS);
	if (view_grid)
		 glCallList(DL_GRID);
	if (niebla)
		glEnable(GL_FOG);

	///////////////////////////// dibujar ////////////////////////


		escena->generarEscena();



    /////////////////////////// fin dibujar =P /////////////////////
	if (niebla)
		glDisable(GL_FOG);
//	glPopMatrix();

	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	window_size[0]  = w;
	window_size[1] = h;
	Set3DEnv();
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {
    case 0x1b: //ESC
       	exit(0);
      break;
	case 0x2B:  // '+'
		escena->getCamara()->trasladar_u(1);
		glutPostRedisplay();
		break;
	case 0x2D:  // '-'
		escena->getCamara()->trasladar_u(-1);
		glutPostRedisplay();
		break;
    case 'g':
    case 'G':
      view_grid = !view_grid;
      glutPostRedisplay();
      break;
    case 'a':
    case 'A':
      view_axis = !view_axis;
      glutPostRedisplay();
      break;
    case 'f':
    case 'F':
      niebla = !niebla;
      glutPostRedisplay();
      break;
    case 'l':
    case 'L':
      linterna = !linterna;
      if (linterna) {
    	  glDisable(GL_LIGHT0);
    	  glEnable(GL_LIGHT1);
      }else{
    	  glDisable(GL_LIGHT1);
    	  glEnable(GL_LIGHT0);
      }
      glutPostRedisplay();
      break;
    case 'c':
    case 'C':
      escena->getCamara()->reset();
      glutPostRedisplay();
      break;
    case 'p':
	case 'P':
		 escena->nextAnimationMode();
        break;
    case 'r':
	case 'R':
		 escena->nextRenderMode();
		 glutPostRedisplay();
        break;
	case 's':
	case 'S':
		 escena->nextFrame();
		 break;
    case 't':
	case 'T':
		 escena->nextTrackDisplayMode();
		 glutPostRedisplay();
        break;
    default:
      break;
  }
}

void specialKeys(int key,int x, int y) {

	switch(key) {
	case GLUT_KEY_LEFT:
		escena->getCamara()->trasladar_s(-1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		escena->getCamara()->trasladar_s(1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		escena->getCamara()->trasladar_f(1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		escena->getCamara()->trasladar_f(-1);
		glutPostRedisplay();
		break;
	}
}


void mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(!mouseDown){
			xprev=x;
			yprev=y;
		}
		mouseDown = true;
	}
	else
		mouseDown = false;
}

void mouseMotion(int x, int y) {
	if (mouseDown) {
		escena->getCamara()->rotar_h((xprev-x)*0.3);
		escena->getCamara()->rotar_v((yprev-y)*0.2);
		xprev = x;
		yprev = y;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP Final - Sistemas Graficos");
//  glutSetIconTitle("iconsmall.png");
//  glutFullScreen();
  glutWarpPointer(window_size[0] / 2, window_size[1] / 2);
  glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);



  escena = new ControladorEscena();

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  atexit(salir);
  srand(time(0));

  /* Informacion */
  std::cout<<"Controles: "<<std::endl;
  std::cout<<"A - \t ejes"<<std::endl;
  std::cout<<"F - \t niebla"<<std::endl;
  std::cout<<"G - \t grilla"<<std::endl;
  std::cout<<"C - \t reset camara"<<std::endl;
  std::cout<<"L - \t linterna / luz ambiental"<<std::endl;
  std::cout<<"P - \t iniciar/detener animacion"<<std::endl;
  std::cout<<"R - \t render de escena"<<std::endl;
  std::cout<<"S - \t avanzar 1 frame la animacion"<<std::endl;
  std::cout<<"T - \t trayectorias"<<std::endl;
  std::cout<<"flechas \t traslacion horizontal"<<std::endl;
  std::cout<<"'+' '-' \t traslacion vertical"<<std::endl;
  std::cout<<"boton izq \t rotacion camara"<<std::endl;
  std::cout.flush();



  glutMainLoop();
  return 0;
}

