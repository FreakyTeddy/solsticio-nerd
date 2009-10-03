/*
 * Funciones.cpp
 *
 *  Created on: 03/10/2009
 *      Author: luuu
 */

#include "Funciones.h"

void Funciones::swap(void* a, void* b) {
	void* aux = a;
	a = b;
	b = aux;
}
