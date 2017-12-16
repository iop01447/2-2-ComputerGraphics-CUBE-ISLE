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
	GLfloat Poslight[4] = { 0.0f, WIDTH / 4, 0.0f, 1.0f };

	void light_global();

	GLfloat key_AmbientLight[4] = { 0.8f, 0.8f, 0.2f, 1.0f };
	GLfloat key_DiffuseLight[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat key_SpecularLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat key_Poslight[7][4];
	float direction[3] = { 0,0,-1 };
	float cutoff = 180.0f;
	float exponent = 0.0f;
	float key_light_size = 2;
	int yrot = 0;

	void init(Vector3 key_pos, int num);
	void light_on();
	void light_off();
	void update();
};