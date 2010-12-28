#include <GL/glut.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

#include "Objetos/Burbuja.h"
#include "Objetos/Alga.h"
#include "Primitivas/Superficie/Superficie.h"


Alga alguita;
std::list<Burbuja*> burbujas;

// Variables que controlan la ubicación de la cámara en la Escena 3D
float eye[3] = {0.0, 20.0, 5.0};	//camara
float at[3]  = { 0.0,  0.0, 5.0};	//centro
float up[3]  = { 0.0,  0.0, 1.0};	//vector normal
int tras[3] = {0 , 0 ,0 }; //traslacion de la camara

// Variable asociada al movimiento de la camara
float rotate_cam_x = 0;
float rotate_cam_y = 0;
float zoom = 1;
int xprev = 0; //posicion anterior del mouse
int yprev = 0;
int zprev = 0;

// Variables asociadas la fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 48.0f};
float light_ambient[4] = {0.9f, 0.95f, 1.0f, 1.0f};


//float altura_curva = 6.0;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool zoomOn = false;
bool luz = true;
bool animando = false;


// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_CUADRADO (dl_handle+2)

// Tamaño de la ventana
GLfloat window_size[2];


void animarBurbujas(int n) {

	if (!burbujas.empty()) {
		animando = true;
		glutTimerFunc(100,animarBurbujas,0);	//llamo al timer para generar la animacion
		std::list<Burbuja*>::iterator it;
		for (it = burbujas.begin(); it != burbujas.end(); it++)
			(*it)->animar();
		glutPostRedisplay();
	}
	else
		animando = false;
}


void OnIdle (void)
{}

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
  glColor3f(0.15, 0.1, 0.1);
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

/* Seteo del ambiente 3D
 * Debe llamarse cada vez que se cambia el tamaño de ventana */
void Set3DEnv() {
	glViewport (0, 0, (GLsizei) window_size[0], (GLsizei) window_size[1]);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) window_size[0]/(GLfloat) window_size[1], 0.10, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (eye[0]/zoom, eye[1]/zoom, eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

}

void init(void) {

  dl_handle = glGenLists(3);

  glClearColor (0, 0.05, 0.10, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_ambient);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  glEnable(GL_FOG); //niebla
    {
       GLfloat fogColor[4] = {0.0, 0.05, 0.1, 0.0};

       glFogi (GL_FOG_MODE, GL_EXP2);
       glFogfv (GL_FOG_COLOR, fogColor);
       glFogf (GL_FOG_DENSITY, 0.035);
       glHint (GL_FOG_HINT, GL_DONT_CARE);
       glFogf (GL_FOG_START, 1.0);
       glFogf (GL_FOG_END, 5.0);
    }

  /* seteo del ambiente */
  Set3DEnv();

  // Generación de las Display Lists
  glNewList(DL_AXIS, GL_COMPILE);
  DrawAxis();
  glEndList();

  glNewList(DL_GRID, GL_COMPILE);
  DrawXYGrid();
  glEndList();

  glNewList(DL_CUADRADO, GL_COMPILE);
  glDisable(GL_LIGHTING);
  glBegin(GL_QUADS);
  glColor3f(0.8,0.5,0.9);
  glVertex3f(1,0,0);
  glVertex3f(1,1,0);
  glVertex3f(0,1,0);
  glVertex3f(0,0,0);
  glEnd();
  glEnable(GL_LIGHTING);
  glEndList();

}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////
	// Escena 3D

	glPushMatrix();
	//Camara
	glTranslatef(tras[0],tras[1], tras[2]);
	glRotatef(rotate_cam_y, 0.0,1.0,0.0);
	glRotatef(rotate_cam_x, 0.0,0.0,1.0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //tambien roto la luz

	if (view_axis)
		 glCallList(DL_AXIS);
	if (view_grid)
		 glCallList(DL_GRID);

	/* cuadrados display lists */
//	for (int i=0; i<100; i++) {
//		glPushMatrix();
//			glTranslatef(i,i,0);
//			glCallList(DL_CUADRADO);
//		glPopMatrix();
//	}
	/* testeo de esfera*/
//    if (!blend)
//    		glDisable(GL_BLEND);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //material
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE);	//transparencia
//    glutSolidSphere (1.0, 20, 16);
    //glutWireSphere(0.9, 20, 16);
