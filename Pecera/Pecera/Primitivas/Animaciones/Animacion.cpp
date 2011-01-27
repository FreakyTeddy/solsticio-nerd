#include "Animacion.h"

Animacion::Animacion() {
	frame = 0;
	f_cant = 0;
	f_act = 0;

}

Animacion::~Animacion() {
//	for (u_short i=0; i < cant_f; i++) {
//		delete frame[i];
//	}

}

void Animacion::animar() {
	frame[f_act].dibujar(0);
	(f_act != f_cant-1) ? f_act++ : f_act = 0;
}
