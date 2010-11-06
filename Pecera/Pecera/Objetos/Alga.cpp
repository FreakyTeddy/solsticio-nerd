
#include "Alga.h"
#include "../Primitivas/Curva/Curva.h"

Alga::Alga() {

	/* ejemplo de alga */
	std::vector<Vertice> v;
	std::vector<Vertice> trasl;
	Vertice q;
	Curva curva;
	std::vector<Vertice> alga_c;
	std::vector<Vertice> alga_s;
	q.set(0.5,0,0);
	alga_c.push_back(q);
	alga_c.push_back(q);
	alga_c.push_back(q);
	q.set(-0.5,0,0);
	alga_c.push_back(q);
	alga_c.push_back(q);
	alga_c.push_back(q);
	curva.Bspline(alga_c, alga_s);

	trasl.clear();
	q.set(0,0,0);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);

	q.set(0,-1,1.5);
	trasl.push_back(q);

	q.set(0,0,4);
	trasl.push_back(q);

	q.set(0.5,0.5,6);
	trasl.push_back(q);

	q.set(0.5,0.8,6.5);
	trasl.push_back(q);

	q.set(0.8,0.8,7);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	curva.Bspline(trasl, v);

	std::vector<Vertice> def;
	std::vector<Vertice> def2;
	q.set(0.1, 0.1, 1);
	def.push_back(q);
	def.push_back(q);
	def.push_back(q);
	q.set(1,1,1);
	def.push_back(q);
	q.set(0.5,0.5,1);
	def.push_back(q);
	q.set(0.8,0.8,1);
	def.push_back(q);
	q.set(0.4,0.4,1);
	def.push_back(q);
	q.set(0.01, 0.01, 1);
	def.push_back(q);
	def.push_back(q);
	def.push_back(q);
	curva.Bspline(def, def2);

	this->alga = new SuperficieBarrido(alga_s, v , def2);
	alga->setDiffuse(0,1,0.5,1);
	alga->setSpecular(0,0.5,0.5,1);
	alga->setShininess(50);
}

Alga::~Alga() {
	delete this->alga;
}

void Alga::dibujar() {
	this->alga->dibujar();
}

