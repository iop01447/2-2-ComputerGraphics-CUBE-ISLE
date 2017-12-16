#include "Skybox.h"



Skybox::Skybox()
{
	init();
}


Skybox::~Skybox()
{
}

void Skybox::init()
{
	//size = HEIGHT / 10;
	texture.LoadImg();

	size = 2;
	scl = { size,size,size };
}

void Skybox::draw(Vector3& pos)
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	glScalef(scl.x, scl.y, scl.z);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture.textures[0]);
	glBegin(GL_QUADS);
	//�ո�
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, 1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture.textures[1]);
	glBegin(GL_QUADS);
	//���� ������
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, 1, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture.textures[2]);
	glBegin(GL_QUADS);
	//�޸�
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, 1, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture.textures[3]);
	glBegin(GL_QUADS);
	//���� ����
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, 1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture.textures[4]);
	glBegin(GL_QUADS);
	//�ظ�
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, -1, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture.textures[5]);
	glBegin(GL_QUADS);
	//����
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, 1, -1);
	glEnd();
	glPopMatrix();
}
