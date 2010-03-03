#include <GL/glut.h>
#include <stdlib.h>

// Variables que controlan la ubicación de la cámara en la Escena 3D
#define EYE_Z 5.0
float eye[3] = {0.0, 20.0, EYE_Z};	//camara
float at[3]  = { 0.0,  0.0, EYE_Z};	//centro
float up[3]  = { 0.0,  0.0, 1.0};	//vector normal
int tras[3] = {0 , 0 ,0 };

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

// Variable asociada al movimiento de rotación de la esfera alrededor del eje Z
float rotate_cam = 0;
float zoom = 1;
int xprev = 0; //posicion anterior del mouse
int yprev = 0;
float altura_curva = 6.0;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool zoomOn = false;

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

void Set3DEnv() {
  glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}

void init(void) {
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
	glTranslatef(tras[0],tras[1], tras[2]);
	glRotatef(rotate_cam, 0,0,1.0);	//en lugar de rotar la cam roto el modelo


	if (view_axis)
		 glCallList(DL_AXIS);
	if (view_grid)
		 glCallList(DL_GRID);

	glPopMatrix();
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

void keyboard (unsigned char key, int x, int y) {
  switch (key) {
    case 0x1b:
      exit(0);
      break;
	case 0x2B:  // '+'
		tras[2] += 1.0;
		glutPostRedisplay();
		break;
	case 0x2D:  // '-'
		tras[2] -= 1.0;
		glutPostRedisplay();
		break;
//    case 'g':
//      view_grid = !view_grid;
//      glutPostRedisplay();
//      break;
//    case 'a':
//      view_axis = !view_axis;
//      glutPostRedisplay();
//      break;
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
		if(!mouseDown)
			xprev=x;
		mouseDown = true;
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

  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
//  glutIdleFunc(OnIdle);
  glutMainLoop();

  return 0;
}
