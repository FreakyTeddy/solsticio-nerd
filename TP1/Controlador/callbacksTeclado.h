#ifndef CALLBACKSTECLADO_H_
#define CALLBACKSTECLADO_H_

#include <stdio.h>
#include <time.h>
#include "../Primitivas Graficas/Celular.h"

#define SECONDS 10
#define STEP 5
#define ZOOM 10

class CallBacksTeclado {
	
	private:
		Celular& celular;
	
	public:
		CallBacksTeclado(Celular celular);
		void pressedNumber(int number);
		void changeLine(char type);	
		void zoom(char type);	
		void moveView(char orientation);
		void clearScreen();
};

#endif /*CALLBACKSTECLADO_H_*/
