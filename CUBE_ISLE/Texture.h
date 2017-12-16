#pragma once
#include "stdafx.h"

#define TEXTURENUM	6

class Texture
{
public:
	Texture();
	~Texture();

	GLubyte		*pBytes; // �����͸� ����ų ������
	BITMAPINFO	*info; // ��Ʈ�� ��� ������ ����
	GLuint		textures[TEXTURENUM];

	void		LoadImg();
	GLubyte		*LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

