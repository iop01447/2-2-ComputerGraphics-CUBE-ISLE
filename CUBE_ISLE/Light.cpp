#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::light_global()
{
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, Shininess);

	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, Poslight);
	glEnable(GL_LIGHT0);

	glPushMatrix();
		glTranslatef(Poslight[0], Poslight[1], Poslight[2]);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidSphere(2, 7, 7);
	glPopMatrix();
}
