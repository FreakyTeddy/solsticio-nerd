#include "ContenedorObjetos.h"
//#include <GL/glu.h>

ContenedorObjetos* ContenedorObjetos::instancia=0;

ContenedorObjetos::ContenedorObjetos() {
	//creo todas las superficies dibujables
	crearSuperficies();
	crearAnimaciones();
	crearCardumenes();
	crearBurbuja();
}

ContenedorObjetos::~ContenedorObjetos() {
//	for (int i=0; i < MAX_DIBUJOS; i++)
//		delete superficies[i];	TODO
//	for (int i=0; i < MAX_ANIMACIONES; i++)
//		delete animaciones[i];
//	for (int i=0; i < MAX_CARDUMEN; i++)
//		delete cardumen[i];
	delete superficies[ALGA2];
	delete superficies[ALGA1];
	delete superficies[FLORERO];
	delete animaciones[0];
	delete cardumen[0];
	delete tray_burbujas;
	glDeleteLists(handle_burbuja, 2);
}

void ContenedorObjetos::dibujarObjeto(unsigned int id, unsigned int render_mode) {
	if (id < MAX_DIBUJOS)
		superficies[id]->dibujar(render_mode);
	else{
		if (id == BURBUJA){
			if (render_mode == GL_LINE)
				glCallList(handle_burbuja);
			else
				glCallList(handle_burbuja+1);
		}else
		std::cout<<"id de dibujo inválido: "<<id<<" . Máximo: "<<MAX_DIBUJOS<<std::endl;
	}

}

void ContenedorObjetos::crearSuperficies() {

	//todo rellenar los otros espacios del vector
	superficies[FLORERO] = crearFlorero();
	superficies[ALGA1] = crearAlga1();
	superficies[ALGA2] = crearAlga2();
//	superficies[ROCA1] = crearRoca1();
	crearEscenario();
}

void ContenedorObjetos::crearAnimaciones() {
	animaciones[0] = crearAlga3();
}

void ContenedorObjetos::crearCardumenes() {
	cardumen[0] = crearCardumen1();
}

void ContenedorObjetos::crearBurbuja() {
	handle_burbuja = glGenLists(2);

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	Material m;
	m.setDiffuse(0.85,0.85,0.96,0.3);
	m.setAmbient(0.15,0.15,0.6,0.3);
	m.setSpecular(1,1,1,0);
	m.setShininess(170);

	/* sin transparencia, con lineas */
	glNewList(handle_burbuja, GL_COMPILE);

		m.usarMaterial();
	    gluQuadricDrawStyle(qobj, GLU_LINE);
	    gluQuadricNormals(qobj, GLU_SMOOTH);
		gluSphere(qobj, 1, 15, 10);


	glEndList();

	/* con transparencia y con relleno*/
	glNewList(handle_burbuja+1, GL_COMPILE);

		glEnable(GL_BLEND);
			m.usarMaterial();
		    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//transparencia
		    gluQuadricDrawStyle(qobj, GLU_FILL);
		    gluQuadricNormals(qobj, GLU_SMOOTH);
			gluSphere(qobj, 0.75, 15, 10);
		glDisable(GL_BLEND);

	glEndList();

	gluDeleteQuadric(qobj);

	/* trayectoria que seguira la burbuja */
	std::vector<Vertice> puntos;
	Vertice v;
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10)/5;
	v.y += (float)(rand()%20 - 10)/5;
	v.z += 4;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10)/5;
	v.y += (float)(rand()%20 - 10)/5;
	v.z += 6;
	puntos.push_back(v);
	v.x += (float)(rand()%20 - 10)/5;
	v.y += (float)(rand()%20 - 10)/5;
	v.z += 10;
	puntos.push_back(v);
	puntos.push_back(v);
	puntos.push_back(v);
	tray_burbujas = new Trayectoria(puntos,false,6,false);
}