//    if (!blend)
//		glEnable(GL_BLEND);

	/* animacion burbujas */
	if (animando) {
		Vertice* v;
		std::list<Burbuja*>::iterator it;
		for (it = burbujas.begin(); it != burbujas.end(); it++) {
			v = (*it)->getPos();
			if (v != NULL) {
				glPushMatrix();
					glTranslatef(v->x,v->y,v->z);
					(*it)->dibujar();
				glPopMatrix();
			}
			else {
				Burbuja* b = *it;
				burbujas.erase(it); //y lo saco de la lista de burbujas
				it--;
				delete b; //si termino su trayectoria lo elimino
			}
		}
	}

	/* ALGAAAAAAAAAAA */
	alguita.dibujar();
	glPopMatrix();

	//
	///////////////////////////////////////////////////
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
		tras[2] -= 1.0;
		glutPostRedisplay();
		break;
	case 0x2D:  // '-'
		tras[2] += 1.0;
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		if (!animando) {
			animarBurbujas(0);
			glutPostRedisplay();
		}
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
       tras[0]=0;tras[1]=0;tras[2]=0;
       rotate_cam_x=0; rotate_cam_y=0;
       zoom=1;
       glutPostRedisplay();
       break;
    case 'r':
 	case 'R':
 		Superficie::nextMode();
 		glutPostRedisplay();
        break;
     default:
      break;
  }
}

void specialKeys(int key,int x, int y) {

	switch(key) {
	case GLUT_KEY_LEFT:
		tras[0] -= 1.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		tras[0] += 1.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		tras[1] += 1.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		tras[1] -= 1.0;
		glutPostRedisplay();
		break;
	}
}


void mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(!mouseDown) {
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
		rotate_cam_x += (x-xprev);
		rotate_cam_y += (y-yprev)*0.1;
		xprev = x;
		yprev = y;
		glutPostRedisplay();
	}
	if (zoomOn) {
		if (y > zprev)
			zoom += 0.001*(zprev-y);
		else if(y < zprev)
			zoom -=0.001*(y-zprev);
		zprev = y;
		glutPostRedisplay();
	}

}
//
//void ImageLoad(std::string route[]){
//	Imagen im;
//	SDL_Surface* imagen = NULL;
//	int numColores = 0;
//	int formatoTextura = 0;
//
//	glEnable(GL_TEXTURE_2D);
//	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
//	glGenTextures(N,textures);
//
//	for(int i = 0; i < N; i++){
//		imagen = im.cargarImagen(route[i]);
//		if(!imagen) std::cerr << "Error al cargar la imagen " << std::endl;
//
//		//De acuerdo al formato de la imagen, chequeo y seteo
//		// el formato de textura correspondiente.
//		//en caso de no ser una imagen "true color" muestra el error
//		// por cerr informando que probablemente la imagen no se
//		//observe correctamente
//		numColores = imagen->format->BytesPerPixel;
//        if (numColores == 4){     //Posee transparencias
//
//                if (imagen->format->Rmask == 0x000000ff)
//                        formatoTextura = GL_RGBA;
//                else
//                        formatoTextura = GL_BGRA;
//        } else if (numColores == 3){     // no posee transparencias
//
//                if (imagen->format->Rmask == 0x000000ff)
//                        formatoTextura = GL_RGB;
//                else
//                        formatoTextura = GL_BGR;
//        } else {
//                std::cerr << "Advertencia!!!! la imagen que intenta cargar no es true color "<< std::endl;
//                std::cerr << " Es probable que no se visualice correctamente esta imagen. " << std::endl;
//        }
//
//		glBindTexture(GL_TEXTURE_2D,textures[i]);
//
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
//
//		gluBuild2DMipmaps(GL_TEXTURE_2D,4,imagen->w,
//			  imagen->h,formatoTextura,
//			  GL_UNSIGNED_BYTE,imagen->pixels);
//	}
//}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP Final - Sistemas Graficos");
  glutFullScreen();

//  //cargo las rutas de las imagenes
//  std::string route[N];
//  //cargo las rutas de las imagenes por defecto
//  loadDefaulImage(&route[0]);
//  //cargo las texturas a partir de las rutas
//  ImageLoad(route);
  srand((unsigned)time(0));
  Burbuja* bubble1 = new Burbuja(1,2,3);
  Burbuja* bubble2 = new Burbuja(3,2,1);
  burbujas.push_back(bubble1);
  burbujas.push_back(bubble2);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
//  glutIdleFunc(OnIdle);

   std::cout<<"Controles: "<<std::endl;
   std::cout<<"A - \t ejes"<<std::endl;
   std::cout<<"G - \t grilla"<<std::endl;
   std::cout<<"C - \t reset camara"<<std::endl;
   std::cout<<"R - \t render de escena"<<std::endl;
   std::cout<<"flechas \t traslacion xy"<<std::endl;
   std::cout<<"'+' '-' \t traslacion z"<<std::endl;
   std::cout<<"boton izq \t rotacion camara"<<std::endl;
   std::cout<<"boton der \t zoom camara"<<std::endl;


  glutMainLoop();

  return 0;
}
