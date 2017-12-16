#pragma once
#include "stdafx.h"
#include "Camera.h"

class Zakka
{
public:
	Zakka();
	~Zakka();

	Vector3 pos;
	Vector3 scl;
	Vector3 rot;
	float size;
	int slices;
	Aabb aabb;

	enum State {
		  stand
		, up
		, left
		, down
		, right
	};
	State state;
	float speed;

	void Init();
	void Init_aabb();
	void rotate(Camera& look);
	void Draw(Camera&);
	void draw_aabb();
	void move();
};

