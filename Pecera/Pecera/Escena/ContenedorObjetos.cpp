#include "ContenedorObjetos.h"
#include <math.h>

ContenedorObjetos* ContenedorObjetos::instancia=0;

ContenedorObjetos::ContenedorObjetos() {
	//creo todas las superficies dibujables
	crearSuperficies();
	crearAnimaciones();
	crearCardumenes();
	crearBurbuja();
}

ContenedorObjetos::~ContenedorObjetos() {
	for (int i=0; i < MAX_DIBUJOS; i++)
		delete superficies[i];
	for (int i=0; i < MAX_ANIMACIONES; i++)
		delete animaciones[i];
	for (int i=0; i < MAX_CARDUMEN; i++)
		delete cardumen[i];
	for (int i=0; i < MAX_TIPO_PECES; i++){
		delete cuerpos[i];
		delete aletas[i];
		delete colas[i];
	}

	delete tray_burbujas;
	glDeleteLists(handle_burbuja, 2);
	glDeleteLists(handle_agua, 1);
}

void ContenedorObjetos::dibujarObjeto(unsigned int id, unsigned int render_mode) {
	if (id == BURBUJA){
		if (render_mode == GL_LINE)
			glCallList(handle_burbuja);
		else
			glCallList(handle_burbuja+1);
		return;
	}
	glEnable(GL_CULL_FACE);
		superficies[id]->dibujar(render_mode);
	glDisable(GL_CULL_FACE);
}

void ContenedorObjetos::crearSuperficies() {

	superficies[FLORERO] = crearFlorero();
	superficies[ROCA2] = crearRoca2();
	superficies[ROCA1] = crearRoca1();
	superficies[ROCA0] = crearRoca0();

	cuerpos[PEZ0] = crearPez0();
	cuerpos[PEZ1] = crearPez1();
	cuerpos[PEZ2] = crearPez2();

	longitud[PEZ0].set(0.4,-1.49);
	longitud[PEZ1].set(0.65,-2.8);	//hardcodeeeeeeeee
	longitud[PEZ2].set(0.8,-1.9);

	crearAgua();
}

void ContenedorObjetos::crearAnimaciones() {
	animaciones[ALGA0] = crearAlga0();
	animaciones[ALGA1] = crearAlga1();
	animaciones[ALGA2] = crearAlga2();
	animaciones[BIGOTE] = crearBigote();

	aletas[PEZ0] = crearAletaPez0();
	aletas[PEZ1] = crearAletaPez1();
	aletas[PEZ2] = crearAletaPez2();

	colas[PEZ0] = crearColaPez0();
	colas[PEZ1] = crearColaPez1();
	colas[PEZ2] = crearColaPez2();
}

void ContenedorObjetos::crearCardumenes() {
	cardumen[CAR2] = crearCardumen2();
	cardumen[CAR1] = crearCardumen1();
	cardumen[CAR0] = crearCardumen0();
}

void ContenedorObjetos::crearBurbuja() {
	handle_burbuja = glGenLists(2);

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	Material m;
	m.setDiffuse(0.85,0.85,0.96,0.3);
	m.setAmbient(0.01,0.05,0.1,0.3);
	m.setSpecular(0.5,0.55,1,0.2);
	m.setShininess(100);

	/* sin transparencia, con lineas */
	glNewList(handle_burbuja, GL_COMPILE);

		m.usarMaterial();
	    gluQuadricDrawStyle(qobj, GLU_LINE);
	    gluQuadricNormals(qobj, GLU_SMOOTH);
		gluSphere(qobj, 1, 15, 10);


	glEndList();

	/* con transparencia y con relleno*/
	glNewList(handle_burbuja+1, GL_COMPILE);

		m.usarMaterial();
	    gluQuadricDrawStyle(qobj, GLU_FILL);
	    gluQuadricNormals(qobj, GLU_SMOOTH);

		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//transparencia

				glCullFace( GL_FRONT );
				gluSphere(qobj, 0.75, 12, 8);
				glCullFace( GL_BACK );
				gluSphere(qobj, 0.75, 12, 8);

		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
	glEndList();

	gluDeleteQuadric(qobj);

	/* trayectoria que seguira la burbuja */
	std::vector<Vertice> puntos;
	Vertice v;
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);
	v.x = -(float)(rand()%10);
	v.y = -(float)(rand()%10);
	v.z = 28;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 35;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 46;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 55;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 65;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 78;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 98;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10);
	v.y += (float)(rand()%20 - 10);
	v.z = 128;
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);
	tray_burbujas = new Trayectoria(puntos,false,8,false);
	tray_burbujas->setColor(0.5,0.8,1);
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
	t.set(-1,0,0);
	Vertice q(0,0,1);
	Superficie* florero = new SuperficieRevolucion(vertb, -360,t,q);
	florero->aplicarTextura("papel.bmp");

	return florero;
}

