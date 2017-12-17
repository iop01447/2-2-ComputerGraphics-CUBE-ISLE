#pragma once
#include "stdafx.h"

class Cube {
public:
	bool exsist;
	Vector3 color;
	Vector3 pos;
	int size;
	Aabb aabb;
	bool is_sea = false;

	Cube() = default;
	~Cube() = default;

	void draw() {
		if (!exsist) return;

		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		if (is_sea)
			glColor4f(color.x, color.y, color.z, 0.8);
		else
			glColor3fv(&color);
		glutSolidCube(size);
		glPopMatrix();
	}

	void draw_aabb() {
		if (!exsist) return;

		aabb.draw();
	}

	void broken_ani() {

	}
};
