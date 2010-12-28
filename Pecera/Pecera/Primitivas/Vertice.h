#ifndef VERTICE_H_
#define VERTICE_H_

#include <math.h>
#include <iostream>
class Vertice {
	
	public:
		float x;
		float y;
		float z;

		Vertice() {
			x = 0.0; y = 0.0; z= 0.0;
		};

		Vertice(float a, float b, float c) {
			x = a; y = b; z= c;
		};

		Vertice (const Vertice &v) {
			*this = v;
		}

		bool operator==(const Vertice& v) const {
			return  ((x == v.x) && (y == v.y) && (z == v.z));
		};

		void operator=(const Vertice& v) {
			  x = v.x; y = v.y; z = v.z;
		};

		Vertice operator+(const Vertice& v) const {
			Vertice q(x + v.x, y + v.y, z + v.z);
			return q;
		};

		Vertice operator-(const Vertice& v) const {
			Vertice q(x - v.x, y - v.y, z - v.z);
			return q;
		};

		Vertice operator*(const float d) const {
			Vertice q(x*d, y*d, z*d);
			return q;
		};
		Vertice operator*(const Vertice &v) const {
			Vertice q(v.x*x, v.y*y ,v.z*z);
			return q;
		};

		/* NO verifica d != 0 */
		Vertice operator/(const float d) const {
			Vertice q(x/d, y/d, z/d);
			return q;
		};

		void operator-=(const Vertice& v) {
			  x -= v.x; y -= v.y; z -= v.z;
		};

		void operator+=(const Vertice& v) {
			  x += v.x; y += v.y; z += v.z;
		};

		void operator/=(const float a) {
			  x /= a; y /= a; z /= a;
		};

		void operator*=(const float a) {
			  x *= a; y *= a; z *= a;
		};

		void set(const float a, const float b, const float c) {
			x = a; y = b; z = c;
		};

		bool esIgual(const float a, const float b, const float c) const {
			return  ((x == a) && (y == b) && (z == c));
		};

		float modulo() const {
			return sqrt(z*z + y*y + x*x);
		};

		Vertice& normalizar() {
			(*this) /= this->modulo();
			return *this;
		};

		Vertice proyeccionYZ() const {
			Vertice q(0,y,z);
			return q;
		};

		/* realiza el producto vectorial: this x v */
		Vertice prodVectorial(const Vertice &v) const {
			Vertice q(y*v.z - z*v.y , z*v.x - x*v.z, x*v.y - y*v.x);
			return q;
		};

		/* devuelve un vector normal al actual y al parametro */
		Vertice normal(const Vertice &v) const {
			return this->prodVectorial(v).normalizar();
		};

		void print() {
			std::cout<< x<<" "<<y<<" "<<z<<std::endl;
		};

};

#endif /*VERTICE_H_*/
