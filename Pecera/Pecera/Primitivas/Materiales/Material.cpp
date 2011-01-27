
#include "Material.h"

Material::Material() {
	setDiffuse(0.85,0.85, 0.85, 1);
	setSpecular(0.8, 0.81, 1, 1);
	setAmbient(0.0, 0.1, 0.2, 1);
	setShininess(128.0);
}

Material::~Material() {}

void Material::usarMaterial() {
	glColor4fv( mat_diffuse );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
//->> TODO no se por que no anda el BACK como yo quiero!!!
}

void Material::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
	mat_diffuse[0]=r; mat_diffuse[1]=g; mat_diffuse[2]=b; mat_diffuse[3]=alpha;
}
void Material::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
	mat_ambient[0]=r; mat_ambient[1]=g; mat_ambient[2]=b; mat_ambient[3]=alpha;
}
void Material::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
	mat_specular[0]=r; mat_specular[1]=g; mat_specular[2]=b; mat_specular[3]=alpha;
}
void Material::setShininess(GLfloat shine) {
	mat_shininess[0] = shine;
}

