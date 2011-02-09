
#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <GL/glut.h>

class Material {
private:

	/* material de la superficie */
	GLfloat mat_diffuse[4];
	GLfloat mat_ambient[4];
	GLfloat mat_specular[4];
	GLfloat mat_emisividad[4];
	GLfloat mat_shininess[1];
public:

	Material();

	Material (Material &m);

	~Material();

	/* aplica el material */
	void usarMaterial();

	/* cambian el material de la superficie.. los valores son entre 0 y 1
	 * alpha = 1 -> no hay transparencia	 */
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
	void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);
	void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);

	/* menor shine hace el brillo mas "grande" */
	void setShininess(GLfloat shine);

};

#endif /* MATERIAL_H_ */
