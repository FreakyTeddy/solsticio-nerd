#include "SuperficieRevolucion.h"
#include "../rotacion_3d.h"
#include <math.h>


SuperficieRevolucion::SuperficieRevolucion(std::vector<Vertice> &forma, float angulo, Vertice eje1, Vertice eje2, uint pasos, bool borrar) {

	tam = forma.size(); //guardo la long de la curva patron
	cerrada = !((int)angulo%360);

	//aplico rotacion

	for (uint i=0; i<=pasos; i++) {
		Rotacion3d rot(eje1,eje2, -angulo*i/pasos);

		for(unsigned int pos=0 ; pos <  tam ; pos++) {
			superficie.push_back(rot.rotar_const(forma[pos]));
		}
	}
	keep = !borrar;
	init();

}

SuperficieRevolucion::~SuperficieRevolucion() {}


