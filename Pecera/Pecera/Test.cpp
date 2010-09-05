#include <GL/glut.h>
#include <stdlib.h>
#include "Primitivas/Curva/Curva.h"
#include "Camara/Camara.h"
#include "Primitivas/Superficie/SuperficieBarrido.h"
#include "Primitivas/Superficie/SuperficieRevolucion.h"
#include <iostream>
#include <vector>



GLfloat vertex_buf[] = {0,0,0, 0,1,0, 0,1,1, 0,0,1};
GLfloat color_buf[] =   {1,0,0, 0,1,0, 0,0,1, 1,1,1};
GLubyte index_buf[] = {0,1,2, 2,3,0};

//GLfloat mat_diffuse[] = { 1.0, 0.50, 0.0,0.70 };
//GLfloat mat_specular[] = { 1.0, 0.90, 0.0,0.7 };//material de la esfera
//GLfloat mat_shininess[] = { 100.0 };


std::vector<Vertice> vertices;  //flan
Superficie *sb;

// Variables que controlan la ubicación de la cámara en la Escena 3D
#define EYE_Z 5.0
float eye[3] = {0.0, 20.0, EYE_Z};	//camara
float at[3]  = { 0.0,  0.0, EYE_Z};	//centro
float up[3]  = { 0.0,  0.0, 1.0};	//vector normal
int tras[3] = {0 , 0 ,0 };

// Variables asociadas a única fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};

// Variable asociada al movimiento de rotación de la esfera alrededor del eje Z
float rotate_cam_x = 0;
float rotate_cam_y = 0;
float zoom = 1;
int xprev = 0; //posicion anterior del mouse
int yprev = 0;
int zprev = 0;
float altura_curva = 6.0;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool zoomOn = false;
bool luz = true;
bool blend = false;

// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)

// Tamaño de la ventana
GLfloat window_size[2];

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
	glLoadIdentity();
	gluLookAt (eye[0]/zoom, eye[1]/zoom, eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

}

void init(void) {
  dl_handle = glGenLists(3);

  //glClearColor (0.02, 0.02, 0.04, 0.0);
  glClearColor (0, 0.05, 0.10, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_ambient);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  //glEnable(GL_BLEND);

 // glEnable(GL_FOG);
    {
       GLfloat fogColor[4] = {0.05, 0.05, 0.1, 1.0};//{0.05, 0.25, 0.55, 1.0};

       glFogi (GL_FOG_MODE, GL_EXP2);
       glFogfv (GL_FOG_COLOR, fogColor);
       glFogf (GL_FOG_DENSITY, 0.03);
       glHint (GL_FOG_HINT, GL_DONT_CARE);
       glFogf (GL_FOG_START, 1.0);
       glFogf (GL_FOG_END, 5.0);
    }


  // Generación de las Display Lists
  glNewList(DL_AXIS, GL_COMPILE);
  DrawAxis();
  glEndList();
  glNewList(DL_GRID, GL_COMPILE);
  DrawXYGrid();
  glEndList();

  std::vector<Vertice> v;
  Vertice q;
  q.x = 1;
  q.y = 1;
  q.z = 0;
  v.push_back(q);
  v.push_back(q);
  v.push_back(q);

  q.x = 1.5;
  q.y = 1.5;
  q.z = 3.8;
  v.push_back(q);

  q.x = 3.5;
  q.y = 2.0;
  q.z = 0.5;
  v.push_back(q);

  q.x = 4.0;
  q.y = 3.0;
  q.z = 1.0;
  v.push_back(q);
  v.push_back(q);
  v.push_back(q);

  Curva curva;
  curva.Bspline(v, vertices);
  q.x = 0;
  q.y = 0;
  q.z = 0;
  std::vector<Vertice> trasl;
  trasl.push_back(q);
  trasl.push_back(q);
  trasl.push_back(q);
  q.x = 2.5;
  q.y = -1.5;
  q.z = 0;
  trasl.push_back(q);
  trasl.push_back(q);
  trasl.push_back(q);
  curva.Bspline(trasl, v);

  q.set(0,0,0);
  Vertice x(0,0,1);
  sb = new SuperficieRevolucion(vertices, 180.0, q, x);
  //sb = new SuperficieBarrido(vertices, v);

//  std::vector<Vertice> alga;
//  q.x= 2;  q.y=2;   q.z=0;
//  alga.push_back(q);
//  q.x=3;
//  alga.push_back(q);
//
//  trasl.clear();
//  q.x=0; q.y=0; q.z=0;
//  trasl.push_back(q);
//  trasl.push_back(q);
//  trasl.push_back(q);
//
//  q.x=-1; q.y=0; q.z=1;
//  trasl.push_back(q);
//
//  q.x=1; q.y=0; q.z=3;
//  trasl.push_back(q);
//
//  q.x=-1; q.y=0; q.z=5;
//  trasl.push_back(q);
//  trasl.push_back(q);
//  trasl.push_back(q);
//
//  curva.Bspline(trasl, v);
//
//  trasl.clear();
//   q.x=1; q.y=1; q.z=1;
//   trasl.push_back(q);
//   trasl.push_back(q);
//   trasl.push_back(q);
//
//   q.x=0.5; q.y=0.5; q.z=1;
//   trasl.push_back(q);
//
//   q.x=1; q.y=1.5; q.z=1;
//   trasl.push_back(q);
//
//   q.x=0.01; q.y=0.01; q.z=1;
//   trasl.push_back(q);
//   trasl.push_back(q);
//   trasl.push_back(q);
//
//
//  std::vector<Vertice> def;
//
//  curva.Bspline(trasl, def);
//   sb2 = new SuperficieBarrido(alga, v, def);



}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Set3DEnv();

	///////////////////////////////////////////////////
	// Escena 3D
