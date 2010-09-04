#include "SuperficieBarrido.h"
#include <iostream>

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl) {

	tam = forma.size(); //guardo la long de la curva patron

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

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl, std::vector<float> defo) {

	tam = forma.size(); //guardo la long de la curva patron

	//guardo la malla de vertices de la superficie formada y aplico traslacion
	Vertice v;

	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v = forma[pos] * defo[pos] + trasl[i];
			superficie.push_back(v);
		}
	}
	
	init();
}



SuperficieBarrido::~SuperficieBarrido() {}