Animacion* ContenedorObjetos::crearAlga2() {
	std::vector<Vertice> v;			/* alga doblada */
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
	curva.setFactor(4);

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
	Vertice dir(0,1,0);
	Animacion *ani = new Animacion(alga_s,v,def2,dir,2,25, true);
	Material m;
	m.setDiffuse(0,1,0.5,1);
	m.setSpecular(0,0.5,0.5,1);
	m.setShininess(50);
	ani->setTextura("madera.bmp");
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearAlga1() {
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
	q.set(0,0,0);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	q.set(0,0,1.5);
	trasl.push_back(q);
	q.set(0,0,4);
	trasl.push_back(q);
	q.set(0.5,0,6);
	trasl.push_back(q);
	q.set(0.5,0,6.5);
	trasl.push_back(q);
	q.set(0.8,0,7);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	curva.Bspline(trasl,v);

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
	def.clear();

	Vertice dir(0,1,0);
	Animacion *ani = new Animacion(alga_s,v,def2,dir,2,25, true);
	Material m;
	m.setDiffuse(0,1,0.5,1);
	m.setSpecular(0,0.5,0.5,1);
	m.setShininess(50);
	ani->setTextura("madera2.bmp");
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearAlga0() {
	std::vector<Vertice> v; /* alga "serpiente" */
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
	q.set(0,0,0);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	q.set(0,0,1.5);
	trasl.push_back(q);
	q.set(0,1,2);
	trasl.push_back(q);
	q.set(0,1,4);
	trasl.push_back(q);
	q.set(0,3,4.5);
	trasl.push_back(q);
	q.set(0,3,6);
	trasl.push_back(q);
	q.set(0,4,6.5);
	trasl.push_back(q);
	q.set(0,4,7);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	curva.Bspline(trasl,v);

	//deformacion de los puntos
	std::vector<Vertice> def;
	std::vector<Vertice> def2;
	q.set(0.1, 0.1, 1);
	def.push_back(q);
	def.push_back(q);
	def.push_back(q);
	q.set(0.71,1,1);
	def.push_back(q);
	q.set(0.51,1,1);
	def.push_back(q);
	q.set(0.61,1,1);
	def.push_back(q);
	q.set(0.71,1,1);
	def.push_back(q);
	q.set(0.61,1,1);
	def.push_back(q);
	q.set(0.31,1,1);
	def.push_back(q);
	q.set(0.01, 1, 1);
	def.push_back(q);
	def.push_back(q);
	def.push_back(q);
	curva.Bspline(def, def2);
	def.clear();

	Vertice dir(0,1,0);
	Animacion *ani = new Animacion(alga_s,v,def2,dir,2,25, true);
	Material m;
	m.setDiffuse(0,1,0.5,1);
	m.setSpecular(0,0.5,0.5,1);
	m.setShininess(50);
	ani->setTextura("madera.bmp");
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearColaPez0() {

	std::vector<Vertice> ctrol_c, curva_c, t1, t2, t3, t4, def, def2;
	Vertice t(0,0,0.5);
	ctrol_c.push_back(t);
	ctrol_c.push_back(t);
	ctrol_c.push_back(t);
	t.set(0,-0.3,0.3);
	ctrol_c.push_back(t);
	t.set(0,0.3,0);
	ctrol_c.push_back(t);
	t.set(0,-0.3,-0.3);
	ctrol_c.push_back(t);
	t.set(0,0,-0.5);
	ctrol_c.push_back(t);
	ctrol_c.push_back(t);
	ctrol_c.push_back(t);
	curva.setFactor(2);
	curva.Bspline(ctrol_c,curva_c);

	t.set(0,0,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);
	t.set(0.3,-0.2,0);
	t1.push_back(t);
	t.set(-0.3,-0.6,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);

	curva.setFactor(2);
	curva.Bspline(t1,t3);

	t.set(0,0,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);
	t.set(-0.3,-0.2,0);
	t2.push_back(t);
	t.set(0.3,-0.6,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);

	curva.Bspline(t2,t4);

	t.set(0,0,0.2);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);
	t.set(1,0,1);
	def.push_back(t);
	t.set(1,1,1);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);

	curva.Bspline(def,def2);

	Animacion* ani = new Animacion(curva_c,t3,t4,def2,2);
	ani->setModoTransicion(false);
	ani->setTextura("plateadoaleta.png");
	Material m;
	m.setDiffuse(1,1,0.8,1);
	m.setSpecular(1,1,0,1);
	m.setAmbient(0.1,0.1,0.1,1);
	m.setShininess(120);
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearColaPez1() {

	std::vector<Vertice> ctrol_s, t1, t2, t3, t4, def, def2;
	Vertice t(0,0,0.3);
	ctrol_s.push_back(t);
	t.set(0,0.3,0);
	ctrol_s.push_back(t);
	t.set(0,0,-0.3);
	ctrol_s.push_back(t);

	t.set(0,0,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);
	t.set(0.5,-0.8,0);
	t1.push_back(t);
	t.set(-0.5,-1.2,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);

	curva.setFactor(2);
	curva.Bspline(t1,t3);

	t.set(0,0,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);
	t.set(-0.5,-0.8,0);
	t2.push_back(t);
	t.set(0.5,-1.2,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);

	curva.Bspline(t2,t4);

	t.set(0,1,0);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);
	t.set(1,1,1);
	def.push_back(t);
	t.set(1,1,1.8);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);

	curva.Bspline(def,def2);

	Animacion* ani = new Animacion(ctrol_s,t3,t4,def2,2);
	ani->setModoTransicion(false);
	ani->setTextura("dorialeta.png");
	Material m;
	m.setDiffuse(0,0.53,0.73,1);
	m.setSpecular(1,1,0,1);
	m.setShininess(120);
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearColaPez2() {
	std::vector<Vertice> ctrol, curva_c, t1,t2,def;
	Vertice t;

	t.set(0,0,1);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(0,-0.3,0.5);
	ctrol.push_back(t);
	t.set(0,0.3,0);
	ctrol.push_back(t);
	t.set(0,-0.3,-0.5);
	ctrol.push_back(t);
	t.set(0,0,-1);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	curva.setFactor(2);
	curva.Bspline(ctrol,curva_c);

	ctrol.clear();
	t.set(0,0,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(0.5,-0.8,0);
	ctrol.push_back(t);
	t.set(-0.5,-1.2,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);

	curva.setFactor(2);
	curva.Bspline(ctrol,t1);

	ctrol.clear();
	t.set(0,0,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(-0.5,-0.8,0);
	ctrol.push_back(t);
	t.set(0.5,-1.2,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);

	curva.Bspline(ctrol,t2);

	ctrol.clear();
	t.set(0,1,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(1,1,1);
	ctrol.push_back(t);
	t.set(1,1,1.8);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);

	curva.Bspline(ctrol,def);

	Animacion* ani = new Animacion(curva_c,t1,t2,def,2);
	ani->setModoTransicion(false);
	ani->setTextura("koialeta.png");
	Material m;
	m.setDiffuse(1,1,1,1);
	m.setSpecular(1,0.5,0,1);
	m.setAmbient(0.1,0.1,0.1,1);
	m.setShininess(120);
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearAletaPez0() {
	std::vector<Vertice> ctrol_s, t1, t2, t3, t4, def, def2;
	Vertice t(0,0,0);
	ctrol_s.push_back(t);
	t.set(0,-0.5,0);
	ctrol_s.push_back(t);

	t.set(0,0,-0.3);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);
	t.set(0.2,-0.1,-0.55);
	t1.push_back(t);
	t.set(0.3,-0.2,-0.8);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);

	curva.setFactor(2);
	curva.Bspline(t1,t3);

	t.set(0,0,-0.3);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);
	t.set(0.1,-0.1,-0.50);
	t2.push_back(t);
	t.set(0.3,-0.2,-0.70);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);

	curva.Bspline(t2,t4);

	t.set(1,1,1);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);
	t.set(1,0.5,1);
	def.push_back(t);
	t.set(1,0,1);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);

	curva.Bspline(def,def2);

	Animacion* ani = new Animacion(ctrol_s,t3,t4,def2,2);
	ani->setModoTransicion(false);
	ani->setTextura("plateadoaleta.png");
	Material m;
	m.setDiffuse(1,1,0.8,1);
	m.setSpecular(1,1,0,1);
	m.setAmbient(0.1,0.1,0.1,1);
	m.setShininess(120);
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearAletaPez1(){

	std::vector<Vertice> ctrol_s, t1, t2, t3, t4, def, def2;
	Vertice t(0,0,-0.2);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	t.set(0,0.2,0);
	ctrol_s.push_back(t);
	t.set(0,0,0.3);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);

	t.set(0,0,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);
	t.set(0.2,-0.3,0.5);
	t1.push_back(t);
	t.set(-0.1,-0.9,1);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);

	curva.setFactor(2);
	curva.Bspline(t1,t3);

	t.set(0,0,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);
	t.set(-0.1,-0.3,0.5);
	t2.push_back(t);
	t.set(0.2,-0.9,1);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);

	curva.Bspline(t2,t4);

	t.set(1,0.8,0.7);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);
	t.set(1,1,1);
	def.push_back(t);
	t.set(1,1,0);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);

	curva.Bspline(def,def2);

	Animacion* ani = new Animacion(ctrol_s,t3,t4,def2,2);
	ani->setModoTransicion(false);
	ani->setTextura("dorialeta.png");
	Material m;
	m.setDiffuse(0,0.53,0.73,1);
	m.setSpecular(1,1,0,1);
	m.setShininess(120);
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearAletaPez2() {
	std::vector<Vertice> ctrol_s, t1, t2, t3, t4, def, def2;
	Vertice t(0,0,-0.4);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	t.set(0.1,0,0);
	ctrol_s.push_back(t);
	t.set(0,0,0.4);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);

	t.set(0,0,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);
	t.set(0.2,-0.3,0);
	t1.push_back(t);
	t.set(0.3,-0.6,0);
	t1.push_back(t);
	t1.push_back(t);
	t1.push_back(t);

	curva.setFactor(2);
	curva.Bspline(t1,t3);

	t.set(0,0,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);
	t.set(0.1,-0.3,0);
	t2.push_back(t);
	t.set(0.15,-0.6,0);
	t2.push_back(t);
	t2.push_back(t);
	t2.push_back(t);

	curva.Bspline(t2,t4);

	t.set(1,1,0.2);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);
	t.set(1,1,1);
	def.push_back(t);
	t.set(1,1,0.4);
	def.push_back(t);
	def.push_back(t);
	def.push_back(t);

	curva.Bspline(def,def2);

	Animacion* ani = new Animacion(ctrol_s,t3,t4,def2,2);
	ani->setModoTransicion(false);
	ani->setTextura("koialeta.png");
	Material m;
	m.setDiffuse(1,1,1,1);
	m.setSpecular(1,0.5,0,1);
	m.setAmbient(0.1,0.1,0.1,1);
	m.setShininess(120);
	ani->setMaterial(m);
	return ani;
}

