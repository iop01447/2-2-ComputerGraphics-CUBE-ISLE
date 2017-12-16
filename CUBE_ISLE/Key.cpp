#include "stdafx.h"
#include "Key.h"



Key::Key()
{
}


Key::~Key()
{
}

void Key::Init()
{
	m_xtrs = m_ytrs = m_ztrs = 50;
	m_xscl = 1;
	m_yscl = 1;
	m_zscl = 0.9f;
	m_xrot = m_yrot = m_zrot = 0;
	size = 1;
	slices = 6;
}

void Key::Draw()
{
	glPushMatrix();
	glTranslatef(m_xtrs, m_ytrs, m_ztrs);
	glRotatef(m_xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(m_zrot, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -size * m_yscl, 0.0f);
	glRotatef(15, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, size * m_yscl, 0.0f);
	glScalef(m_xscl, m_yscl, m_zscl);

	glColor3f(1.0f, 1.0, 0.2f); // key color
	glutSolidTorus(size / 4, size, slices, slices);

	glPushMatrix();
	glTranslatef(0.0f, -size * 3, 0.0f);
	glScalef(0.4f, 4.0f, 0.4f);
	glutSolidCube(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size / 3, -size * 3, 0.0f);
	glScalef(0.8f, 0.4f, 0.4f);
	glutSolidCube(size);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size / 2, -size * 4, 0.0f);
	glScalef(1.0f, 0.4f, 0.4f);
	glutSolidCube(size);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(m_xtrs, m_ytrs, m_ztrs);
	glRotatef(m_yrot, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, -size * m_yscl * 2, 0.0f);
	glScalef(m_xscl, m_yscl, m_zscl);
	glScalef(1.0f, 2.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
	glutSolidCube(size * 4);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Key::Update()
{
	m_yrot = (m_yrot + 1) % 360;
}
