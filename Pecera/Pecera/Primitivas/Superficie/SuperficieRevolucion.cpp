#include "SuperficieRevolucion.h"

SuperficieRevolucion::SuperficieRevolucion(std::vector<Vertice> &forma, float angulo) {

	tam = forma.size(); //guardo la long de la curva patron
	pasos = 100;
	//guardo la malla de vertices de la superficie formada
	Vertice v;

	//aplico rotacion
	for(unsigned int i=0; i < pasos; i++ ) {
		for(unsigned int pos=0 ; pos <  tam ; pos++) {
//			v.x = forma[pos].x + trasl[i].x;
//			v.y = forma[pos].y + trasl[i].y;
//			v.z = forma[pos].z + trasl[i].z;
//			superficie.push_back(v);
		}
	}
//calculo de normales


}

SuperficieRevolucion::~SuperficieRevolucion() {
	// TODO Auto-generated destructor stub
}
