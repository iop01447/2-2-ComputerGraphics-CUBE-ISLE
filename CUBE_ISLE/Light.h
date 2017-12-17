#pragma once
#include "stdafx.h"

class Light
{
public:
	Light();
	~Light();

	GLfloat AmbientLight[4] = { 0.0f, 0.0f, 0.0f, 0.5f };
	GLfloat DiffuseLight[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat SpecularLight[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLint Shininess = 128;
	GLfloat Poslight[4] = { 0.0f, WIDTH / 4, 0.0f, 1.0f };
	GLfloat r, g, b;
	GLint global_rot = 0;
	GLint global_rot_cnt = 0;
	GLboolean global_state = false;

	void init();
	void light_global();

	GLfloat key_AmbientLight[4] = { 0.6f, 0.8f, 0.2f, 0.5f };
	GLfloat key_DiffuseLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat key_SpecularLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat key_Poslight[7][4];
	float direction[3] = { 0,0,-1 };
	float cutoff = 180.0f;
	float exponent = 0.0f;
	float key_light_size = 2;
	GLint light_rot = 0;
	bool exist[7] = { true };

	void pos_init(Vector3 key_pos, int num);
	void light_on();
	void light_off();
	void update();
};