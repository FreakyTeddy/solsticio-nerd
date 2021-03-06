#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "Primitivas Graficas/Curva/Curva.h"
#include "Imagenes/Imagen.h"
#include "Trayectoria/Trayectoria.h"

// Variables que controlan la ubicación de la cámara en la Escena 3D
#define EYE_Z 5.0
float eye[3] = {15.0, 15.0, EYE_Z};	//camara
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
float altura_curva = 6.0;

// Variables de control
bool view_grid = true;
bool view_axis = true;
bool edit_panel = true;
bool view_curves = true;	//indica si se ven las curvas de control
bool view_trayectories = false;
bool mouseDown = false; 	//indica si se apreta el boton izquierdo del mouse
bool zoomOn = false;
bool modo_curva = false; 	//indica si esta en modo curva o en modo grilla
bool animando = false; 		//indica si se esta realizando la animacion
bool nuevaCurvaEditor = false;
bool moviendoImagenes = false;          //indica si se estan moviendo las imagenes
bool camaraArriba = false;
bool imagenesArriba = false;          //indica si se estan moviendo las imagenes

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

//Cantidad de Imagenes a mostrar en la grilla
#define N 16

//Factor de ampliacion de 2D a 3D
#define FACTOR 50

// Variables globales
Curva curva;
std::list<Vertice> pControl;	//puntos de control dibujados con el mouse
std::list<Vertice> pTangente;	//tangente a puntos de control dibujados con el mouse
std::list<Vertice> pNormal;		//normal a puntos de control dibujados con el mouse
std::list<Vertice> curva_editada;
std::map<int,Vertice> distancias;
std::list<Vertice> curva_cam;	//curva que describe la camara
GLuint textures[N]; //arreglo de texturas de imagenes

float longBezier;
Trayectoria trayectoria;
std::vector<Trayectoria> trayectorias(N, trayectoria);
std::list<Vertice> camino;
std::vector< std::list<Vertice> > caminos(N, camino);
Vertice normales[16];
float alfas[16];
unsigned int sizeBezier= 0;
int angulo = 0;
std::list<Vertice> spline_normales[16];


Vertice posicionFinalCentroImagen(int numFoto) {

  Vertice last;
  float espacioXQuad= (float) ((longBezier*FACTOR)/N);
  //harcodeo ancho imagen 2
  float espacioSobrante= espacioXQuad-2;
  float espacioInicial= (float) espacioSobrante/2;
  int distancia= (espacioXQuad*numFoto) + espacioInicial + 1;
  last = (distancias.lower_bound(distancia)->second);

  //aca lo que quiero hacer es obtener el vector normal a la curva en la posicion final
  std::list<Vertice>::iterator it = pNormal.begin();
  bool encontrado = false;
  while (!encontrado && it !=pNormal.end() ) {
	  if (last == (*it)) {
		  encontrado = true;
		  normales[numFoto] = *it;
		  it++; //n
		  normales[numFoto].x = it->x;
		  normales[numFoto].y = it->y;
		  normales[numFoto].z = it->z;

		  //creo la curva bspline de normales
		  std::list<Vertice> ctrolNormal;
		  Vertice v;
		  v.x = 0;
		  v.y = 1;
		  v.z = 0;
		  ctrolNormal.push_back(v);
		  ctrolNormal.push_back(v);
		  ctrolNormal.push_back(v);
		  v.x = normales[numFoto].x + normales[numFoto].y;
		  v.y = normales[numFoto].x + normales[numFoto].y;
		  ctrolNormal.push_back(v);
		  v.x = normales[numFoto].x;
		  v.y = normales[numFoto].y;
		  ctrolNormal.push_back(v);
		  ctrolNormal.push_back(v);
		  ctrolNormal.push_back(v);
		  spline_normales[numFoto].clear();
		  curva.Bspline(ctrolNormal, spline_normales[numFoto]);
	  }
	  else
		  it++;
	  it++;
  }

  return last;
}


void OnIdle (void)
{}

void generarMatriz(int k, Vertice vCentro) {

  Vertice vInicial= trayectorias[k].ptosTrayectoria.front();
  trayectorias[k].ptosTrayectoria.pop_front();
  Vertice vFinal= trayectorias[k].ptosTrayectoria.front();

  float dx= vFinal.x-vInicial.x;
  float dy= vFinal.y-vInicial.y;

  //Muevo al proximo vertice de la trayectoria
  glTranslatef(vInicial.x+dx, vInicial.y+dy, vInicial.z);
  //Traslado centro de la imagen
  glTranslatef(-vCentro.x, -vCentro.y, 0);

  //Si estamos en los dos puntos finales de las trayectorias
  //guardo el anteultimo vertice nuevamente para que las
  //imagenes permanezcan arriba
  if(trayectorias[k].ptosTrayectoria.size() == 1) {
    trayectorias[k].ptosTrayectoria.push_front(vInicial);
    if(moviendoImagenes && k==N-1) {
      imagenesArriba= true;
      moviendoImagenes= false;
    }
  }
}

