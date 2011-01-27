#include "ContenedorObjetos.h"

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
	crearEscenario();
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

void ContenedorObjetos::crearEscenario() {
	textura[0].cargarImagen("pared_neg_y.jpg");
	textura[1].cargarImagen("pared_piso.jpg");
	textura[2].cargarImagen("pared_pos_x.jpg");
	textura[3].cargarImagen("pared_pos_y.jpg");
	textura[4].cargarImagen("pared_neg_x.jpg");
	textura[5].cargarImagen("pared_techo.jpg");
}

void ContenedorObjetos::dibujarEscenario(unsigned int render_mode) {

	glShadeModel (GL_FLAT);

	glFrontFace( GL_CCW );
	glCullFace( GL_BACK );
	glEnable(GL_CULL_FACE);

	mat_escenario.usarMaterial();

	glDisable(GL_LIGHTING);

	static GLfloat cubo[24]={CX_INF,CY_INF,CZ_INF , CX_INF,CY_INF,CZ_SUP ,
							 CX_SUP,CY_INF,CZ_SUP , CX_SUP,CY_INF,CZ_INF ,
							 CX_SUP,CY_SUP,CZ_INF , CX_SUP,CY_SUP,CZ_SUP ,
							 CX_INF,CY_SUP,CZ_SUP , CX_INF,CY_SUP,CZ_INF};

//	static GLfloat norm[18]={ 0,1,0, 0,0,1, -1,0,0, 0,-1,0, 1,0,0, 0,0,-1};

	static GLshort idx[24] = { 0,1,2,3, 0,3,4,7, 2,5,4,3, 5,6,7,4, 0,7,6,1, 1,6,5,2 };

	if ( render_mode == GL_LINE)
		glPolygonMode( GL_FRONT, GL_LINE);
	else
		glPolygonMode( GL_FRONT, GL_FILL);


	for (unsigned int i=0; i<24; i+=4){

		if ((render_mode == GL_TEXTURE) && textura[i/4].tieneTextura() ) {

			glBindTexture(GL_TEXTURE_2D, textura[i/4].getID());
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);

			glTexCoord2f(0.0,0.0);
			glVertex3f(cubo[idx[i  ]*3],cubo[idx[i  ]*3+1],cubo[idx[i  ]*3+2]);
			glTexCoord2f(1.0,0.0);
			glVertex3f(cubo[idx[i+1]*3],cubo[idx[i+1]*3+1],cubo[idx[i+1]*3+2]);
			glTexCoord2f(1.0,1.0);
			glVertex3f(cubo[idx[i+2]*3],cubo[idx[i+2]*3+1],cubo[idx[i+2]*3+2]);
			glTexCoord2f(0.0,1.0);
			glVertex3f(cubo[idx[i+3]*3],cubo[idx[i+3]*3+1],cubo[idx[i+3]*3+2]);

			glDisable(GL_TEXTURE_2D);
		}
		else{
			glBegin(GL_QUADS);
			glVertex3f(cubo[idx[i  ]*3],cubo[idx[i  ]*3+1],cubo[idx[i  ]*3+2]);
			glVertex3f(cubo[idx[i+1]*3],cubo[idx[i+1]*3+1],cubo[idx[i+1]*3+2]);
			glVertex3f(cubo[idx[i+2]*3],cubo[idx[i+2]*3+1],cubo[idx[i+2]*3+2]);
			glVertex3f(cubo[idx[i+3]*3],cubo[idx[i+3]*3+1],cubo[idx[i+3]*3+2]);
		}

		glEnd();
	}
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glDisable( GL_CULL_FACE );

	glShadeModel (GL_SMOOTH);

}