Superficie* ContenedorObjetos::crearFlorero() {

	curva.setFactor(5);
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
	t.set(-1,0,0); //con arena
//	t.set(0,0,0);
	Vertice q(0,0,1);
	Superficie* florero = new SuperficieRevolucion(vertb, -360,t,q,36);
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
	sup->getMaterial()->setDiffuse(0,1,0.5,1);
	sup->getMaterial()->setSpecular(0,1,1,1);
	sup->getMaterial()->setShininess(50);
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
	sup->getMaterial()->setDiffuse(0,1,0.5,1);
	sup->getMaterial()->setSpecular(0,0.5,0.5,1);
	sup->getMaterial()->setShininess(50);
	sup->aplicarTextura("madera.bmp");
	return sup;
}

Animacion* ContenedorObjetos::crearAlga3() {
	std::vector<Vertice> v1, v2;
	std::vector<Vertice> trasl;
	Vertice q;

	//puntos de control
	std::vector<Vertice> alga_s;

	q.set(0.5,0,0);
	alga_s.push_back(q);
	q.set(-0.5,0,0);
	alga_s.push_back(q);

	//traslacion inicial de los puntos
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
	curva.Bspline(trasl, v1);

	//traslacion final de los puntos
	trasl.clear();
	q.set(0,0,0);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);

	q.set(-0.2,0.5,1);
	trasl.push_back(q);

	q.set(-0.75,0.75,3);
	trasl.push_back(q);

	q.set(-1.5,1.5,4);
	trasl.push_back(q);

	q.set(-2,2,3);
	trasl.push_back(q);

	q.set(-1.5,1.5,2.5);
	trasl.push_back(q);
	trasl.push_back(q);
	trasl.push_back(q);
	curva.Bspline(trasl, v2);

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
	Animacion *ani = new Animacion(alga_s,v1,v2,def2,4);
	Material m;
	m.setDiffuse(0,1,0.5,1);
	m.setSpecular(0,0.5,0.5,1);
	m.setShininess(50);
	ani->setTextura("madera.bmp");
	ani->setMaterial(m);
	return ani;
}


Superficie* ContenedorObjetos::crearRoca1(){
//	std::vector<Vertice> v;
//	Vertice q;
//	v.push_back(q);
//	q.set(0,0,0);
//	v.push_back(q);
//	q.set(0,1,0);
//	v.push_back(q);
//	q.set(0,1,1);
//	v.push_back(q);
//	q.set(0,0,1);
//	v.push_back(q);
//	Superficie* s= new Superficie(v);
//	s->aplicarTextura("stones.bmp");
//	return s;
return 0;
}

Cardumen* ContenedorObjetos::crearCardumen1(){

	//puntos control trayecto
	std::vector<Vertice> control;
	Vertice t;
	control.push_back(t);
	control.push_back(t);
	control.push_back(t);
	t.set(30,12,0);
	control.push_back(t);
	t.set(5,-12,24);
	control.push_back(t);
	t.set(-32,-52,36);
	control.push_back(t);
	t.set(0,0,0);
	control.push_back(t);
	control.push_back(t);
	control.push_back(t);


	Cardumen* cardumen1 = new Cardumen(FLORERO,1,control,true,6,false);
	return cardumen1;
}

void ContenedorObjetos::crearEscenario() {
	textura[0].cargarImagen("pared_neg_y.jpg");
	textura[1].cargarImagen("pared_pos_x.jpg");
	textura[2].cargarImagen("pared_pos_y.jpg");
	textura[3].cargarImagen("pared_neg_x.jpg");
	textura[4].cargarImagen("pared_techo.jpg");
	mat_escenario.setSpecular(0,0,0,0);
	mat_escenario.setAmbient(1,1,1,1);
	mat_escenario.setDiffuse(1,1,1,1);
	mat_escenario.setShininess(0);
}

