#include "Controlador.h"

Controlador::Controlador(Curva* curva) {

	this->curva= curva;	
}

void Controlador::aumentarPasoBezier() {
	
	curva->modificarFactorBezier(PASO);
}

void Controlador::disminuirPasoBezier() {

	curva->modificarFactorBezier(-PASO);
}
