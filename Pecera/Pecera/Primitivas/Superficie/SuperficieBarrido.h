#ifndef SUPERFICIEBARRIDO_H_
#define SUPERFICIEBARRIDO_H_

#include "Superficie.h"



class SuperficieBarrido :public Superficie {

public:

	/* Crea una superficie de barrido en base a una curva, aplicando la traslacion
	 * y deformacion correspondiente a cada paso
	 * conviene que trasl empiece en (0,0,0) ;)*/

	SuperficieBarrido(std::vector<Vertice> &forma, std::vector<Vertice> &trasl);
	~SuperficieBarrido();

};

#endif /* SUPERFICIEBARRIDO_H_ */
