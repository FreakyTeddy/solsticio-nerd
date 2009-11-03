// Test Basico De Cargar Imagenes
// Simplemente prueba la funcionalidad de la libreria SDL

//#include <iostream>
//#include "Imagen.h"
//
//int main(int argc,char** argv){
//
//	Imagen image;
//	SDL_Surface* retorno = NULL;
//	retorno = image.cargarImagen("Imagenes/ubuntu-logo.png");
//	std::cout << "retorno: " << retorno << std::endl;
//	
//	return 0;
//}

/*
 * 
 * Para convertir de SDL_Surface* a GLvoid*
 * 
 * Si SDL_Surface* imagen;
 * 
 * entonces:
 * 
 * imagen->pixels es GLvoid* :)
 * 
glTextImage2D(GLenum objetivo, Glint nivel, GLint componentes,
 GLsizei ancho, GLsizei alto, GLint borde, GLenum formato,
  GLenum tipo, const GLvoid *pixels);

Donde:
parámetro
	
valores
objetivo 	GL_TEXTURE_2D (para texturas bidimensionales)
nivel 	0,1,2.. es el nivel de detalle de la textura. Si sólo hay una textura nivel=0
componentes 	Número de componentes de color. Color indexado=1, RGB=3, RGBA=4
ancho 	Ancho de la textura: potencia de 2
alto 	Alto de la textura: potencia de 2
borde 	Anchura del borde= 0,1, ó 2.
formato 	formato de la información de píxel. Pueden ser: GL_COLOR_INDEX, GL_RGB, GL_RGBA, etc.
tipo 	Tipo de datos de cada píxel: GL_UNSIGNED_BYTE, GL_INT, etc.
pixels 	Puntero al array donde se almacenan los valores de la textura.


typedef struct SDL_Surface {
   2     Uint32 flags;                           // Read-only 
   3     SDL_PixelFormat *format;                // Read-only 
   4     int w, h;                               // Read-only 
   5     Uint16 pitch;                           // Read-only 
   6     void *pixels;                           // Read-write
   7     SDL_Rect clip_rect;                     // Read-only 
   8     int refcount;                           // Read-mostly 
   9 
  10   // This structure also contains private fields not shown here 
  11 } SDL_Surface;




*/


//
// Sistemas Gráficos - 6671
// 1er cuatrimestre 2009
//
#include "GL/glut.h" 
#include <stdlib.h>
#include <iostream>
#include "../Primitivas Graficas/Curva/Curva.h"
#include "../Controlador/Controlador.h"
#include "Imagen.h"

#define ANCHO	800
#define ALTO	600

Curva curva;
Controlador controlador(&curva);

char caption[]= "-- Texturas --";


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
	
	Imagen image;
	SDL_Surface* im;
	
	im=image.cargarImagen("ubuntu-logo.bmp");
	if(!im) std::cerr << "Error al cargar la imagen" << std::endl;
	std::cout << "numero de colores: " << im->format->BytesPerPixel << std::endl;

	GLuint texture;
	
/* Standard OpenGL texture creation code */
	 glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,im->w,
			  im->h,GL_BGRA_EXT,
			  GL_UNSIGNED_BYTE,im->pixels);
	
	//Free surface after using it
 	glBegin(GL_QUADS);
	//Top-left vertex (corner)
	glTexCoord2i( 0, 0 );
	glVertex3f( 100, 100, 0.0f );
	
	//Bottom-left vertex (corner)
	glTexCoord2i( 1, 0 );
	glVertex3f( 228, 100, 0 );
	
	//Bottom-right vertex (corner)
	glTexCoord2i( 1, 1 );
	glVertex3f( 228, 228, 0 );
	
	//Top-right vertex (corner)
	glTexCoord2i( 0, 1 );
	glVertex3f( 100, 228, 0 );
	
	glEnd();
  	glutSwapBuffers();
	SDL_FreeSurface(im);
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
		case 0x61:
		std::cout << "A: aumenta el paso bspline" << std::endl;
		controlador.aumentarPasoBspline();
		glutPostRedisplay();
		break;
	case 0x73:
		std::cout << "S: disminuye el paso bspline" << std::endl;
		controlador.disminuirPasoBspline();
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
if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
}
 
// SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
 
// SDL_Surface* screen = SDL_SetVideoMode( 800, 600, 16, SDL_OPENGL); // *changed* 
   init();
   glutKeyboardFunc(keyboard);
    glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMainLoop();
   
   return 0;
}
