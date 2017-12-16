#pragma once
#include "stdafx.h"

#define TEXTURENUM	6

class Texture
{
public:
	Texture();
	~Texture();

	GLubyte		*pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO	*info; // 비트맵 헤더 저장할 변수
	GLuint		textures[TEXTURENUM];

	void		LoadImg();
	GLubyte		*LoadDIBitmap(const char *filename, BITMAPINFO **info);
};

