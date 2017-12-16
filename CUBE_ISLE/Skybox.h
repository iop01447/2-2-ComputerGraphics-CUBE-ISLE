#pragma once
#include "stdafx.h"
#include "Texture.h"

class Skybox
{
public:
	//	Texture
	Texture	texture;

	Skybox();
	~Skybox();

	Vector3 pos;
	Vector3 scl;
	Vector3 rot;
	float size;

	void init();
	void draw(Vector3& pos);
};