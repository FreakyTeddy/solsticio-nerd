#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "Primitivas Graficas/Curva/Curva.h"
#include "Controlador/Controlador.h"

// Variables que controlan la ubicación de la cámara en la Escena 3D
float eye[3] = {15.0, 15.0, 5.0};	//camara
float at[3]  = { 0.0,  0.0, 0.0};	//centro
float up[3]  = { 0.0,  0.0, 1.0};	//vector normal

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

// Variable asociada al movimiento de rotación de la esfera alrededor del eje Z
float rotate_cam = 0;
float zoom = 1;
int xprev = 0; //posicion anterior del mouse
int yprev = 0;
float altura_curva = 5.0;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = true;
bool view_curves = true;	//indica si se ven las curvas de control
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool zoomOn = false;
bool modo_curva = false; 	//indica si esta en modo curva o en modo grilla


// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

// Tamaño de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

int TOP_VIEW_POSX = ((int)((float)W_WIDTH*0.60f)) -10;
int TOP_VIEW_W = ((int)((float)W_WIDTH*0.40f));
int TOP_VIEW_POSY = ((int)((float)W_HEIGHT*0.60f)) -10;
int TOP_VIEW_H = ((int)((float)W_HEIGHT*0.40f));

// Variables globales
Curva curva;
std::list<Vertice> pControl;	//puntos de control dibujados con el mouse
std::list<Vertice> pTangente;	//puntos de control dibujados con el mouse
std::list<Vertice> pNormal;	//puntos de control dibujados con el mouse
std::list<Vertice> curva_editada;
std::list<Vertice> curva_cam;	//curva que describe la camara
Controlador controlador(&curva);



void OnIdle (void)
{}

void animarCam() {
	//este metodo usa la curva bspline para hacer la animacion de la camara
	//para la transicion entre la grilla y la curva
	if (modo_curva) {
		//si esta en modo curva paso a modo grilla
		//bajo la camara
		at[2] -= altura_curva;
		eye[2] -=altura_curva;//esta transicion se hace con la curva
		view_grid = true;
	}
	else {
		//si esta en modo grilla paso a modo curva
		view_grid = false;
		at[2] += altura_curva;
		eye[2] +=altura_curva;//esta transicion se hace con la curva
	}
	modo_curva = !modo_curva;
	glutPostRedisplay();
}

void DrawAxis()
{
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

void DrawAxis2DTopView()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		// X
		glColor3f(0.0, 0.5, 1.0);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.1, 0.1, 0.1);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();

	glEnable(GL_LIGHTING);
}