/* estrellitas */
//	glDisable(GL_BLEND);
//		glDisable(GL_LIGHTING);
//	for (int i=0; i<4; i+=2){
//	for (int j=0; j<4; j+=2){
//		glPushMatrix();
//		glTranslatef(1-i,0,1-j);
//		glBegin(GL_POLYGON);
//			glColor3f(0.8,0,0);
//			glVertex3f(0,0,1);
//			glVertex3f(-0.5,0,0);
//			glVertex3f(0,0,0.26);
//			glVertex3f(0.5,0,0);
//		glEnd();
//		glBegin(GL_POLYGON);
//		glVertex3f(0,0,0.26);
//		glVertex3f(0.5,0,0.7);
//		glVertex3f(-0.5,0,0.7);
//		glEnd();
//		glPopMatrix();
//	}}
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //tambien roto la luz
	glPushMatrix();
	glTranslatef(tras[0],tras[1], tras[2]);
	glRotatef(rotate_cam_x, 0,0,1.0);	//en lugar de rotar la cam roto el modelo
	glRotatef(rotate_cam_y, 1.0,0,0);


	if (!luz)
		glDisable(GL_LIGHT0);

	if (view_axis)
		 glCallList(DL_AXIS);
	if (view_grid)
		 glCallList(DL_GRID);
    ///////////////////////////// dibujar ////////////////////////

 //EL FLAN
//	glEnableClientState (GL_VERTEX_ARRAY);
//	glVertexPointer(3,GL_FLOAT,0,&(vertices.front()));
//	glColor3f(0.5,0.0,0.9);
//	for (int i=0; i<100; i++) {
//
//    	glPushMatrix();
//    	glRotatef(i*3.6, 0,0,1);
//    	glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
//		glPopMatrix();
//    }
//	glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
//	glDisableClientState (GL_VERTEX_ARRAY);

//glDisable(GL_LIGHTING);
	//CINTA
//
//	//glRotatef(i*3.6, 0,0,1);
//	std::vector<Vertice>::iterator it0 = vertices.begin();
//	std::vector<Vertice>::iterator it1 = vertices.begin();
//	std::vector<Vertice>::iterator it;
//	int tam = vertices.size();
//	glBegin(GL_TRIANGLE_STRIP);
//	std::cout<<"pasos bspline: "<<tam<<std::endl;
//	for (it=vertices.begin();it!=vertices.end();it++)
//		std::cout<<it->x<<" "<<it->y<<" "<<it->z<<" "<<std::endl;
//	for(int pos=0 ; pos <  tam-1 ; pos++) {
//		glColor3f((float)pos/tam,0,(float)pos/tam);
//		glVertex3f(it0->x,it0->y,it0->z);
//		glVertex3f(it1->x + 2,it1->y,it1->z);
//		it1++;
//		glVertex3f(it1->x + 2,it1->y,it1->z);
//
//		glColor3f((float)pos/tam,1,(float)pos/tam);
//		glVertex3f(it0->x,it0->y,it0->z);
//		glVertex3f(it1->x + 2,it1->y,it1->z);
//		it0++;
//		glVertex3f(it0->x,it0->y,it0->z);
//	}
//	glEnd();


//CINTA CON CLASE B-]
//glDisable(GL_LIGHTING);
		sb->dibujar();
//
//
//	//cuadradito colorinche
//	glDisable(GL_LIGHTING);
//	glEnableClientState (GL_VERTEX_ARRAY);
//	glEnableClientState (GL_COLOR_ARRAY);
//	glVertexPointer(3,GL_FLOAT,0,vertex_buf);
//	glColorPointer(3,GL_FLOAT, 0, color_buf);
//
//    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE, index_buf);
//    glTranslatef(2,2,2);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, index_buf);
//        glTranslatef(2,2,2);
//            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, index_buf);
//            glTranslatef(2,2,2);
//                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, index_buf);
//    glDisableClientState (GL_VERTEX_ARRAY);
//    glDisableClientState (GL_COLOR_ARRAY);


	//ESFERA del DRAGON

//		glEnable(GL_LIGHTING);
//		glEnable(GL_BLEND);
//		    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //material
//		    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//		    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//		    glBlendFunc (GL_SRC_ALPHA, GL_ONE);       //transparencia
//		    glutSolidSphere (4.0, 40, 26);


    /////////////////////////// fin dibujar =P /////////////////////

	if (!luz)
		glEnable(GL_LIGHT0);
	glPopMatrix();

	//
	///////////////////////////////////////////////////
	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	window_size[0]  = w;
	window_size[1] = h;
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
	case 'l':
	case 'L':
		luz=!luz;
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

