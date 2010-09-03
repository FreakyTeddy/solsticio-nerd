#include "SuperficieRevolucion.h"
#include <iostream>
#include <math.h>
#define PI 3.141592654

SuperficieRevolucion::SuperficieRevolucion(std::vector<Vertice> &forma, float angulo) {

	tam = forma.size(); //guardo la long de la curva patron

	//guardo la malla de vertices de la superficie formada

	int pasos = 30;
	Vertice eje (0,0,0);
	Vertice eje2(0,0,10);
	Vertice v, v1, q;

	//traslado el eje
	eje2 -= eje;
	eje2.normalizar();

	//proyecto sobre yz y calculo el angulo
	v = eje2.proyeccionYZ();
	double norm = v.modulo();
	double sen_x = v.y/norm;
	double cos_x = v.z/norm;

	v1 = eje2;
	std::cout<<" v1: "<<v1.x<<" "<<v1.y<<" "<<v1.z<<std::endl;
	rotar(v1.y, v1.z, sen_x, cos_x);

	double sen_y = v1.x / v1.modulo();
	double cos_y = v1.z / v1.modulo();



	//aplico rotacion

	for (int i=0; i<=pasos; i++) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			/* con ejes coordenados */
//			v.x = forma[pos].x;	v.y = forma[pos].y;	v.z = forma[pos].z;
//			rotar(v.x,v.y, angulo*i/pasos);
//			superficie.push_back(v);

			q = forma[pos];
			//traslado al origen
			q -= eje;
			//roto sobre eje x
			rotar(q.y, q.z, sen_x, cos_x);
			//roto sobre eje y
			rotar(q.z, q.x, sen_y, cos_y);
			//roto el angulo alfa en el eje z
			rotar(q.x, q.y, angulo*i/pasos);

			//hago el camino inverso

			//roto sobre eje y
			rotar(q.z, q.x, -sen_y, cos_y);
			//roto sobre eje x
			rotar(q.y, q.z, -sen_x, cos_x);
			//traslado
			q += eje;

			superficie.push_back(q);
		}
	}

//calculo de normales

	setIndices();
	//setNormales();

}

SuperficieRevolucion::~SuperficieRevolucion() {
	// TODO Auto-generated destructor stub
}

void SuperficieRevolucion::rotar(float &p1, float &p2, float angulo) {

	double alfa = 0;
	alfa = angulo*PI/180;
	float aux = p1;
	p1 = aux * cos(alfa) - p2 * sin(alfa);
	p2 = aux * sin(alfa) + p2 * cos(alfa);

}

void SuperficieRevolucion::rotar(float &p1, float &p2, float seno, float coseno) {

	float aux = p1;
	p1 = aux * coseno - p2 * seno;
	p2 = aux * seno + p2 * coseno;

}

