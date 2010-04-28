#ifndef VERTICE_H_
#define VERTICE_H_

class Vertice {
	
	public:
		float x;
		float y;
		float z;

		Vertice() { x = 0.0; y = 0.0; z= 0.0; };

		bool operator==(const Vertice& v) {
			return  ((x == v.x) && (y == v.y) && (z == v.z));
		};
};

#endif /*VERTICE_H_*/
