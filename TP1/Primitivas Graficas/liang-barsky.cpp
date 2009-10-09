#include "liang-barsky.h"

#define INFINITY  2147483647

ClippingPoligonos::ClippingPoligonos() {}


//implementacion de Liang-Barsky segun Van dam

Poligono* ClippingPoligonos::clippingLB(int Vtop, int Vbottom, int Vleft, int Vright, Poligono* poligono){
     std::list<Vertice> verticesOriginales = poligono->obtenerVertices();
     std::list<Vertice>::iterator it = verticesOriginales.begin();
     Poligono* poligonoClippeado = new Poligono();
     Vertice vertice0;
     float xo0,xo1,yo0,yo1; //pares x,y originales
     float x0 = (*it).x;
     float x1 = 0;
     float y0 = (*it).y;
     float y1 = 0;

     vertice0.x=x0;
     vertice0.y=y0;

     verticesOriginales.push_back(vertice0);
     
     float xIn, xOut, yIn, yOut;                   // Coordenadas de entrada y salida pofloats
     float tOut1, tIn2, tOut2;                     // Parameter values of same  
     float tInX, tOutX, tInY, tOutY;               // Parameter values for floatersection  
     float deltaX, deltaY;                         // Direction of edge  
     int i;  

     for(it=verticesOriginales.begin();it!=verticesOriginales.end();it++,x0=xo1,y0=yo1){
	  xo1=x1=(*it).x;
	  yo1=y1=(*it).y;

	  deltaX=x1-x0;
	  deltaY=y1-y0;

	  if((deltaX > 0) || (deltaX == 0 && x0 > Vright)) {  
	       xIn = Vleft; xOut = Vright;  
	  } else{
	       xIn = Vright; xOut = Vleft;  
	  }  
	  if((deltaY > 0) || (deltaY == 0 && y0 > Vtop)) {  
	       yIn = Vbottom; yOut = Vtop;  
	  } else {  
		    yIn = Vtop; yOut = Vbottom;  
	  }
		    
	  if(deltaX != 0) {  
	       tOutX = ((xOut - x0)*256.0) / deltaX;  
	  } else if(x0 <= Vright && Vleft <= x0)  
	       tOutX = INFINITY;  
	  else  
	       tOutX = -INFINITY;  
	  
	  if(deltaY != 0) {  
	       tOutY = ((yOut - y0)*256.0) / deltaY;  
	  } else if(y0 <= Vtop && Vbottom <= y0)  
	       tOutY = INFINITY;  
	  else  
	       tOutY = -INFINITY;  
   
         // Order the two exit points  
	  if(tOutX < tOutY) {  
	       tOut1 = tOutX; tOut2 = tOutY;  
	  } else {
	       tOut1 = tOutY; tOut2 = tOutX;  
	  }  
   
	  if(tOut2 > 0) {  
	       
	       if(deltaX != 0)  
		    tInX = ((xIn - x0)*256.0) / deltaX;  
	       else  
		    tInX = -INFINITY;  
	       
	       if(deltaY != 0)  
		    tInY = ((yIn - y0)*256.0) / deltaY;  
	       else  
		    tInY = -INFINITY;  
	       
	       if(tInX < tInY)  
		    tIn2 = tInY;  
	       else  
		    tIn2 = tInX;  
	       
	       if(tOut1 < tIn2) {   // no visible segment  
		    if(0 < tOut1 && tOut1 <= 256) {
			 // line crosses over intermediate corner region  
			 if(tInX < tInY) {
			      poligonoClippeado->agregarVertice(xOut,yIn);
			 } else { 
			      poligonoClippeado->agregarVertice(xIn,yOut);
			 }
		    } 
			 
	       } else {
   
		    // line crosses though window  
		    if(0 < tOut1 && tIn2 <= 256.0) {  
			 if(0 <= tIn2) {  // visible segment  
			      if(tInX > tInY) {  
				   poligonoClippeado->agregarVertice(xIn, y0 + ((tInX * deltaY)/256.0));
			      } else {
				   poligonoClippeado->agregarVertice(x0 + ((tInY * deltaX)/256.0), yIn);
			      }
			 }
   
			 if((1<<8) >= tOut1) {  
			      if(tOutX < tOutY) {  
				   poligonoClippeado->agregarVertice(xOut, y0 + ((tOutX * deltaY)/256.0));
			      } else {
				   poligonoClippeado->agregarVertice(x0 + ((tOutY * deltaX)/256.0), yOut);
			      }
			 } else { 
			      poligonoClippeado->agregarVertice(x1,y1);
			 }
		    }
		    
	       }
   
	       if(0 < tOut2 && tOut2 <= 256) {
		    poligonoClippeado->agregarVertice(xOut,yOut);
	       }
	       
	  }  
     }
     
     return poligonoClippeado;
}

ClippingPoligonos::~ClippingPoligonos() {}
