#include "linea.h"
#include "../../Funciones.h"

void Linea::lineaBresenham(int x0, int y0, int x1, int y1)
{
	//dibuja solo el punto.. tal vez no sea necesario
	if ((x0 == x1) && (y0 == y1)){
	    //glBegin(GL_POINTS);
			glVertex2i(x0, y0);
			//glEnd();
		 return;
	}

	if (x0>x1) {
		Funciones::swap(&x0,&y0);
		Funciones::swap(&x1,&y1);
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

	    //glBegin(GL_POINTS);

	    for ( x = x0; x != x1; x += stepx ) {

	    	glVertex2i( x, y );

	    	if( e <= 0 ) {
	    		e += dosd;
	    	} else {
	    		y += stepy;
	    		e += de;
	    	}
	    }

		//glEnd();

	} else { //lo mismo pero con y

	    de = 2 * (dx - dy);
	    dosd = 2 * dx;
	    e = dosd - dy;
	    x = x0;

	    //glBegin(GL_POINTS);

	    for( y = y0; y != y1; y += stepy ) {

	        glVertex2i( x, y );

	        if( e <= 0 ) {
	        	e += dosd;
	        } else {
	        	x += stepx;
	        	e += de;
	        }
	    }
		//glEnd();
	}
}

void Linea::lineaDDA(int x0, int y0, int x1, int y1) {
	
	int dx, dy, k, steps;
  float xIncrement, yIncrement, x, y;
  dx= x1 - x0;
  dy= y1 - y0;
  x= x0;
  y= y0;

	if(fabs(dx) > fabs(dy))
		steps= fabs(dx);
	else
		steps= fabs(dy);

	xIncrement= ((float) dx)/ ((float) steps);
	yIncrement= ((float) dy)/ ((float) steps);
  
  glVertex2i(round(x), round(y));
   
  for(k= 0; k < steps; k++) {
  	x+= xIncrement;
  	y+= yIncrement;
		glVertex2i(round(x), round(y));
  }
}
