#pragma once
#include "stdafx.h"

class Fog {
public:
	Fog() {
		init(); 
	};
	~Fog() = default;

	GLfloat fog_color[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat density;
	GLfloat start;
	GLfloat end;
	GLint mode;

	void init() {
		density = 0.005f;
		start = 10;
		end = 50;
	}

	void draw() {
		glFogf(GL_FOG_MODE, GL_EXP);
		glFogfv(GL_FOG_COLOR, fog_color);
		glFogf(GL_FOG_START, start);
		glFogf(GL_FOG_END, end);
		glFogf(GL_FOG_DENSITY, density);
	}
};