Animacion* ContenedorObjetos::crearBigote() {

	std::vector<Vertice> ctrol, bigo, tl, def;

	Vertice t(0,0,-0.2);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(0,-0.15,0);
	ctrol.push_back(t);
	t.set(0,0,0.2);
	ctrol.push_back(t);
	t.set(0,0.15,0);
	ctrol.push_back(t);
	t.set(0,0,-0.2);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);

	curva.setFactor(2);
	curva.Bspline(ctrol,bigo);
	bigo.push_back(t);


	ctrol.clear();
	t.set(0,0,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(0.11,0.05,-0.08);
	ctrol.push_back(t);
	t.set(0.06,0.06,-0.33);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	curva.Bspline(ctrol,tl);

	ctrol.clear();
	t.set(0.1,0.1,0.1);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	t.set(1,1,1);
	ctrol.push_back(t);
	t.set(0,0,0);
	ctrol.push_back(t);
	ctrol.push_back(t);
	ctrol.push_back(t);
	curva.Bspline(ctrol,def);
	Vertice dir(0.2,0,-0.2);
	Animacion *ani = new Animacion(bigo,tl,def,dir,4,15, true);
	ani->setTextura("koi.png");
	Material m;
	m.setDiffuse(1,1,1,1);
	m.setSpecular(1,0.5,0,1);
	m.setAmbient(0.1,0.1,0.1,1);
	m.setShininess(120);
	ani->setMaterial(m);
	ani->setCull(GL_BACK);
	return ani;
}

