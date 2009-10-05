#include "linea.h"

void Linea::lineaBresenham(int x0, int y0, int x1, int y1) {

	float m= (float) (y0-y1) / (x0-x1);
	std::cout << "Pendiente B: " << m << std::endl;

	int dx= abs(x0-x1);
	int dy= abs(y0-y1);

	int p= 2*dy-dx;

	int twoDy= 2*dy;
	int twoDyDx= 2*(dy-dx);

	int twoDx= 2*dx;
	int twoDxDy= 2*(dx-dy);
	
	int x,y,xEnd,yEnd;

	//Pendientes positivas
	if(m>=0) {
		
		std::cout << "PENDIENTE POSITIVA" << std::endl; 
		
		//Si la pendiente esta entre 0<m<=1
		if(m>=0 && m<=1) {
			//Determinamos el punto inicial y final en x
			if(x0 > x1) {
				x= x1;
				y= y1;
				xEnd= x0;
			} else {
				x= x0;
				y= y0;
				xEnd= x1;
			}
	
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
		//Si la pendiente es m>1
		//Determinamos el punto inicial y final en y
			if(y0 > y1) {
				x= x1;
				y= y1;
				yEnd= y0;
			} else {
				x= x0;
				y= y0;
				yEnd= y1;
			}
			glVertex2i(round(x), round(y));
			
			while(y < yEnd) {
				y++;
				if(p < 0)
					p+= twoDx;
				else {
					x++;
					p+= twoDxDy;			
				}
				glVertex2i(round(x), round(y));
			}
		}
			
	} else {
	//Si la pendiente es negativa	
		std::cout << "PENDIENTE NEGATIVA" << std::endl; 
		//Si la pendiente esta entre 0<m<=1
		if(abs(m)>0 && abs(m)<=1) {
			//Determinamos el punto inicial y final en x
			if(x0 > x1) {
				x= x1;
				y= y1;
				xEnd= x0;
			} else {
				x= x0;
				y= y0;
				xEnd= x1;
			}
	
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
			
		} else {
		//Si la pendiente es m>1
		//Determinamos el punto inicial y final en y
			if(y0 > y1) {
				x= x1;
				y= y1;
				yEnd= y0;
			} else {
				x= x0;
				y= y0;
				yEnd= y1;
			}
			glVertex2i(round(x), round(y));
			
			while(y < yEnd) {
				y++;
				if(p < 0)
					p+= twoDx;
				else {
					x--;
					p+= twoDxDy;			
				}
				glVertex2i(round(x), round(y));
			}
		}
	}
}


void Linea::lineaDDA(int x0, int y0, int x1, int y1) {
	
	float m= (float) (y0-y1) / (x0-x1);

	std::cout << "Pendiente D: " << m << std::endl;
	
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
