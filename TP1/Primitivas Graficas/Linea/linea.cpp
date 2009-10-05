#include "linea.h"

void Linea::lineaBresenham(int x0, int y0, int x1, int y1) {

	float m= (float) (y0-y1) / (x0-x1);

	//Si la pendiente es mayor a 1, invierto xi con yi
	if(abs(m) > 1) {
		Funciones::swap(&x0,&y0);
		Funciones::swap(&x1,&y1);		
	}

	int dx= abs(x0-x1);
	int dy= abs(y0-y1);

	int p= 2*dy-dx;
	
	int twoDy= 2*dy;
	int twoDyDx= 2*(dy-dx);
	
	int x,y,xEnd;
	
	/*Determinamos el punto inicial y final*/
	if(x0 > x1) {
		x= x1;
		y= y1;
		xEnd= x0;
	} else {
		x= x0;
		y= y0;
		xEnd= x1;
	}

  glVertex2i(round(x), round(y));
	
	//Si la pendiente es positiva
	if(m > 0) { 
		while(x < xEnd) {
			x++;
			if(p < 0)
				p+= twoDy;
			else {
				y++;
				p+= twoDyDx;			
			}
		  glVertex2i(round(x), round(y));
		}
	} else {
	//Si la pendiente es negativa	
	while(x < xEnd) {
			x++;
			if(p < 0)
				p+= twoDy;
			else {
				y--;
				p+= twoDyDx;			
			}
		  glVertex2i(round(x), round(y));
		}
	}		 	
}


void Linea::lineaDDA(int x0, int y0, int x1, int y1) {
	
	int dx, dy, k, steps;
  float xIncrement, yIncrement, x, y;
  dx= x1-x0;
  dy= y1-y0;
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
