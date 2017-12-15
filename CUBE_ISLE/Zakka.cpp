#include "stdafx.h"
#include "Zakka.h"


Zakka::Zakka()
{
}


Zakka::~Zakka()
{
}

void Zakka::Init()
{
	m_xtrs = m_ytrs = m_ztrs = 0;
	m_xscl = 10;
	m_yscl = 10;
	m_zscl = 9;
	m_xrot = 10;
	m_yrot = m_zrot = 0;
	size = 1;
	slices = 30;
}

void Zakka::Draw()
{
	glPushMatrix();

	glTranslatef(m_xtrs, m_ytrs, m_ztrs);
	glRotatef(m_xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(m_zrot, 0.0f, 0.0f, 1.0f);
	glScalef(m_xscl, m_yscl, m_zscl);

	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(size, slices, slices);

	//´«
	glPushMatrix();
	glTranslatef(-size / 6, size / 2, 5 * size / 6);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(size / 30, 6, 6);
	glTranslatef(2 * size / 6, 0.0f, 0.0f);
	glutSolidSphere(size / 30, 6, 6);
	glPopMatrix();

	//ÀÔ
	glPushMatrix();
	glTranslatef(0.0f, size * 0.49f, 4 * size / 5);
	glColor3f(0.8f, 0.2f, 0.2f);
	glRotatef(35, 1.0f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 0.0f, 1.0f);
	glutSolidCone(size / 10, size / 5, 4, 4);
	glPopMatrix();

	//¾Æ·¡ ¾ó±¼
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, -size / 4, size / 10);
	glScalef(1.1f, 0.9f, 1.2f);
	glutSolidSphere(size, slices, slices);
	glPopMatrix();

	//±Í
	glPushMatrix();
	glTranslatef(-size + size / 7, 3 * size / 4, 0.0f);
	glRotatef(-60, 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.5f, 1.0f);
	glutSolidSphere(size / 7, slices / 2, slices / 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size - size / 7, 3 * size / 4, 0.0f);
	glRotatef(60, 0.0f, 0.0f, 1.0f);
	glScalef(1.0f, 1.5f, 1.0f);
	glutSolidSphere(size / 7, slices / 2, slices / 2);
	glPopMatrix();

	//º¼
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(-size / 4, 3 * size / 7, 6 * size / 7);
	glScalef(2.0f, 1.0f, 1.0f);
	glColor4f(1.0f, 0.4f, 0.2f, 0.4f);
	glutSolidSphere(size / 20, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size / 4, 3 * size / 7, 6 * size / 7);
	glScalef(2.0f, 1.0f, 1.0f);
	glutSolidSphere(size / 20, 10, 10);
	glDisable(GL_BLEND);
	glPopMatrix();

	glPopMatrix();
}
