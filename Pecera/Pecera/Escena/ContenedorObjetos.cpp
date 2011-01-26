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

void ContenedorObjetos::crearEscenario() {
	textura[0].cargarImagen("escenario1.bmp");
	textura[1].cargarImagen("escenario2.bmp");
	textura[2].cargarImagen("escenario3.bmp");
	textura[3].cargarImagen("escenario4.bmp");
	textura[4].cargarImagen("escenario5.bmp");
	textura[5].cargarImagen("escenario6.bmp");
	textura[6].cargarImagen("escenario7.bmp");
	textura[7].cargarImagen("escenario8.bmp");
}

void ContenedorObjetos::dibujarEscenario(unsigned int render_mode) {

//	glFrontFace( GL_CCW );
//	glCullFace( GL_BACK );
//	//glEnable(GL_CULL_FACE);
//
//	static GLfloat cubo[24]={CX_INF,CY_INF,CZ_INF , CX_INF,CY_INF,CZ_SUP ,
//							 CX_SUP,CY_INF,CZ_SUP , CX_SUP,CY_INF,CZ_INF ,
//							 CX_SUP,CY_SUP,CZ_INF , CX_SUP,CY_SUP,CZ_SUP ,
//							 CX_INF,CY_SUP,CZ_SUP , CX_INF,CY_SUP,CZ_INF};
//
//	static GLshort idx[24] = { 0,1,2,3, 0,3,4,7, 2,5,4,3, 5,6,7,3, 0,7,6,1, 1,6,5,2 };
//
//	static GLfloat texCoord[8] = { 0,0, 0,1, 1,1, 1,0 };
//
//	glEnableClientState (GL_VERTEX_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, cubo);
//
//	for (unsigned int i=0; i<6; i++){
//
//		//Render Mode
//		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
//		if ((render_mode == GL_TEXTURE) && (textura[i].tieneTextura())) {  	//TODO no anda
//				glBindTexture(GL_TEXTURE_2D,textura[i].getID());
//				glEnable(GL_TEXTURE);
//				glEnableClientState(GL_TEXTURE_2D_ARRAY);
//				glTexCoordPointer(2,GL_FLOAT,0, texCoord);
//		}
//		if (render_mode == GL_LINE) {
//			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
//		}
//
//		//dibujar
//		glDrawElements(GL_QUADS, 4, GL_SHORT, &(idx[i*4]));
//
//
//	//desactivar estados
//		glDisableClientState (GL_VERTEX_ARRAY);
//		if ((render_mode == GL_TEXTURE) && textura[i].tieneTextura()) {
//			glDisableClientState(GL_TEXTURE_2D_ARRAY);
//			glDisable(GL_TEXTURE);
//		}
//	}
//	glDisable( GL_CULL_FACE );
	glShadeModel (GL_FLAT);

	glFrontFace( GL_CCW );
	glCullFace( GL_BACK );
	glEnable(GL_CULL_FACE);

	glColor3f(0.92,0.5,0.51);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	static GLfloat cubo[24]={CX_INF,CY_INF,CZ_INF , CX_INF,CY_INF,CZ_SUP ,
							 CX_SUP,CY_INF,CZ_SUP , CX_SUP,CY_INF,CZ_INF ,
							 CX_SUP,CY_SUP,CZ_INF , CX_SUP,CY_SUP,CZ_SUP ,
							 CX_INF,CY_SUP,CZ_SUP , CX_INF,CY_SUP,CZ_INF};

	static GLfloat norm[18]={ 0,1,0, 0,0,1, -1,0,0, 0,-1,0, 1,0,0, 0,0,-1};

	static GLshort idx[24] = { 0,1,2,3, 0,3,4,7, 2,5,4,3, 5,6,7,4, 0,7,6,1, 1,6,5,2 };

	//static GLfloat texCoord[8] = { 0,0, 0,1, 1,1, 1,0 };

	if ( render_mode == GL_LINE)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);


	for (unsigned int i=0; i<24; i+=4){
		glBegin(GL_QUADS);

		glNormal3f(norm[(i/4)*3],norm[(i/4)*3 + 1],norm[(i/4)*3 +2 ]);

		if ((render_mode == GL_TEXTURE) && textura[i/4].tieneTextura() ) {
			glBindTexture(GL_TEXTURE_2D, textura[i/4].getID());
			glEnable(GL_TEXTURE);

			glTexCoord2f(0,0);
			glVertex3f(cubo[idx[i  ]*3],cubo[idx[i  ]*3+1],cubo[idx[i  ]*3+2]);
			glTexCoord2f(1,0);
			glVertex3f(cubo[idx[i+1]*3],cubo[idx[i+1]*3+1],cubo[idx[i+1]*3+2]);
			glTexCoord2f(1,1);
			glVertex3f(cubo[idx[i+2]*3],cubo[idx[i+2]*3+1],cubo[idx[i+2]*3+2]);
			glTexCoord2f(0,1);
			glVertex3f(cubo[idx[i+3]*3],cubo[idx[i+3]*3+1],cubo[idx[i+3]*3+2]);

			glDisable(GL_TEXTURE);
		}
		else{
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