void ContenedorObjetos::dibujarEscenario(unsigned int render_mode) {

	glFrontFace( GL_CCW );
	glCullFace( GL_BACK );
	glEnable(GL_CULL_FACE);

	mat_escenario.usarMaterial();

	static GLfloat cubo[24]={CX_INF,CY_INF,CZ_INF , CX_INF,CY_INF,CZ_SUP ,
							 CX_SUP,CY_INF,CZ_SUP , CX_SUP,CY_INF,CZ_INF ,
							 CX_SUP,CY_SUP,CZ_INF , CX_SUP,CY_SUP,CZ_SUP ,
							 CX_INF,CY_SUP,CZ_SUP , CX_INF,CY_SUP,CZ_INF};

	static GLfloat norm[15]={ 0,1,0, -1,0,0, 0,-1,0, 1,0,0, 0,0,-1};

	static GLshort idx[20] = { 0,1,2,3, 2,5,4,3, 5,6,7,4, 0,7,6,1, 1,6,5,2 };

	if ( render_mode == GL_LINE)
		glPolygonMode( GL_FRONT, GL_LINE);
	else
		glPolygonMode( GL_FRONT, GL_FILL);


	for (unsigned int i=0, j=0; i<20; i+=4, j++){

		if ((render_mode == GL_TEXTURE) && textura[j].tieneTextura() ) {

			glBindTexture(GL_TEXTURE_2D, textura[j].getID());
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);

				glNormal3fv(&norm[j]);
				glTexCoord2f(0.0,0.0);
				glVertex3f(cubo[idx[i  ]*3],cubo[idx[i  ]*3+1],cubo[idx[i  ]*3+2]);
				glTexCoord2f(1.0,0.0);
				glVertex3f(cubo[idx[i+1]*3],cubo[idx[i+1]*3+1],cubo[idx[i+1]*3+2]);
				glTexCoord2f(1.0,1.0);
				glVertex3f(cubo[idx[i+2]*3],cubo[idx[i+2]*3+1],cubo[idx[i+2]*3+2]);
				glTexCoord2f(0.0,1.0);
				glVertex3f(cubo[idx[i+3]*3],cubo[idx[i+3]*3+1],cubo[idx[i+3]*3+2]);

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glBegin(GL_QUADS);
				glNormal3fv(&norm[j]);
				glVertex3f(cubo[idx[i  ]*3],cubo[idx[i  ]*3+1],cubo[idx[i  ]*3+2]);
				glVertex3f(cubo[idx[i+1]*3],cubo[idx[i+1]*3+1],cubo[idx[i+1]*3+2]);
				glVertex3f(cubo[idx[i+2]*3],cubo[idx[i+2]*3+1],cubo[idx[i+2]*3+2]);
				glVertex3f(cubo[idx[i+3]*3],cubo[idx[i+3]*3+1],cubo[idx[i+3]*3+2]);
			glEnd();
		}


	}
	glDisable( GL_CULL_FACE );

}

void ContenedorObjetos::dibujarCardumen(Cardumen* car, unsigned int render_mode) {
	glPushMatrix();

		float escala;
		Vertice pos = car->recorrido->getPosicion();

		glTranslatef(pos.x, pos.y, pos.z);	//ubico al cardumen en su trayectoria

		//TODO!!! tendrian que rotar para mirar siempre hacia adelante!

		glEnable(GL_RESCALE_NORMAL);	//habilito el reescalado de normales

		for (uint i=0; i < car->cantidad; i++){

			glPushMatrix();
				pos = car->ubicacion[i];
				escala = car->volumen[i];
				glTranslatef(pos.x, pos.y, pos.z);	//ubico al objeto en su posicion dentro del cardumen
				glScalef(escala,escala,escala);		//reesccalo el objeto
				dibujarObjeto(car->IDobjeto, render_mode);
			glPopMatrix();
		}

		glDisable(GL_RESCALE_NORMAL);

	glPopMatrix();
}




ContenedorObjetos* ContenedorObjetos::getInstancia(){
	if (!instancia)
		instancia = new ContenedorObjetos();
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



