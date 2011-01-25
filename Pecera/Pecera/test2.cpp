#include <GL/glut.h>
#include <stdlib.h>
#include "Primitivas/Curva/Curva.h"
#include "Camara/Camara.h"
#include "Primitivas/Superficie/SuperficieBarrido.h"
#include "Primitivas/Superficie/SuperficieRevolucion.h"
#include "Escena/ControladorEscena.h"
#include <iostream>
#include <vector>


/* Variables Globales
 * */
Camara cam;	//camara
ControladorEscena* escena;

void suelo() {
	 glShadeModel (GL_FLAT);

	//falta material del suelo
	glFrontFace( GL_CCW );
	glCullFace( GL_FRONT );
	glEnable(GL_CULL_FACE);

	if (escena->getRenderMode() == GL_LINE)
		glPolygonMode( GL_BACK, GL_LINE);
	else
		glPolygonMode( GL_BACK, GL_FILL);
	for(int j=-50; j<50; j+=5) {
		glBegin(GL_QUAD_STRIP);
		for (int i=-50; i<51; i+=5){
			glVertex3f(i, j, 0.0);
			glVertex3f(i, j+5, 0.0);
		}
		glEnd();
	}

	glDisable( GL_CULL_FACE );
	glShadeModel (GL_SMOOTH);
}

/************************************/

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};

// Variable asociada al movimiento de rotación de la esfera alrededor del eje Z
int xprev = 0; //posicion anterior del mouse
int yprev = 0;
int zprev = 0;

// Variables de control
bool view_grid = false;
bool view_axis = true;
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool zoomOn = false;
bool luz = true;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

// Tamaño de la ventana
GLfloat window_size[2];

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
	gluPerspective(60.0, (GLfloat) window_size[0]/(GLfloat) window_size[1], 0.10, 100.0);
	glMatrixMode(GL_MODELVIEW);
	cam.lookAt();

}

void init(void) {
  dl_handle = glGenLists(3);

  glClearColor (0, 0.05, 0.10, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_ambient);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_FOG);
    {
       GLfloat fogColor[4] = {0, 0.05, 0.10, 1.0};

       glFogi (GL_FOG_MODE, GL_EXP2);
       glFogfv (GL_FOG_COLOR, fogColor);
       glFogf (GL_FOG_DENSITY, 0.03);
       glHint (GL_FOG_HINT, GL_DONT_CARE);
       glFogf (GL_FOG_START, 1.0);
       glFogf (GL_FOG_END, 5.0);
    }

    Set3DEnv();

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
	delete escena;
	std::cout<<"Gracias por usar Peces Pepe"<<std::endl;
	std::cout.flush();
	exit(0);
}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cam.lookAt();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glPushMatrix();


	if (view_axis)
		 glCallList(DL_AXIS);
	if (view_grid)
		 glCallList(DL_GRID);


    ///////////////////////////// dibujar ////////////////////////
	escena->generarEscena();
//	suelo();


    /////////////////////////// fin dibujar =P /////////////////////

	glPopMatrix();

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
		cam.trasladar_u(1);
		glutPostRedisplay();
		break;
	case 0x2D:  // '-'
		cam.trasladar_u(-1);
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
    case 'c':
    case 'C':
      cam.reset();
      glutPostRedisplay();
      break;
    case 'r':
	case 'R':
		 escena->nextMode();
		 glutPostRedisplay();
        break;
    default:
      break;
  }
}

void specialKeys(int key,int x, int y) {

	switch(key) {
	case GLUT_KEY_LEFT:
		cam.trasladar_s(1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		cam.trasladar_s(-1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		cam.trasladar_f(1);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		cam.trasladar_f(-1);
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

	if(!zoomOn)
	     zprev=y;
	(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) ? zoomOn = true : zoomOn = false;
}

void mouseMotion(int x, int y) {
	if (mouseDown) {
		cam.rotar_h((x-xprev)*(-0.5));
		cam.rotar_v((y-yprev)*0.1);
		xprev = x;
		yprev = y;
		glutPostRedisplay();
	}
	if (zoomOn) {
		if (y > zprev)
			cam.zoom_in(0.001*(zprev-y));
		else if(y < zprev)
			cam.zoom_in(-0.001*(y-zprev));
		zprev = y;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP Final - Sistemas Graficos");
  //glutFullScreen();

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  atexit(salir);

  /* Informacion */
  std::cout<<"Controles: "<<std::endl;
  std::cout<<"A - \t ejes"<<std::endl;
  std::cout<<"G - \t grilla"<<std::endl;
  std::cout<<"C - \t reset camara"<<std::endl;
  std::cout<<"R - \t render de escena"<<std::endl;
  std::cout<<"flechas \t traslacion horizontal"<<std::endl;
  std::cout<<"'+' '-' \t traslacion vertical"<<std::endl;
  std::cout<<"boton izq \t rotacion camara"<<std::endl;
  std::cout<<"boton der \t zoom camara"<<std::endl<<std::endl;
  std::cout.flush();

  /** TESTS **/
//
//  contenedorTex = ContenedorTexturas::getInstancia();
//  textura = contenedorTex->cargarImagen("arena.bmp");
  escena = new ControladorEscena();

  glutMainLoop();
  return 0;
}

