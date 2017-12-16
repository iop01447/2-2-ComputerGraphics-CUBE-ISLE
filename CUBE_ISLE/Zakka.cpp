#include "stdafx.h"
#include "Zakka.h"


Zakka::Zakka()
{
	Init();
}


Zakka::~Zakka()
{
}

void Zakka::Init()
{
	pos = { 0,0,0 };
	scl = { 10,10,9 };
	scl *= 0.5;
	rot = { 0,180,0 };
	size = 1;
	slices = 30;
	get_key_num = 0;
	Init_aabb();
}

void Zakka::Init_aabb()
{
	float add = 1;
	aabb = { pos - scl + add, pos + scl - add };
}

void Zakka::Draw()
{
	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	glScalef(scl.x, scl.y, scl.z);

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
	glTranslatef(-size / 4, 3 * size / 7, 6 * size / 7);
	glScalef(2.0f, 1.0f, 1.0f);
	glColor4f(1.0f, 0.4f, 0.2f, 0.4f);
	glutSolidSphere(size / 20, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(size / 4, 3 * size / 7, 6 * size / 7);
	glScalef(2.0f, 1.0f, 1.0f);
	glutSolidSphere(size / 20, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void Zakka::draw_aabb() {
	aabb.draw();
}

void Zakka::move(Camera& camera)
{
	Vector3 add;
	int speed = 3;
	if (jump_active) speed = 1;
	add = camera.GetLookVector().normalize();
	add.y = 0;
	add *= speed;

	switch (key)
	{
	case 'w':
		add = -add;
		pos += add;
		break;
	case 'a':
		yRotate(add, 90);
		pos += add;
		break;
	case 's':
		pos += add;
		break;
	case 'd':
		yRotate(add, -90);
		pos += add;
		break;
	}
	key = 0;

	Init_aabb();
	camera.SetFpvPosition(pos);
}

void Zakka::move_back(Camera& camera)
{
	Vector3 add;
	int speed = 3;
	if (jump_active) speed = 1;
	add = camera.GetLookVector().normalize();
	add.y = 0;
	add *= speed;

	switch (back_key)
	{
	case 'w':
		add = -add;
		pos -= add;
		break;
	case 'a':
		yRotate(add, 90);
		pos -= add;
		break;
	case 's':
		pos -= add;
		break;
	case 'd':
		yRotate(add, -90);
		pos -= add;
		break;
	}
	back_key = 0;

	Init_aabb();
	camera.SetFpvPosition(pos);
}

void Zakka::jump()
{
	static int time = 0;
	// cube size°¡ 18
	static int add = 2;
	pos.y += add;
	time++;
	if (time > 18) {
		add = 0;
	}
	if (time > 36) {
		jump_active = false;
		time = 0;
		add = 2;
	}
}

void Zakka::yRotate(Vector3& add, int angle) {
	float theta = radian(angle);
	float y[3][3] = { { cos(theta),0,-sin(theta) },{ 0,1,0 },{ sin(theta),0,cos(theta) } };
	add = { y[0][0] * add.x + y[0][1] * add.y + y[0][2] * add.z,
		y[1][0] * add.x + y[1][1] * add.y + y[1][2] * add.z ,
		y[2][0] * add.x + y[2][1] * add.y + y[2][2] * add.z };
}

void Zakka::update()
{
	// Áß·Â
	pos.y -= 1;

	// Á¡ÇÁ
	if (jump_active) {
		jump();
		key = jump_key;
	}

	Init_aabb();
}

void Zakka::update_back()
{
	pos.y += 1;
	Init_aabb();

//	if (jump_active)
//		jump_active = false;
}
