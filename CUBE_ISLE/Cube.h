#pragma once
#include "stdafx.h"

class Cube {
public:
	bool exsist;
	Vector3 color;
	Vector3 pos;
	int size;
	Aabb aabb;

	Cube() = default;
	~Cube() = default;

	void draw() {
		if (!exsist) return;

		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glColor3fv(&color);
		glutSolidCube(size);
		glPopMatrix();
	}

	void draw_aabb() {
		if (!exsist) return;

		aabb.draw();
	}
};