void DrawXYGrid()
{
	int i;
	glDisable(GL_LIGHTING);
	glColor3f(0.15, 0.1, 0.1);
	glBegin(GL_LINES);
	for(i=-20; i<21; i++)
	{
		glVertex3f(i, -20.0, 0.0);
		glVertex3f(i,  20.0, 0.0);
		glVertex3f(-20.0, i, 0.0);
		glVertex3f( 20.0, i, 0.0);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}

void Set3DEnv()
{
	glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}

void SetPanelTopEnv()
{
	glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
}


void init(void)
{
	dl_handle = glGenLists(3);

	glClearColor (0.02, 0.02, 0.04, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	// Generación de las Display Lists
	glNewList(DL_AXIS, GL_COMPILE);
		DrawAxis();
	glEndList();
	glNewList(DL_GRID, GL_COMPILE);
		DrawXYGrid();
	glEndList();
	glNewList(DL_AXIS2D_TOP, GL_COMPILE);
		DrawAxis2DTopView();
	glEndList();
}



void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///////////////////////////////////////////////////
	// Escena 3D
	Set3DEnv();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (eye[0]/zoom, eye[1]/zoom, eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

	glPushMatrix();
	glRotatef(rotate_cam, 0,0,1.0);	//en lugar de rotar la cam roto el modelo

	if (view_axis)
		 glCallList(DL_AXIS);

	if (view_grid)
		 glCallList(DL_GRID);

	if (view_curves) {

		//dibujar las curvas

		glDisable(GL_LIGHTING);

		std::list<Vertice>::iterator it;
		glBegin(GL_LINE_STRIP);
			glColor3f(0,1.0,1.0);
			for (it = curva_editada.begin(); it != curva_editada.end(); it++)
				glVertex3f(it->x * 20, it->y * 20, altura_curva); //TODO calcular este factor de escala
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();
	//
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// Panel 2D para la vista superior
	if (edit_panel)
	{
		SetPanelTopEnv();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);

		glDisable(GL_LIGHTING);

		std::list<Vertice>::iterator it;

		//dibujo los puntos de control
		glBegin(GL_POINTS);
			glColor3f(0,1.0,1.0);
			for (it = pControl.begin(); it != pControl.end(); it++)
				glVertex3f(it->x, it->y, 0.0);
		glEnd();

		//dibujo el poligono de control
		if (view_curves) {
			glBegin(GL_LINE_STRIP);
				glColor3f(0.5,0,0.7);
				for (it = pControl.begin(); it != pControl.end(); it++)
					glVertex3f(it->x, it->y, 0.0);
			glEnd();
		}


		curva_editada.clear();

		//TODO: aca esta bezier
		//falta ver tema normales
		curva.BezierCubica(pControl, curva_editada, pTangente, pNormal);

		glBegin(GL_LINE_STRIP);
			glColor3f(1.0,1.0,0);
			for (it = curva_editada.begin(); it != curva_editada.end(); it++)
				glVertex3f(it->x, it->y, 0.0);
		glEnd();

		glEnable(GL_LIGHTING);

		glCallList(DL_AXIS2D_TOP); //dibuja el cuadrado del viewport2D

	}
	//
	///////////////////////////////////////////////////

	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	W_WIDTH  = w;
	W_HEIGHT = h;

	TOP_VIEW_POSX = ((int)((float)W_WIDTH*0.60f)) -10;
	TOP_VIEW_W = ((int)((float)W_WIDTH*0.40f));
	TOP_VIEW_POSY = ((int)((float)W_HEIGHT*0.60f)) -10;
	TOP_VIEW_H = ((int)((float)W_HEIGHT*0.40f));
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
		case 0x1b:
         exit(0);
    	break;
	  case 'g':
		  view_grid = !view_grid;
		  glutPostRedisplay();
			break;
	  case 'a':
		  view_axis = !view_axis;
		  glutPostRedisplay();
			break;
	  case 'e':
		  edit_panel = !edit_panel;
		  glutPostRedisplay();
			break;
	  case 't':
		  view_curves = !view_curves;
		  glutPostRedisplay();
		  break;
	  case 'b':
		  animarCam();
		  break;
	  case 'c':
		  pControl.clear();
		  curva_editada.clear();
		  glutPostRedisplay();
		  break;
    default:
    	break;
   }
}

void mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		int x0 = TOP_VIEW_POSX; 			//limite izq
		int x1 = x0 + TOP_VIEW_W;			//limite der
		int y0 = W_HEIGHT - TOP_VIEW_POSY;	//limite abajo
		int y1 = y0-TOP_VIEW_H;				//limite arriba

		if (edit_panel) { 	//si el edit panel esta habilitado capturo el x e y para dibujar el punto de control

			Vertice v;

			v.x = (float)(x - x0) / (float) (x1-x0) ;
			v.y = (float)(y0 - y) / (float) (y0-y1);
			v.x -=0.5;
			v.y -=0.5;
			v.z = altura_curva;

			if(!mouseDown)
			     xprev=x;

			mouseDown = true;

			if ( x > x0 && x < x1) {
				if ( y < y0 && y > y1) {

					mouseDown = false; //lo deshabilito para que no rote
					pControl.push_back(v);	//agrego el vertice normalizado
					glutPostRedisplay();
				}
			}
		}
		else{
		     if(!mouseDown)
			  xprev=x;
		     mouseDown = true;
		}
		
	}
	else
		mouseDown = false;

	if(!zoomOn)
	     yprev=y;
	(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) ? zoomOn = true : zoomOn = false;
}

void mouseMotion(int x, int y) {
	if (mouseDown) {
		if (x > xprev){
		     rotate_cam += 0.3*(x-xprev);
			if(rotate_cam > 360.0) rotate_cam = 0.0;
		}
		else {
			rotate_cam -=0.3*(xprev-x);
			if(rotate_cam < -360.0) rotate_cam = 0.0;
		}
		xprev = x;
		glutPostRedisplay();
	}
	if (zoomOn) {
		if (y > yprev)
			zoom += 0.001*(yprev-y);
		else if(y < yprev)
			zoom -=0.001*(y-yprev);
		yprev = y;
		glutPostRedisplay();
	}
	
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1024, 768);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("TP2 - Sistemas Graficos");
   glutFullScreen();
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(mouseMotion);
   glutIdleFunc(OnIdle);
   glutMainLoop();
   return 0;
}
