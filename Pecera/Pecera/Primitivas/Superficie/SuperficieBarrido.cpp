#include "SuperficieBarrido.h"

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl, bool borrar) {

	tam = forma.size(); //guardo la long de la curva patron
	cerrada = false;
	//guardo la malla de vertices de la superficie formada y aplico traslacion
	Vertice v;

	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v = forma[pos] + trasl[i];
			superficie.push_back(v);
		}
	}
	keep = !borrar;
	init();
}

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl, std::vector<Vertice> &defo, bool borrar) {

	tam = forma.size(); //guardo la long de la curva patron
	cerrada = false;
	//guardo la malla de vertices de la superficie formada y aplico traslacion
	Vertice v;

	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v = forma[pos] * defo[i] + trasl[i];
			superficie.push_back(v);
		}
	}
	keep = !borrar;
	init();
}



SuperficieBarrido::~SuperficieBarrido() {
	glDeleteLists(dl_handle, 2);
}

