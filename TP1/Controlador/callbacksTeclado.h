#ifndef CALLBACKSTECLADO_H_
#define CALLBACKSTECLADO_H_

class callBacksTeclado {
	
	public:
		void pressedNumber(int number);
		void changeLine(char type);	
		void zoom(char type);	
		void moveView(char orientation);
};

#endif /*CALLBACKSTECLADO_H_*/
