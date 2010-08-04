#include "Burbuja.h"
#include <cstdlib>
#include <iostream>

Burbuja::Burbuja(float x, float y, float z) {
	// TODO
	//ver valores que correspondan y queden lindos :)
	radio = (float)((rand()%19)+1)/20.0;

	/* trayectoria que seguira la burbuja */
	std::list<Vertice> puntos;
	Vertice v;
	v.x = x; v.y = y; v.z = z;
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10)/5;
	v.y += (float)(rand()%20 - 10)/5;
	v.z += 4;
	std::cout<< "Trayectoria burbuja: "<<std::endl;
	std::cout<<v.x<<" "<<v.y<<" "<<v.z<<std::endl;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10)/10;
	v.y += (float)(rand()%20 - 10)/10;
	v.z += 6;
	std::cout<<v.x<<" "<<v.y<<" "<<v.z<<std::endl;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10)/10;
	v.y += (float)(rand()%20 - 10)/10;
	v.z += 10;
	std::cout<<v.x<<" "<<v.y<<" "<<v.z<<std::endl<<std::endl;
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);
	curva.Bspline(puntos,trayectoria);
}

Burbuja::~Burbuja() {
	// TODO Auto-generated destructor stub
}

void Burbuja::dibujar() {
//TODO

	glEnable(GL_BLEND);
	    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	    glBlendFunc (GL_SRC_ALPHA, GL_ONE);	//transparencia
	    glutSolidSphere (radio, 20, 16);
	glDisable(GL_BLEND);
}

Vertice* Burbuja::getPos() {
	Vertice* v = NULL;
	if (!trayectoria.empty()) { //todavia le queda trayectoria
		v = &(trayectoria.front());
	}
	return v;
}

void Burbuja::animar() {
	if (!trayectoria.empty())  //todavia le queda trayectoria
		trayectoria.pop_front();
}