void generarTrayectoria(int numFoto, Vertice vInicial) {

  std::list<Vertice> ptosControl;
  ptosControl.clear();

  //Creo las trayectorias desde la grilla a la curva final
  int factorX= 1;
  int factorY= 1;
  int modificarX= 0;
  int modificarY= 0;

  if(numFoto >= 0 && numFoto <= 3)
    factorY= -5;
  else if(numFoto >= 4 && numFoto <= 7)
    factorX= -5;
  else if(numFoto >= 8 && numFoto <= 11)
    factorX= 5;
  else if(numFoto >= 12 && numFoto <= 15)
    factorY= 5;

  switch(numFoto) {
    case 0:
    case 12:
      modificarX= -20;
      break;
    case 1:
    case 13:
      modificarX= -5;
      break;
    case 2:
    case 14:
      modificarX= 5;
      break;
    case 3:
    case 15:
      modificarX= 20;
      break;
    case 4:
    case 8:
      modificarY= -20;
      break;
    case 5:
    case 9:
      modificarY= -5;
      break;
    case 6:
    case 10:
      modificarY= 5;
      break;
    case 7:
    case 11:
      modificarY= 20;
      break;
  }

  //interpolo el punto inicial
  ptosControl.push_back(vInicial);
  ptosControl.push_back(vInicial);
  ptosControl.push_back(vInicial);

  Vertice v;
  v.x= 5 * factorX + modificarX;
  v.y= 5 * factorY + modificarY;
  v.z= altura_curva*0.333;
  ptosControl.push_back(v);

  v.z= altura_curva*0.666;
  ptosControl.push_back(v);

  v= posicionFinalCentroImagen(numFoto);
  v.x= v.x * FACTOR;
  v.y= v.y * FACTOR;
  v.z= altura_curva;
  //interpolo el punto final
  ptosControl.push_back(v);
  ptosControl.push_back(v);
  ptosControl.push_back(v);

  trayectorias[numFoto].ptosTrayectoria.clear();
  caminos[numFoto].clear();
  curva.Bspline(ptosControl, trayectorias[numFoto].ptosTrayectoria);
  caminos[numFoto]= trayectorias[numFoto].ptosTrayectoria;
}

//mueve la camara al siguiente lugar especificado en curva_cam y redibuja
void moverCam(int n) {
  if (!curva_cam.empty()) {
    Vertice v = curva_cam.front();
    curva_cam.pop_front();
    eye[0] = v.x;
    eye[1] = v.y;
    eye[2] = v.z;
    at[2] = v.z - EYE_Z;
    glutPostRedisplay();
    glutTimerFunc(50,moverCam,0);	//llamo al timer para que actualice la pos de la cam
    if (angulo < 180 && camaraArriba)
        angulo++;
  }
  else {
    animando = false;
  }

}

void animar() {
	//este metodo usa la curva bspline para hacer la animacion de la camara
	//para la transicion entre la grilla y la curva
	animando = true;
	angulo = 0;
	std::list<Vertice> puntos, tg, norm;
	Vertice v;
	curva_cam.clear();

	//punto inicial... lo agrego 3 veces para que interpole
	v.x = eye[0];
	v.y = eye[1];
	v.z = eye[2];
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);

	if (modo_curva) {
		//si esta en modo curva paso a modo grilla
		//bajo la camara
		v.x = eye[0]*1.5;
		v.y = eye[1]*1.5;
		v.z = eye[2] - (altura_curva*0.333);
		puntos.push_back(v);

		v.z = eye[2] - (altura_curva*0.666);
		puntos.push_back(v);

		v.x = eye[0];
		v.y = eye[1];
		v.z = eye[2] - altura_curva;
	}
	else {
		//si esta en modo grilla paso a modo curva

		v.x = eye[0]*1.5;
		v.y = eye[1]*1.5;
		v.z = eye[2] + (altura_curva*0.333);
		puntos.push_back(v);

		v.z = eye[2] + (altura_curva*0.666);
		puntos.push_back(v);

		v.x = eye[0];
		v.y = eye[1];
		v.z = eye[2] + altura_curva;
	}
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);

	curva.Bspline(puntos,curva_cam);
	moverCam(0);
	modo_curva = !modo_curva;
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

