#pragma once
#include "stdafx.h"

class Fog {
public:
	Fog() {
		init(); 
	};
	~Fog() = default;

	GLfloat fog_color[4] = { 0.4f, 0.8f, 0.8f, 1.0f };
	GLfloat fog_light_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat density;
	GLfloat start;
	GLfloat end;
	GLint mode;

	void init() {
		density = 0.005f;
		start = 2;
		end = 3;
	}

	void draw() {
		glFogf(GL_FOG_MODE, GL_EXP);
		glFogfv(GL_FOG_COLOR, fog_light_color);
		glFogf(GL_FOG_START, start);
		glFogf(GL_FOG_END, end);
		glFogf(GL_FOG_DENSITY, density);
	}

	void update(GLfloat r, GLfloat g, GLfloat b) {
		fog_light_color[0] = r;
		fog_light_color[1] = g + 0.2f;
		fog_light_color[2] = b + 0.2f;
	}
};