Superficie* ContenedorObjetos::crearPez0() {
	std::vector<Vertice> ctrol_s, curva_s, ctrol_t, curva_t, ctrol_d, curva_d;
	Vertice t;

	t.set(0,0,-1);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	t.set(0.2,-0.5,-0.6);
	ctrol_s.push_back(t);
	t.set(0.6,0,0);
	ctrol_s.push_back(t);
	t.set(0.2,-0.5,0.6);
	ctrol_s.push_back(t);
	t.set(0,0,1);
	ctrol_s.push_back(t);
	t.set(-0.2,-0.5,0.6);
	ctrol_s.push_back(t);
	t.set(-0.6,0,0);
	ctrol_s.push_back(t);
	t.set(-0.2,-0.5,-0.6);
	ctrol_s.push_back(t);
	t.set(0,0,-1);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);

	curva.setFactor(3);
	curva.Bspline(ctrol_s,curva_s);
	curva_s.push_back(t);

	t.set(0,1.1,-0.05);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	t.set(0,0.7,-0.05);
	ctrol_t.push_back(t);
	t.set(0,0.5,0);
	ctrol_t.push_back(t);
	t.set(0,0,0);
	ctrol_t.push_back(t);
	t.set(0,-1,0);
	ctrol_t.push_back(t);
	t.set(0,-1.3,0);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);

	curva.setFactor(2);
	curva.Bspline(ctrol_t,curva_t);
	curva_t.push_back(t);

	ctrol_t.push_back(t);
	t.set(0.1,0,0.1);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	t.set(0.2,0,0.2);
	ctrol_d.push_back(t);
	t.set(1,0,0.8);
	ctrol_d.push_back(t);
	t.set(1,0,1);
	ctrol_d.push_back(t);
	t.set(1,1,1.3);
	ctrol_d.push_back(t);
	t.set(0,1,1.1);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);

	curva.setFactor(2);
	curva.Bspline(ctrol_d,curva_d);
	curva_d.push_back(t);

	Superficie *s = new SuperficieBarrido(curva_s,curva_t,curva_d);
	s->getMaterial()->setDiffuse(1,1,0.8,1);
	s->getMaterial()->setSpecular(1,1,0,1);
	s->getMaterial()->setAmbient(0.1,0.1,0.1,1);
	s->getMaterial()->setShininess(120);
	s->aplicarTextura("plateado.png");
	return s;

}

