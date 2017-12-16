#pragma once
#include "stdafx.h"

class Light
{
public:
	Light();
	~Light();

	GLfloat AmbientLight[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat DiffuseLight[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat SpecularLight[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLint Shininess = 128;
	GLfloat Poslight[4] = { 0.0f, 10, 0.0f, 1.0f };

	void light_global();
};