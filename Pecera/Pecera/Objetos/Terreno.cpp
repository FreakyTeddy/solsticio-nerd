#include "Terreno.h"

#include "../Primitivas/Curva/Curva.h"

Terreno::Terreno() {
	Curva c;
	c.setFactor(5);
	Vertice t(CX_INF,0,0);

	//creo el perfil del terreno
	std::vector<Vertice> perfil, ptos_p, traslacion, ptos_t, defo, ptos_d;
	perfil.push_back(t);
	perfil.push_back(t);
	perfil.push_back(t);

	t.set(CX_INF*2/3, 0, 3);
	perfil.push_back(t);

	t.set(CX_INF/3, 0, 3);
	perfil.push_back(t);

	t.set(0, 0, 0);
	perfil.push_back(t);

	t.set(CX_SUP/3, 0, 9);
	perfil.push_back(t);

	t.set(CX_SUP*2/3, 0, 6);
	perfil.push_back(t);

	t.set(CX_SUP,0,0);
	perfil.push_back(t);
	perfil.push_back(t);
	perfil.push_back(t);
	c.Bspline(perfil, ptos_p);

	//traslacion
	t.set(0,CY_INF,0);
	traslacion.push_back(t);
	traslacion.push_back(t);
	traslacion.push_back(t);

	t.set(0,CY_INF*3/4,0);
	traslacion.push_back(t);

	t.set(0,CY_INF/2,2);
	traslacion.push_back(t);

	t.set(0,CY_INF/4,0);
	traslacion.push_back(t);

	t.set(0,0,0);
	traslacion.push_back(t);

	t.set(0,CY_SUP/4,0);
	traslacion.push_back(t);

	t.set(0,CY_SUP/2,5);
	traslacion.push_back(t);

	t.set(0,CY_SUP*3/4, 0);
	traslacion.push_back(t);

	t.set(0, CY_SUP,0);
	traslacion.push_back(t);
	traslacion.push_back(t);
	traslacion.push_back(t);

	c.Bspline(traslacion, ptos_t);


	//deformacion
	t.set(1,1,1);
	defo.push_back(t);
	defo.push_back(t);
	defo.push_back(t);

	t.set(1,CY_INF*3/4,1);
	defo.push_back(t);

	t.set(1,CY_INF/2,1);
	defo.push_back(t);

	t.set(1,CY_INF/4,1);
	defo.push_back(t);

	t.set(1,1,1);
	defo.push_back(t);

	t.set(1,CY_SUP/4,1);
	defo.push_back(t);

	t.set(1,CY_SUP/2,2);
	defo.push_back(t);

	t.set(1,CY_SUP*3/4, 1);
	defo.push_back(t);

	t.set(1, CY_SUP,1);
	defo.push_back(t);
	defo.push_back(t);
	defo.push_back(t);

	c.Bspline(defo, ptos_d);

	sup = new SuperficieBarrido(ptos_p,ptos_t,  false);
	sup->aplicarTextura("arena2.jpg");
	Material m;
	m.setDiffuse(0.83,0.57,0.34,1);
	m.setShininess(0);
	m.setSpecular(0,0,0,1);
	sup->setMaterial(m);

}

Terreno::~Terreno() {
	delete sup;
}