Superficie* ContenedorObjetos::crearPez1(){
	std::vector<Vertice> ctrol_s, curva_s, ctrol_t, curva_t, ctrol_d, curva_d;
	Vertice t(0,0,2);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	t.set(1,0,0);
	ctrol_s.push_back(t);
	t.set(0,0,-2);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	t.set(-1,0,0);
	ctrol_s.push_back(t);
	t.set(0,0,2);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	ctrol_s.push_back(t);
	curva.setFactor(3);
	curva.Bspline(ctrol_s, curva_s);
	curva_s.push_back(t);

	t.set(0,-3,0);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	t.set(0,-1,0);
	ctrol_t.push_back(t);
	t.set(0,0,0);
	ctrol_t.push_back(t);
	t.set(0,0.5,0);
	ctrol_t.push_back(t);
	t.set(0,1,0);
	ctrol_t.push_back(t);
	t.set(0,2,0);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	curva.setFactor(3);
	curva.Bspline(ctrol_t, curva_t);

	t.set(0,1,0);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	t.set(0.5,1,0.5);
	ctrol_d.push_back(t);
	t.set(1,1,1);
	ctrol_d.push_back(t);
	t.set(1,1,0.9);
	ctrol_d.push_back(t);
	t.set(0.9,1,0.6);
	ctrol_d.push_back(t);
	t.set(0,1,0);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	curva.setFactor(3);
	curva.Bspline(ctrol_d, curva_d);

	Superficie *s = new SuperficieBarrido(curva_s,curva_t,curva_d);
	s->getMaterial()->setDiffuse(0,0.53,0.73,1);
	s->getMaterial()->setSpecular(1,1,0,1);
	s->getMaterial()->setShininess(120);
	s->aplicarTextura("dori.png");
	return s;
}

Superficie* ContenedorObjetos::crearPez2() {

	std::vector<Vertice>ctrol_p, curva_p;
	Vertice t(0,1.7,0);
	ctrol_p.push_back(t);
	ctrol_p.push_back(t);
	ctrol_p.push_back(t);

	t.set(0,2,-0.1);
	ctrol_p.push_back(t);
	t.set(0,1.5,-0.7);
	ctrol_p.push_back(t);
	t.set(0,0,-1);
	ctrol_p.push_back(t);
	t.set(0,-1.5,-0.3);
	ctrol_p.push_back(t);
	t.set(0,-2,-0.3);
	ctrol_p.push_back(t);
	t.set(0,-2,0);
	ctrol_p.push_back(t);
	ctrol_p.push_back(t);
	ctrol_p.push_back(t);

	curva.Bspline(ctrol_p, curva_p);
	t.set(0,1,0);
	Vertice q;
	Superficie* sup = new SuperficieRevolucion(curva_p, -360, q,t) ;
	sup->aplicarTextura("koi.png");
	sup->getMaterial()->setSpecular(1,0.5,0,1);
	sup->getMaterial()->setDiffuse(1,1,1,1);
	sup->getMaterial()->setAmbient(0.1,0.1,0.1,1);
	sup->getMaterial()->setShininess(120);
	return sup;
}

Superficie* ContenedorObjetos::crearRoca0() {

	std::vector<Vertice> ctrol_r,curva_r;
	Vertice t;
	t.set(0,1,0);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);
	t.set(0.5,0.9,0);
	ctrol_r.push_back(t);
	t.set(0.8,0.8,0);
	ctrol_r.push_back(t);
	t.set(1,0.7,0);
	ctrol_r.push_back(t);
	t.set(0.8,0.4,0);
	ctrol_r.push_back(t);
	t.set(0.6,0.1,0);
	ctrol_r.push_back(t);
	t.set(0,0,0);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);

	curva.setFactor(2);
	curva.Bspline(ctrol_r,curva_r);

	t.set(0,1,0);
	Vertice q;
	Superficie* sup = new SuperficieRevolucion(curva_r, 180, q,t,10) ;
	sup->aplicarTextura("stones.bmp");
	sup->getMaterial()->setSpecular(0,0.1,0.5,1);
	sup->getMaterial()->setDiffuse(0.5,0.5,0.5,1);
	sup->getMaterial()->setAmbient(0.1,0.1,0.1,1);
	sup->getMaterial()->setShininess(50);
	sup->setCullFace(GL_BACK);

	return sup;
}

