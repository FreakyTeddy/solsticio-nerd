#include "linea.h"

void Linea::lineaBresenham(int x0, int y0, int x1, int y1) {

	float m= (float) (y0-y1) / (x0-x1);

	int dx= abs(x0-x1);
	int dy= abs(y0-y1);

	int x,y,step;
	
	if(m>=0)
		//Pendiente positiva
		step= 1;
	else
		//Pendiente negativa 	
		step= -1;

	//Si el modulo de la pendiente esta entre 0<m<=1
	if(abs(m)>=0 && abs(m)<=1) {
		int py= 2*dy-dx;
		int twoDy= 2*dy;
		int twoDyDx= 2*(dy-dx);
		int xEnd;
		
		//Determinamos el punto inicial y final en x
		if(x0>x1) {
			x= x1;
			y= y1;
			xEnd= x0;
		} else {
			x= x0;
			y= y0;
			xEnd= x1;
		}

		while(x<xEnd) {
			x++;
			if(py<0)
				py+= twoDy;
			else {
				y+=step;
				py+= twoDyDx;			
			}
		  glVertex2i(round(x), round(y));
		}
		
	} else {
	//Si el modulo de la pendiente es m>1
		int px= 2*dx-dy;
		int twoDx= 2*dx;
		int twoDxDy= 2*(dx-dy);
		int yEnd;
		
	//Determinamos el punto inicial y final en y
		if(y0>y1) {
			x= x1;
			y= y1;
			yEnd= y0;
		} else {
			x= x0;
			y= y0;
			yEnd= y1;
		}
		glVertex2i(round(x), round(y));
		
		while(y<yEnd) {
			y++;
			if(px < 0)
				px+= twoDx;
			else {
				x+= step;
				px+= twoDxDy;			
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
   
  for(k= 0; k<steps; k++) {
  	x+= xIncrement;
  	y+= yIncrement;
		glVertex2i(round(x), round(y));
  }
}
