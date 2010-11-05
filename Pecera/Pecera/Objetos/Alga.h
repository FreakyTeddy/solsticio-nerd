#ifndef ALGA_H_
#define ALGA_H_

#include "../Primitivas/Superficie/SuperficieBarrido.h"

class Alga {
private:
	Superficie* alga;

public:
	Alga();
	~Alga();
	void dibujar();
};

#endif /* ALGA_H_ */