Superficie* ContenedorObjetos::crearRoca1(){

	std::vector<Vertice> ctrol_r, ctrol_t, curva_t, ctrol_d, curva_d;
	Vertice t;


	t.set(-0.4,0,0);
	ctrol_r.push_back(t);
	t.set(-0.5,0,0.1);
	ctrol_r.push_back(t);
	t.set(-0.2,0,0.3);
	ctrol_r.push_back(t);
	t.set(-0.5,0,0.5);
	ctrol_r.push_back(t);
	t.set(-0.3,0,0.7);
	ctrol_r.push_back(t);
	t.set(0,0,1);
	ctrol_r.push_back(t);
	t.set(0.2,0,0.7);
	ctrol_r.push_back(t);
	t.set(0.4,0,0.5);
	ctrol_r.push_back(t);
	t.set(0.3,0,0.3);
	ctrol_r.push_back(t);
	t.set(0.5,0,0.1);
	ctrol_r.push_back(t);
	t.set(0.45,0,0);
	ctrol_r.push_back(t);

	t.set(0,1,0);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	t.set(0,0.8,0);
	ctrol_t.push_back(t);
	t.set(0,0.6,0);
	ctrol_t.push_back(t);
	t.set(0,0.2,0);
	ctrol_t.push_back(t);
	t.set(0,0.1,0);
	ctrol_t.push_back(t);
	t.set(0,0,0);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	ctrol_t.push_back(t);
	curva.setFactor(3);
	curva.Bspline(ctrol_t,curva_t);


	t.set(0,1,0);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	t.set(0.8,1,0.3);
	ctrol_d.push_back(t);
	t.set(1.3,1,1.4);
	ctrol_d.push_back(t);
	t.set(1,1,1);
	ctrol_d.push_back(t);
	t.set(0.2,1,0.5);
	ctrol_d.push_back(t);
	t.set(0,1,0);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	ctrol_d.push_back(t);
	curva.Bspline(ctrol_d,curva_d);

	Superficie* sup = new SuperficieBarrido(ctrol_r,curva_t, curva_d,true);
	sup->aplicarTextura("stones.bmp");
	sup->getMaterial()->setSpecular(0,0.1,0.5,1);
	sup->getMaterial()->setDiffuse(0.5,0.5,0.5,1);
	sup->getMaterial()->setAmbient(0.1,0.1,0.1,1);
	sup->getMaterial()->setShininess(50);
	sup->setCullFace(GL_BACK);
	return sup;

}

Superficie* ContenedorObjetos::crearRoca2() {

	std::vector<Vertice> ctrol_r,curva_r;
	Vertice t;
	t.set(0,2,0);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);
	t.set(1.7,1.9,0);
	ctrol_r.push_back(t);
	t.set(2,0,0);
	ctrol_r.push_back(t);
	t.set(1.7,-1.8,0);
	ctrol_r.push_back(t);
	t.set(0,-2,0);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);
	ctrol_r.push_back(t);

	curva.setFactor(2);
	curva.Bspline(ctrol_r,curva_r);

	t.set(0,1,0);
	Vertice q;
	Superficie* sup = new SuperficieRevolucion(curva_r, 180, q,t) ;
	sup->aplicarTextura("stones.bmp");
	sup->getMaterial()->setSpecular(0,0.1,0.5,1);
	sup->getMaterial()->setDiffuse(0.5,0.5,0.5,1);
	sup->getMaterial()->setAmbient(0.1,0.1,0.1,1);
	sup->getMaterial()->setShininess(50);
	sup->setCullFace(GL_BACK);

	return sup;

}

