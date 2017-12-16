#pragma once
#include "stdafx.h"

class Aabb {
public:
	Vector3 min_;
	Vector3 max_;

	Aabb() {}
	Aabb(Vector3 min, Vector3 max) : min_(min), max_(max) {}
	//	Aabb(Vector3 pos, Vector3 length) {
	//		min = pos - length / 2;
	//		max = pos + length / 2;
	//	}
	~Aabb() = default;

	void draw(bool solid = false) {
		glPushMatrix();
		Vector3 pos = (max_ + min_) / 2;
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(max_.x - min_.x, max_.y - min_.y, max_.z - min_.z);
		glColor3f(1, 0, 0);
		if (solid)
			glutSolidCube(1);
		else
	 		glutWireCube(1);
		glPopMatrix();
	}
};
