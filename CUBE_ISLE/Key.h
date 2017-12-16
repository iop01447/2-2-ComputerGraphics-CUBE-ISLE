#pragma once
#include "stdafx.h"

class Key
{
public:
	Key();
	~Key();

	Vector3 pos;
	Vector3 scl;
	Vector3 rot;
	float size;
	int slices;
	Aabb aabb;
	bool exsist;

	void Init();
	void Init_aabb();
	void Draw();
	void draw_aabb();
	void Update();
};