Cardumen* ContenedorObjetos::crearCardumen0(){

	//puntos control trayecto
	std::vector<Vertice> control;
	Vertice t;
	t.set(0,100,10);
	control.push_back(t);
	t.set(-30,100,15);
	control.push_back(t);
	t.set(-30,50,10);
	control.push_back(t);
	t.set(-50,50,10);
	control.push_back(t);
	t.set(-50,60,10);
	control.push_back(t);
	t.set(-50,70,10);
	control.push_back(t);
	t.set(-100,100,10);
	control.push_back(t);
	t.set(-100,50,30);
	control.push_back(t);
	t.set(-30,0,10);
	control.push_back(t);
	t.set(-50,-50,20);
	control.push_back(t);
	t.set(-100,-50,15);
	control.push_back(t);
	t.set(-100,-100,30);
	control.push_back(t);
	t.set(-50,-100,19);
	control.push_back(t);
	t.set(-50,-50,10);
	control.push_back(t);
	t.set(0,-10,15);
	control.push_back(t);
	t.set(50,-50,10);
	control.push_back(t);
	t.set(50,-100,15);
	control.push_back(t);
	t.set(100,-100,10);
	control.push_back(t);
	t.set(100,-50,15);
	control.push_back(t);
	t.set(50,-50,10);
	control.push_back(t);
	t.set(15,0,10);
	control.push_back(t);
	t.set(50,50,15);
	control.push_back(t);
	t.set(100,50,10);
	control.push_back(t);
	t.set(100,100,10);
	control.push_back(t);
	t.set(70,100,10);
	control.push_back(t);
	t.set(60,70,10);
	control.push_back(t);
	t.set(50,50,15);
	control.push_back(t);
	t.set(50,70,10);
	control.push_back(t);
	t.set(30,100,10);
	control.push_back(t);
	t.set(0,100,10);
	control.push_back(t);
	t.set(-30,100,15);
	control.push_back(t);
	t.set(-30,50,10);
	control.push_back(t);

	Cardumen* card = new Cardumen(PEZ0,CANT_PLATEADO,control,true,20,false);
	card->recorrido->setColor(1,1,0);
	return card;

}

Cardumen* ContenedorObjetos::crearCardumen1(){

	//puntos control trayecto
	std::vector<Vertice> control;
	Vertice t;
	t.set(90,90,20);
	control.push_back(t);
	t.set(90,50,20);
	control.push_back(t);
	t.set(30,30,50);
	control.push_back(t);
	t.set(0,10,40);
	control.push_back(t);
	t.set(100,0,70);
	control.push_back(t);
	t.set(100,-120,60);
	control.push_back(t);
	t.set(50,-70,30);
	control.push_back(t);
	t.set(10,10,30);
	control.push_back(t);
	t.set(-50,-40,60);
	control.push_back(t);
	t.set(-102,-52,20);
	control.push_back(t);
	t.set(50,0,30);
	control.push_back(t);
	t.set(40,42,25);
	control.push_back(t);
	t.set(80,90,20);
	control.push_back(t);
	t.set(90,97,20);
	control.push_back(t);
	t.set(90,90,20);
	control.push_back(t);
	t.set(90,50,20);
	control.push_back(t);
	t.set(30,30,50);
	control.push_back(t);


	Cardumen* cardumen1 = new Cardumen(PEZ1,CANT_DORI,control,true,20,false);
	cardumen1->recorrido->setColor(0.1,0.1,1);
	return cardumen1;
}

Cardumen* ContenedorObjetos::crearCardumen2(){

	//puntos control trayecto
	std::vector<Vertice> control;
	Vertice t;
	t.set(-110,-60,55);
	control.push_back(t);
	t.set(-110,0,55);
	control.push_back(t);
	t.set(-90,60,40);
	control.push_back(t);
	t.set(-45,30,20);
	control.push_back(t);
	t.set(0,0,10);
	control.push_back(t);
	t.set(20,-25,10);
	control.push_back(t);
	t.set(-40,-35,30);
	control.push_back(t);
	t.set(-60,-45,40);
	control.push_back(t);
	t.set(90,-60,60);
	control.push_back(t);
	t.set(110,0,50);
	control.push_back(t);
	t.set(90,60,30);
	control.push_back(t);
	t.set(45,-30,50);
	control.push_back(t);
	t.set(0,0,100);
	control.push_back(t);
	t.set(-45,-40,80);
	control.push_back(t);
	t.set(-110,-75,55);
	control.push_back(t);
	t.set(-110,-62,55);
	control.push_back(t);
	t.set(-110,-60,55);
	control.push_back(t);
	t.set(-110,0,55);
	control.push_back(t);
	t.set(-90,60,40);
	control.push_back(t);

	Cardumen* cardumen1 = new Cardumen(PEZ2,CANT_KOI,control,true,20,false);
	cardumen1->recorrido->setColor(1,0.4,0.1);
	return cardumen1;
}

void ContenedorObjetos::crearAgua() {
	handle_agua = glGenLists(1);

	Material mat_agua;
	mat_agua.setSpecular(0,0,0,0);
	mat_agua.setAmbient(0,0.05,0.1,1);
	mat_agua.setDiffuse(0.1,0.2,0.3,1);
	mat_agua.setShininess(0);

	idTexAgua = ContenedorTexturas::getInstancia()->cargarImagen("ocean.jpg");

	glNewList(handle_agua, GL_COMPILE);

		glFrontFace( GL_CCW );
		glCullFace( GL_FRONT );
		glEnable(GL_CULL_FACE);
		mat_agua.usarMaterial();

		glBegin(GL_QUADS);
			glNormal3f(0,0,-1);
			glTexCoord2f(0,0);
			glVertex3f(CX_INF,CY_INF,CZ_SUP);
			glTexCoord2f(1,0);
			glVertex3f(CX_SUP,CY_INF,CZ_SUP);
			glTexCoord2f(1,1);
			glVertex3f(CX_SUP,CY_SUP,CZ_SUP);
			glTexCoord2f(0,1);
			glVertex3f(CX_INF,CY_SUP,CZ_SUP);
		glEnd();

		glDisable( GL_CULL_FACE );
	glEndList();
}