void DrawAxis2DTopView() {
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

void SetPanelTopEnv() {
  glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluOrtho2D(0.5, -0.5, 0.5, -0.5);
  //gluOrtho2D(-0.5, 0.5, -0.5, 0.5); original
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
  glNewList(DL_AXIS2D_TOP, GL_COMPILE);
  DrawAxis2DTopView();
  glEndList();
}



void cargarGrillaImagenes(){
    Vertice vInicial;
    int k = 0;
	int j = 0;
	for(int i = 0; i < sqrt(N); i++){
		for(j = 0; j < sqrt(N); j++){
			glBindTexture(GL_TEXTURE_2D,textures[k]);
                        vInicial.x= 2 * j + j + 1;
                        vInicial.y= 2 * i + i + 1;
                        vInicial.z= 0;

                        //Aplico transformaciones si se esta animando
			if((moviendoImagenes || imagenesArriba) && modo_curva) {
                          glPushMatrix();
             	          generarMatriz(k, vInicial);
			}
			glPushMatrix();

			glTranslatef( 2 *j + j+1, 2 * i + i+1,0);

			if (!spline_normales[k].empty() && camaraArriba) {
				//calculo del angulo de rotacion en z respecto del 0,1,0
				Vertice n = spline_normales[k].front();
				spline_normales[k].pop_front();
				alfas[k] = n.x / n.y;
				alfas[k] = (-atan(alfas[k]));
				alfas[k] = (alfas[k]*180.0) / 3.1416;
				if (n.y < 0)
					alfas[k] = 180 + alfas[k]; //correccion por cuadrante
			}

			//rota la imagen respecto del eje z
			glRotatef(alfas[k],0, 0,1.0);
			//orienta la curva normal al eje y
			glRotatef(angulo/2,1.0, 0,0);
			glRotatef(-angulo,0, 0,1);

			glTranslatef( -(2 *j + j)-1, -(2 * i + i)-1,0);

			glBegin(GL_QUADS);
				//Top-left vertex (corner)
				glTexCoord2i( 0, 0 );
				glVertex3f( 2 *j + j, 2 * i + i, 0 );

				
				//Bottom-left vertex (corner)
				glTexCoord2i( 1, 0 );
				glVertex3f( 2*j + j + 2, 2 * i + i, 0 );


				//Bottom-right vertex (corner)
				glTexCoord2i( 1, 1 );
				glVertex3f( 2 * j + j + 2, 2 * i + i + 2, 0 );


				//Top-right vertex (corner)
				glTexCoord2i( 0, 1 );
				glVertex3f( 2 * j + j, 2 * i + i + 2, 0 );
			glEnd();
			glPopMatrix();

			//Aplico transformaciones si se esta animando
			if((moviendoImagenes || imagenesArriba) && modo_curva)
			  glPopMatrix();

			//Si hay una nueva curva final recalculo las trayectorias
			if(nuevaCurvaEditor)
			  generarTrayectoria(k, vInicial);

			k++;
		}
		if(j!= 4)k++;
	}
	//Si se descomenta va mucho mas rapido que la camara
	//Comentado las imagenes se mueven con la camara
	//glutPostRedisplay();
} 

void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		//Solo si se modifica los puntos de control del editor
		//Vuelvo a calcular bezier
		if(sizeBezier != pControl.size()) {
		  sizeBezier= pControl.size();
		  //limpio los buffers
		  curva_editada.clear();
		  pTangente.clear();
		  pNormal.clear();
		  distancias.clear();
                  curva.BezierCubica(pControl, curva_editada, pNormal, distancias, FACTOR);
                  longBezier= curva.getLongitudBezier();
                  if (!modo_curva)
                	  nuevaCurvaEditor= true;
		}

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
		//dibujo la curva editada para las imagenes
		glBegin(GL_LINE_STRIP);
			glColor3f(0,1.0,1.0);
			for (it = curva_editada.begin(); it != curva_editada.end(); it++)
				glVertex3f((it->x * FACTOR),(it->y * FACTOR), altura_curva);
		glEnd();

		//dibujo la trayectoria de las imagenes
		if(view_trayectories) {
                  glColor3f(1.0,1.0,1.0);
                   for(unsigned int k=0; k<N; k++) {
                     glBegin(GL_LINE_STRIP);
                    for(it= caminos[k].begin(); it != caminos[k].end(); it++)
                      glVertex3f(it->x, it->y, it->z);
                    glEnd();
                  }
 		}
		glEnable(GL_LIGHTING);
	}
			//dibujar imagenes
		glDisable(GL_LIGHTING);
		glColor3f(1.0,1.0,1.0);
		//cargo la grilla de imagenes
		cargarGrillaImagenes();

		glEnable(GL_LIGHTING);

	//Para que los cambios sean cargados solo una vez
	nuevaCurvaEditor= false;

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
      if(!animando) {
        //Si hay curva en el editor,
        //y hay por lo menos 4 ptos de control
        if(pControl.size() > 3) {
          view_trayectories= true;
          moviendoImagenes= !moviendoImagenes;
          camaraArriba= !camaraArriba;
          nuevaCurvaEditor = true;
          for (int i=0; i<16; i++)
          	alfas[i] = 0;
          angulo = 0; //°°°°°°°
          animar();
	}
      }
      break;
    case 'c':
      //No se puede borrar mientras se este animando
      if(!animando) {
        pControl.clear();
        curva_editada.clear();
        view_trayectories= false;
        for (int i=0; i<16; i++)
        	alfas[i] = 0;
        glutPostRedisplay();
        //Las imagenes vuelven a la grilla
        if(imagenesArriba)
          imagenesArriba= false;
        //La camara vuelve abajo
        if(camaraArriba) {
          animar();
          camaraArriba= false;
        }
      }
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

			v.x = (v.x - 0.5) * -1;
			v.y = (v.y - 0.5) * -1;
			v.z = altura_curva;

			if(!mouseDown)
			     xprev=x;

			mouseDown = true;

			if ( x > x0 && x < x1) {
				if ( y < y0 && y > y1) {

					mouseDown = false; //lo deshabilito para que no rote
					if ( !animando){
						pControl.push_back(v);	//agrego el vertice normalizado
						glutPostRedisplay();
					}
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

void ImageLoad(std::string route[]){
	Imagen im;
	SDL_Surface* imagen = NULL;
	int numColores = 0;
	int formatoTextura = 0;
	
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glGenTextures(N,textures);
	
	for(int i = 0; i < N; i++){
		imagen = im.cargarImagen(route[i]);
		if(!imagen) std::cerr << "Error al cargar la imagen " << std::endl;
		
		//De acuerdo al formato de la imagen, chequeo y seteo 
		// el formato de textura correspondiente.
		//en caso de no ser una imagen "true color" muestra el error
		// por cerr informando que probablemente la imagen no se
		//observe correctamente
		numColores = imagen->format->BytesPerPixel;
        if (numColores == 4){     //Posee transparencias
       
                if (imagen->format->Rmask == 0x000000ff)
                        formatoTextura = GL_RGBA;
                else
                        formatoTextura = GL_BGRA;
        } else if (numColores == 3){     // no posee transparencias
        
                if (imagen->format->Rmask == 0x000000ff)
                        formatoTextura = GL_RGB;
                else
                        formatoTextura = GL_BGR;
        } else {
                std::cerr << "Advertencia!!!! la imagen que intenta cargar no es true color "<< std::endl;
                std::cerr << " Es probable que no se visualice correctamente esta imagen. " << std::endl;
        }
		
		glBindTexture(GL_TEXTURE_2D,textures[i]);
	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	
		gluBuild2DMipmaps(GL_TEXTURE_2D,4,imagen->w,
			  imagen->h,formatoTextura,
			  GL_UNSIGNED_BYTE,imagen->pixels);
	}
}

void loadDefaulImage(std::string* route){

  route[0]= "Imagenes/Castles_in_the_Sky.bmp";
  route[1]= "Imagenes/Command_by_GravihK.bmp";
  route[2]= "Imagenes/Fire_materia_in_action_by_DMSLilwolf.bmp";
  route[3]= "Imagenes/Magic_by_GravihK.bmp";
  route[4]= "Imagenes/Space Art Wallpapers 00.bmp";
  route[5]= "Imagenes/Support_by_GravihK.bmp";
  route[6]= "Imagenes/berrywalls-sample-space-curve-8900-wallpaper.bmp";
  route[7]= "Imagenes/celestial_sight04.bmp";
  route[8]= "Imagenes/celestial_sight21.bmp";
  route[9]= "Imagenes/celestial_sight29.bmp";
  route[10]= "Imagenes/dream.bmp";
  route[11]= "Imagenes/eclair.bmp";
  route[12]= "Imagenes/lua.bmp";
  route[13]= "Imagenes/premium-wallpaper-10.bmp";
  route[14]= "Imagenes/sunset.bmp";
  //route[15] = "Imagenes/celestial_sight24.bmp";
  route[15]= "Imagenes/ubuntu-logo.bmp";
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("TP2 - Sistemas Graficos");
  glutFullScreen();

  //cargo las rutas de las imagenes
  std::string route[N];
  //cargo las rutas de las imagenes por defecto
  loadDefaulImage(&route[0]);
  //cargo las texturas a partir de las rutas
  ImageLoad(route);

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
