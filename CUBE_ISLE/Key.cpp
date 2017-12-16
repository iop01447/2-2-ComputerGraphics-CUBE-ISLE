#include "stdafx.h"
#include "Key.h"

Key::Key()
{
	Init();
}


Key::~Key()
{
}

void Key::Init()
{
	exsist = true;
	pos = { 0,0,0 };
	scl = { 1.f,1.f,0.9f };
	rot = { 0,0,0 };
	size = 1;
	slices = 6;
}

void Key::Init_aabb()
{
	Vector3 tmp_pos = pos;
	tmp_pos.y -= size*2;
	Vector3 tmp = { size*2, size*2*2, size*2 };
	aabb = { tmp_pos - tmp, tmp_pos + tmp };
}

void Key::Draw()
{
	if (!exsist) return;

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -size * scl.y, 0.0f);
	glRotatef(15, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, size * scl.y, 0.0f);
	glScalef(scl.x, scl.y, scl.z);

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
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, -size * scl.y * 2, 0.0f);
	glScalef(scl.x, scl.y, scl.z);
	glScalef(1.0f, 2.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
	glutSolidCube(size * 4);
	glPopMatrix();
}

void Key::draw_aabb()
{
	if (!exsist) return;

	aabb.draw();
}

void Key::Update()
{
	if (!exsist) return;

	rot.y = ((int)(rot.y + 1)) % 360;
}