void ContenedorObjetos::dibujarAgua(unsigned int render_mode) {

	if (render_mode == GL_TEXTURE){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindTexture(GL_TEXTURE_2D, idTexAgua);
		glEnable(GL_TEXTURE_2D);
			glCallList(handle_agua);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, render_mode);
		glCallList(handle_agua);
	}
}

void ContenedorObjetos::dibujarCardumen(Cardumen* car, unsigned int render_mode) {

		/* calculo el angulo de rotacion. */
		Vertice dir = car->recorrido->getDireccion();

		double ang_x=0, alfa=0;
		Vertice p(dir.x,dir.y,0);
		ang_x = acos(p.modulo()/dir.modulo())*180/PI;
		if(dir.z<0)
			ang_x = (-ang_x);
		if(dir.y != 0)
			alfa = atan2(dir.x,dir.y) * 180 / PI;
		else {
			(dir.x > 0) ? alfa = 90 : alfa = (-90);
		}

		glEnable(GL_RESCALE_NORMAL);	//habilito el reescalado de normales

		Vertice pos;
		Vertice pos_c = car->recorrido->getPosicion();

		for (uint i=0; i < car->cantidad; i++){
			glPushMatrix();
				pos = car->ubicacion[i];
				glTranslatef(pos_c.x + pos.x,pos_c.y + pos.y,pos_c.z + pos.z);	//ubico al objeto en su posicion dentro del cardumen, sobre la tray
				glRotatef(alfa,0,0,-1); 	//oriento al pez
				glRotatef(ang_x,1,0,0);
				dibujarPez(car->IDobjeto, render_mode, car->volumen[i]);
			glPopMatrix();
		}

		glDisable(GL_RESCALE_NORMAL);
}

ContenedorObjetos* ContenedorObjetos::getInstancia(){
	if (!instancia) {
		instancia = new ContenedorObjetos();
	}
	return instancia;
}

Animacion* ContenedorObjetos::getAnimacion(unsigned int id) {
	if (id < MAX_ANIMACIONES)
		return animaciones[id];
	return 0;
}

Cardumen* ContenedorObjetos::getCardumen(unsigned int id) {
	if (id < MAX_CARDUMEN)
		return cardumen[id];
	return 0;
}

void ContenedorObjetos::dibujarPez(uint id, uint render_mode, float escala) {

	glPushMatrix();
		glEnable(GL_CULL_FACE);
		if (id==PEZ2)
			glScalef(escala,escala,escala*0.8);	//"achato" el pez koi
		else
			glScalef(escala,escala,escala);		//reescalo el objeto
		cuerpos[id]->dibujar(render_mode);
		glDisable( GL_CULL_FACE );
	glPopMatrix();

	glPushMatrix();
		glTranslatef(longitud[id].x*escala,0.2*escala,0);
		glScalef(escala,escala,escala);
		aletas[id]->dibujar(render_mode);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-longitud[id].x*escala,0.2*escala,0);
		glScalef(-escala,escala,escala); //"espejada" respecto del plano YZ
		aletas[id]->dibujar(render_mode);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,longitud[id].y*escala,0);
		glScalef(escala,escala,escala);
		colas[id]->dibujar(render_mode);
	glPopMatrix();

	if(id == PEZ2){		//el pez koi tiene cosas "extra"
		glPushMatrix();
			glTranslatef(0,0,0.7*escala);
			glRotatef(-90,1,0,0);
				//cambio la orientacion
			glScalef(-escala,escala,escala);
			aletas[id]->dibujar(render_mode);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,0.4*escala,0.7*escala);
			glRotatef(-90,1,0,0);
				//cambio la orientacion
			glScalef(escala,escala,escala);
			aletas[id]->dibujar(render_mode);
		glPopMatrix();

		glPushMatrix();
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		glEnable(GL_CULL_FACE);
			glTranslatef(0.20*escala,1.85*escala,0.1*escala);
			glScalef(escala,escala,escala);
			animaciones[BIGOTE]->dibujar(render_mode);
		glDisable(GL_CULL_FACE);
		glPopMatrix();
		glPushMatrix();
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
		glEnable(GL_CULL_FACE);
			glTranslatef(-0.20*escala,1.85*escala,0.1*escala);
			glScalef(-escala,escala,escala);
			animaciones[BIGOTE]->dibujar(render_mode);
		glDisable(GL_CULL_FACE);
		glPopMatrix();
	}
}

