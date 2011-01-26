#ifndef VERTICE_H_
#define VERTICE_H_

#include <math.h>
#include <iostream>

#include "../Util.h"

/*
 * Describe un punto 3D
 *
 * */


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

		Vertice(const Vertice &v) {
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

		void print() const {
			std::cout<< x<<" "<<y<<" "<<z<<std::endl;
		};

		float distancia(const Vertice &v) const {
			return ((*this)-v).modulo();
		}

		void opuesto() {
			x = (-x); y = (-y); z = (-z);
		}

		/* rota el vertice sobre un eje definido por dos puntos */
		void rotar(const Vertice &inicio, const Vertice &fin, const float angulo) {

			//proyecto sobre yz y calculo el angulo del eje con los planos x e y para rotar sobre el eje z
			Vertice v1 = fin - inicio;
			Vertice v = v1.normalizar().proyeccionYZ();

			double norm = v.modulo();
			double sen_x = v.y/norm;
			double cos_x = v.z/norm;
			if (v1.esIgual(1,0,0)) { //caso especial si el eje de rotacion es x
				sen_x = 0;
				cos_x = 1;
			}

			Util::rotar(v1.y, v1.z, sen_x, cos_x);

			double sen_y = v1.x / v1.modulo();
			double cos_y = v1.z / v1.modulo();

			//traslado al origen
			(*this) -= inicio;

			//roto sobre eje x
			Util::rotar(this->y, this->z, sen_x, cos_x);
			//roto sobre eje y
			Util::rotar(this->z, this->x, sen_y, cos_y);

			//roto el angulo alfa en el eje z
			Util::rotar(this->x, this->y, angulo);

			//hago el camino inverso

			//roto sobre eje y
			Util::rotar(this->z, this->x, -sen_y, cos_y);
			//roto sobre eje x
			Util::rotar(this->y, this->z, -sen_x, cos_x);

			//traslado
			(*this) += inicio;


		}
};


/*
 * Describe un punto 2D
 *
 * */

class Vertice2D {

public:
	float x;
	float y;

	Vertice2D() {
		x = 0.0; y = 0.0;
	};

	Vertice2D(float a, float b, float c) {
		x = a; y = b;
	};

	Vertice2D(const Vertice2D &v) {
		*this = v;
	}

	void set(const float a, const float b) {
		x = a; y = b;
	};

	void proyeccionYZ(const Vertice &v) {
		set(v.y,v.z);
	};

	void proyeccionXY(const Vertice &v) {
		set(v.x,v.y);
	};

	void proyeccionZX(const Vertice &v) {
		set(v.z,v.x);
	};
};


#endif /*VERTICE_H_*/
