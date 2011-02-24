#include "Textura.h"

#define M_MOSAICO	1
#define M_EXPANDIDA	2


Textura::Textura() {
	tex = 0;
	modo = M_MOSAICO;
	contenedorTex = ContenedorTexturas::getInstancia();
}

Textura::~Textura() {}

void Textura::cargarImagen(std::string ruta) {
	tex = contenedorTex->cargarImagen(ruta);
}


void Textura::generarCoordenadas(const std::vector<Vertice> &sup, std::vector<Vertice2D> &texCoord, uint tam){


	/* MODO EXPANDIDA */

	/**
	 * Coordenada de textura: (x,y) = (side,tall) = (s,t) en el intervalo [0-1]
	 * Tengo que mapear la superficie al [0-1]
	 */

	std::vector<float> side;	// long a lo "ancho" para cada vertice de la curva patron
	std::vector<float> tall;	// long a lo "largo" para cada vertice de la curva patron
	std::vector<float> acum_s, acum_t;

	tall.resize(sup.size()/tam+1,0);
	acum_t.resize(sup.size()/tam+1,0);
	side.resize(tam+1,0);
	acum_s.resize(tam+1,0);

	uint i=0,j=0,nro_curva = 0;
	for (i=0; i < (sup.size()-tam); i++) {	//i indica donde estoy en la superficie
		nro_curva= i/tam;
		for(j=0; j<tam-1; j++,i++){			//j indica donde estoy en nro_curva
			tall[nro_curva] += sup[i].distancia(sup[i+1]);	// acumulo distancia "vertical"
			side[j] += sup[i].distancia(sup[i+tam]);		// acumulo distancia "horizontal"
		}
		side[j] += sup[i].distancia(sup[i+tam]);
	}
	//al ultimo le falta la longitud
	for(nro_curva+=1 ;i < (sup.size()-1);i++){
		tall[nro_curva] += sup[i].distancia(sup[i+1]);
	}

	/* asigno coordenadas de textura */

	/* calculo nuevamente las distancias y a la vez asigno la coordenada de textura correspondiente
	 * se le asigna una coordenada [0-1] en funcion del porcentaje de "distancia" recorrido en esa direccion
	 * */

	/* Es similar solo que calcula distancias ya recorridas ( resta "tam" en lugar de sumar -> sisi soy complicada X_X )*/

	Vertice2D temp;
	float acum = 0;

	texCoord.push_back(temp);
	// primer curva tiene coordenada s=0
	for (i=1; i < tam; i++){
		acum += sup[i].distancia(sup[i-1]);
		temp.y = acum / tall[0];
		texCoord.push_back(temp);
	}

	for (i=tam; i < sup.size(); i++) {
		nro_curva= i/tam;

		acum_s[j] += sup[i].distancia(sup[i-tam]);
		temp.x = acum_s[j] / side [j];
		temp.y = 0;
		texCoord.push_back(temp);
		i++;

		for(j=1; j<tam; j++,i++){
			acum_t[nro_curva] += sup[i].distancia(sup[i-1]);	// acumulo distancia "vertical"
			acum_s[j] += sup[i].distancia(sup[i-tam]);			// acumulo distancia "horizontal"

			temp.x = acum_s[j] / side [j];						// escalo coordenada 's'
			temp.y = acum_t[nro_curva] / tall[nro_curva];		// escalo coordenada 't'
			texCoord.push_back(temp);
		}
		i--;
	}

	tall.clear();
	side.clear();
	acum_s.clear();
	acum_t.clear();
}


bool Textura::tieneTextura() {
	return (tex!=0);
}

GLuint Textura::getID() {
	return tex;
}

void Textura::setModoMosaico() {
	modo = M_MOSAICO;
}

void Textura::setModoExpandida() {
	modo = M_EXPANDIDA;
}
