#include "SuperficieBarrido.h"

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl) {

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
	
	init();
}

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl, std::vector<Vertice> &defo) {

	tam = forma.size(); //guardo la long de la curva patron
	cerrada = false;
	//guardo la malla de vertices de la superficie formada y aplico traslacion
	Vertice v;

	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v = forma[pos] * defo[i] + trasl[i];
			v.print();
			superficie.push_back(v);
		}
		std::cout<<std::endl;
	}
	
	init();
}



SuperficieBarrido::~SuperficieBarrido() {}

