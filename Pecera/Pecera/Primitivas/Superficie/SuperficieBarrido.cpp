#include "SuperficieBarrido.h"
#include <iostream>
SuperficieBarrido::SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl) {

	tam = forma.size(); //guardo la long de la curva patron

	//guardo la malla de vertices de la superficie formada
	Vertice v;

	//aplico traslacion
	for(unsigned int i=0; i < trasl.size(); i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			v.x = forma[pos].x + trasl[i].x;
			v.y = forma[pos].y + trasl[i].y;
			v.z = forma[pos].z + trasl[i].z;
			superficie.push_back(v);
		}
	}
//calculo de normales


}

SuperficieBarrido::~SuperficieBarrido() {
	// TODO Auto-generated destructor stub
}


