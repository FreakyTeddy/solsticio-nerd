/*
 * rotacion_3d.h
 *
 *  Created on: Jan 22, 2011
 *      Author: nicolas-pc
 */

#ifndef ROTACION_3D_H_
#define ROTACION_3D_H_

#include "Vertice.h"
#include <cmath>

/*
 * Código adaptado de: Gráficos por computadora con OpenGL página 282.
 */
class Rotacion3d
{
public:
	Rotacion3d(const Vertice& ej1, const Vertice& ej2, double grados)
	{
		generarMatriz(ej1, ej2, grados);
	}

	~Rotacion3d()
	{
	}

	Vertice rotar_const(const Vertice& punto)
	{
		Vertice rotado = punto;
		rotar(rotado);
		return rotado;
	}

	void rotar(Vertice& punto)
	{
		Vertice temp = punto;

		temp.x = punto.x * matriz[0][0] +
				  punto.y * matriz[0][1] +
				  punto.z * matriz[0][2] +
				  	  	  	 matriz[0][3];

		temp.y = punto.x * matriz[1][0] +
				  punto.y * matriz[1][1] +
				  punto.z * matriz[1][2] +
				  	  	  	 matriz[1][3];

		temp.z = punto.x * matriz[2][0] +
				  punto.y * matriz[2][1] +
				  punto.z * matriz[2][2] +
				  	  	  	 matriz[2][3];

		punto = temp;
	}

private:

	void cargarIdentidad(double m[][4])
	{
		for (unsigned i = 0; i < 4; i++)
			for (unsigned j = 0; j < 4; j++)
				m[i][j] = (i == j);
	}

	void preMultiplicacion(double m1[][4], double m2[][4])
	{
		double temp[4][4];

		for (unsigned i = 0; i < 4; i++)
			for (unsigned j = 0; j < 4; j++)
				temp[i][j] = m1[i][0] * m2[0][j] +
				 	 	 	 m1[i][1] * m2[1][j] +
				 	 	 	 m1[i][2] * m2[2][j] +
				 	 	 	 m1[i][3] * m2[3][j];

		for (unsigned i = 0; i < 4; i++)
			for (unsigned j = 0; j < 4; j++)
				m2[i][j] = temp[i][j];
	}

	void trasladar3d(double dx, double dy, double dz)
	{
		double tras[4][4];

		cargarIdentidad(tras);

		tras[0][3] = dx;
		tras[1][3] = dy;
		tras[2][3] = dz;

		preMultiplicacion(tras, matriz);

	}

	void generarMatriz(const Vertice& ej1, const Vertice& ej2, double grados)
	{
		double rot[4][4];

		double radians = grados*PI/180;

		double axisVectLength = sqrt ((ej2.x - ej1.x) * (ej2.x - ej1.x) +
									  (ej2.y - ej1.y) * (ej2.y - ej1.y) +
									  (ej2.z - ej1.z) * (ej2.z - ej1.z) );

		double cosA = cos(radians);
		double oneC = 1 - cosA;
		double sinA = sin(radians);

		double ux = (ej2.x - ej1.x) / axisVectLength;
		double uy = (ej2.y - ej1.y) / axisVectLength;
		double uz = (ej2.z - ej1.z) / axisVectLength;

		cargarIdentidad(matriz);
		cargarIdentidad(rot);

		trasladar3d(-ej1.x, -ej1.y, -ej1.z);

		rot[0][0] = ux * ux * oneC + cosA;
		rot[0][1] = ux * uy * oneC - uz * sinA;
		rot[0][2] = ux * uz * oneC + uy * sinA;
		rot[1][0] = uy * ux * oneC + uz * sinA;
		rot[1][1] = uy * uy * oneC + cosA;
		rot[1][2] = uy * uz * oneC - ux * sinA;
		rot[2][0] = uz * ux * oneC - uy * sinA;
		rot[2][1] = uz * uy * oneC + ux * sinA;
		rot[2][2] = uz * uz * oneC + cosA;

		preMultiplicacion(rot, matriz);

		trasladar3d(ej1.x, ej1.y, ej1.z);
	}

	double matriz[4][4];
};

#endif /* ROTACION_3D_H_ */
