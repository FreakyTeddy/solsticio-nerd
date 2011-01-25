#include "ControladorObjetos.h"

ContenedorObjetos::ContenedorObjetos() {

	//creo todas las superficies dibujables
	crearSuperficies();

}

ContenedorObjetos::~ContenedorObjetos() {
	for (int i=0; i < MAX_DIBUJOS; i++)
		delete superficies[i];
}

void ContenedorObjetos::dibujarObjeto(unsigned int id, unsigned int render_mode) {
	if (id < MAX_DIBUJOS)
		superficies[id]->dibujar(render_mode);
	else
		std::cout<<"id de dibujo inválido: "<<id<<" . Máximo: "<<MAX_DIBUJOS<<std::endl;
}

void ContenedorObjetos::crearSuperficies() {

	//todo rellenar los otros espacios del vector
	superficies[FLORERO] = crearFlorero();
	superficies[ALGA1] = crearAlga1();
	superficies[ALGA2] = crearAlga2();
	superficies[ROCA1] = crearRoca1();
}


Superficie* ContenedorObjetos::crearFlorero() {

	curva.setFactor(4);
	std::vector<Vertice> verts, vertb;
	Vertice t;
	t.set(0,0,0);
	verts.push_back(t);
	verts.push_back(t);
	verts.push_back(t);
	t.set(0,3,0);
	verts.push_back(t);
	t.set(0,5,1);
	verts.push_back(t);
	t.set(0,3,2);
	verts.push_back(t);
	t.set(0,1,4);
	verts.push_back(t);
	t.set(0,2,5);
	verts.push_back(t);
	verts.push_back(t);
	verts.push_back(t);
	curva.Bspline(verts,vertb);
//	t.set(1,0,0); con arena
	t.set(0,0,0);
	Vertice q(0,0,1);
	Superficie* florero = new SuperficieRevolucion(vertb, -360,t,q);
	florero->aplicarTextura("papel.bmp");

	return florero;
}

Superficie* ContenedorObjetos::crearAlga1() {
	std::vector<Vertice> v;
	std::vector<Vertice> trasl;
	Vertice q;
	curva.setFactor(3);

	//puntos de control
	std::vector<Vertice> alga_s;
	q.set(0.5,0,0);
	alga_s.push_back(q);
	q.set(-0.5,0,0);
	alga_s.push_back(q);


	//traslacion de los puntos
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

	//deformacion de los puntos
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

	//creacion de superficie de barrido
	Superficie* sup = new SuperficieBarrido(alga_s, v , def2);
	sup->setDiffuse(0,1,0.5,1);
	sup->setSpecular(0,1,1,1);
	sup->setShininess(50);
	sup->aplicarTextura("madera.bmp");

	return sup;
}

Superficie* ContenedorObjetos::crearAlga2() {
	std::vector<Vertice> v;
	std::vector<Vertice> trasl;
	Vertice q;

	//puntos de control
	std::vector<Vertice> alga_s;

	q.set(0.5,0,0);
	alga_s.push_back(q);
	q.set(-0.5,0,0);
	alga_s.push_back(q);

	//traslacion de los puntos
	Curva curva;
	curva.setFactor(3);

	trasl.clear();
	q.set(0,0,0);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);

	q.set(0.2,0.5,1);
	trasl.push_back(q);

	q.set(0.75,0.75,3);
	trasl.push_back(q);

	q.set(1.5,1.5,4);
	trasl.push_back(q);

	q.set(2,2,3);
	trasl.push_back(q);

	q.set(1.5,1.5,2.5);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	curva.Bspline(trasl, v);

	//deformacion de los puntos
	std::vector<Vertice> def;
	std::vector<Vertice> def2;
	q.set(0.1, 0.1, 1);
	def.push_back(q);
	def.push_back(q);
	def.push_back(q);
	q.set(1,1,1);
	def.push_back(q);
	q.set(1.5,1.5,1);
	def.push_back(q);
	q.set(0.8,0.8,1);
	def.push_back(q);
	q.set(1.4,1.4,1);
	def.push_back(q);
	q.set(0.01, 0.01, 1);
	def.push_back(q);
	def.push_back(q);
	def.push_back(q);
	curva.Bspline(def, def2);

	//creacion de superficie de barrido
	Superficie *sup = new SuperficieBarrido(alga_s, v , def2);
	sup->setDiffuse(0,1,0.5,1);
	sup->setSpecular(0,0.5,0.5,1);
	sup->setShininess(50);
	sup->aplicarTextura("madera.bmp");
	return sup;
}

Superficie* ContenedorObjetos::crearRoca1(){
	std::vector<Vertice> v;
	Vertice q;
	v.push_back(q);
	q.set(0,0,0);
	v.push_back(q);
	q.set(0,1,0);
	v.push_back(q);
	q.set(0,1,1);
	v.push_back(q);
	q.set(0,0,1);
	v.push_back(q);
	Superficie* s= new Superficie(v);
	s->aplicarTextura("stones.bmp");
	return s;

}

