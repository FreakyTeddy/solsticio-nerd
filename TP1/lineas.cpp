
#include "GL/glut.h"
#include "lineas.h"

void swap(int &n1, int &n2) {
	int aux = n1;
	n1 = n2;
	n2 = aux;
}

void lineaBresenham(int x0, int y0, int x1, int y1)
{
	//dibuja solo el punto.. tal vez no sea necesario
	if ((x0 == x1) && (y0 == y1)){
	    glBegin(GL_POINTS);
			glVertex2i(x0, y0);
		glEnd();
		 return;
	}

	if (x0>x1) {
		swap(x0,y0);
		swap(x1,y1);
	}
	int dx = x1-x0;
	int dy = y1-y0;
	int stepx = 1, stepy = 1;
	int x,y;

	int e, dosd, de;

	if( dy < 0 ) {
		dy *= -1;
		stepy = -1;
	}

	if( dx > dy ) {

	    dosd = 2 * dy;
	    de = 2 * (dy - dx);
	    e = dosd - dx;
	    y = y0;

	    glBegin(GL_POINTS);

	    for ( x = x0; x != x1; x += stepx ) {

	    	glVertex2i( x, y );

	    	if( e <= 0 ) {
	    		e += dosd;
	    	} else {
	    		y += stepy;
	    		e += de;
	    	}
	    }

		glEnd();

	} else { //lo mismo pero con y

	    de = 2 * (dx - dy);
	    dosd = 2 * dx;
	    e = dosd - dy;
	    x = x0;

	    glBegin(GL_POINTS);

	    for( y = y0; y != y1; y += stepy ) {

	        glVertex2i( x, y );

	        if( e <= 0 ) {
	        	e += dosd;
	        } else {
	        	x += stepx;
	        	e += de;
	        }
	    }
		glEnd();
	}
}
