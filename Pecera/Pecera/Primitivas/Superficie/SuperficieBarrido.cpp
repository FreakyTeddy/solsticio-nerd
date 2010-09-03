#include "SuperficieBarrido.h"
#include <iostream>

SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl) {

	tam = forma.size(); //guardo la long de la curva patron

	//guardo la malla de vertices de la superficie formada
	Vertice v;

	//aplico traslacion
	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v = forma[pos] + trasl[i];
			superficie.push_back(v);
		}
	}

	//seteo los indices de dibujado
	setIndices();

//calculo de normales y texturas


}

SuperficieBarrido::~SuperficieBarrido() {
	// TODO Auto-generated destructor stub
}
