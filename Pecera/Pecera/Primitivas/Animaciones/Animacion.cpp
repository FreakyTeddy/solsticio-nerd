#include "Animacion.h"
#include "../Curva/Curva.h"
#include "../Superficie/SuperficieBarrido.h"

Animacion::Animacion(std::vector<Vertice> &forma, std::vector<Vertice> &trasl_inicial, std::vector<Vertice> &trasl_final, std::vector<Vertice> &defo, u_int intervalo=4) {

	//interpolo con bspline los puntos de la traslacion
	Curva c;
	c.setFactor(intervalo);

	std::vector<Vertice>temp, res;	//vectores temporales
	std::vector<Vertice> *control = 0;
	bool first = true;

	for (size_t i=0; i < trasl_inicial.size(); i++) {
		temp.clear();
		res.clear();
		temp.push_back(trasl_inicial[i]);
		temp.push_back(trasl_inicial[i]);
		temp.push_back(trasl_inicial[i]);
		temp.push_back(trasl_final[i]);
		temp.push_back(trasl_final[i]);
		temp.push_back(trasl_final[i]);
		c.Bspline(temp,res);
		if (first) {
			control = new std::vector<Vertice>[res.size()];
			first = false;
		}

		for (size_t j=0; j<res.size(); j++){	//--> PUAJ!!!!!!!!! por suerte se supone que son pocos puntos
			control[j].push_back(res[j]);
		}

	}

	//inicializo la animacion
	f_cant = res.size();	//WARNING! todas las bspline deben dar la misma cant de frames
	f_act = 0;
	f_next = (f_cant != 0);
	m_ciclico = true;

	frame = new Superficie* [f_cant];
	//creo una superficie de barrido por cada frame
	for (u_short i=0; i < f_cant; i++) {
		frame[i] = new SuperficieBarrido(forma, control[i], defo);
	}

	delete[] control; //VER!!
}

Animacion::Animacion(std::vector<Vertice> &forma, std::vector<Vertice> &trasl, std::vector<Vertice> &defo,Vertice &dir, uint inicio, uint cant_frames, bool ciclico) {
	f_act = 0;
	f_next = (f_cant != 0);
	f_cant = cant_frames;
	m_ciclico = ciclico;

	frame = new Superficie* [f_cant];

	std::vector<Vertice> temp;
	Vertice v,d;

	double fase = 2 * PI / f_cant;
	double despl = 0;
	for (uint i=0; i<f_cant; i++){	//desplazo cada animacion en una fase
		temp.clear();

		for (uint k=0; k<inicio ; k++) //salteo los primeros puntos
			temp.push_back(trasl[k]);

		despl=0;

		//aplico la funcion senoidal al resto de los puntos
		for (uint j=inicio; j<trasl.size(); j++){
			despl+=fabs(trasl[j].z-trasl[j-1].z);
			d = dir * (j-inicio+1)*sin(fase*i+despl)/trasl.size();
			v.set(trasl[j].x + d.x, trasl[j].y + d.y, trasl[j].z + d.z);

			temp.push_back(v);
		}
		frame[i] = new SuperficieBarrido(forma, temp, defo,true);
	}
}


Animacion::~Animacion() {
	for (u_short i=0; i < f_cant; i++) {
		delete frame[i];
	}
	delete[] frame;
}

void Animacion::setModoTransicion(bool ciclico) {
	m_ciclico = ciclico;
}

void Animacion::animaryDibujar(unsigned int render_mode) {
	frame[f_act]->dibujar(render_mode);
	animar();
}

void Animacion::animar() {
	if (m_ciclico)
		(f_act < f_cant-1) ? f_act++ : f_act=0;
	else {
		f_act += f_next;
		if ((f_act == 0) || (f_act == f_cant-1))
			f_next = (-f_next);
	}
}

void Animacion::animar(u_short &f_num, short &f_int, bool modo) {
	if (modo)
		(f_num < f_cant-1) ? f_num++ : f_num=0;
	else {
		f_num += f_int;
		if ((f_num == 0) || (f_num == f_cant-1))
			f_int = (-f_int);
	}
}

void Animacion::dibujar(unsigned int render_mode) {
	frame[f_act]->dibujar(render_mode);
}

void Animacion::dibujar(unsigned int render_mode, u_short f_num) {
	frame[f_num]->dibujar(render_mode);
}

void Animacion::setTextura(std::string name) {
	for (u_short i=0; i < f_cant; i++)
		frame[i]->aplicarTextura(name);
}

void Animacion::setMaterial(Material &m) {
	for (u_short i=0; i < f_cant; i++)
		frame[i]->setMaterial(m);
}

