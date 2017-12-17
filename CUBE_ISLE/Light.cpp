#include "Light.h"



Light::Light()
{
	init();
}


Light::~Light()
{
}

void Light::init()
{
	r = 0.2f;
	g = 0.1f;
	b = 0.0f;
	global_rot = 0;
	global_rot_cnt = 0;
	global_state = false;
	light_rot = 0;
	for(int i = 0; i < 7; ++i)
		exist[i] = true;
}

void Light::light_global()
{
	glPushMatrix();
	glRotatef(global_rot - 180, 0.0f, 0.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, Shininess);

	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientLight);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, Poslight);
	glEnable(GL_LIGHT0);
	glPopMatrix();
}

void Light::pos_init(Vector3 key_pos, int num)
{
	key_Poslight[num][0] = key_pos.x;
	key_Poslight[num][1] = key_pos.y + 15; // 6
	key_Poslight[num][2] = key_pos.z;
//	key_Poslight[num][3] = 0.1f;
	key_Poslight[num][3] = 1.f;
}

void Light::light_on()
{
	//global light
	glPushMatrix();
	glRotatef(global_rot - 180, 0.0f, 0.0f, 1.0f);
	glTranslatef(Poslight[0], Poslight[1], Poslight[2]);
	glColor3f(r, g, b);
	glutSolidSphere(20, 12, 12);
	glPopMatrix();

	glEnable(GL_NORMALIZE);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glDisable(GL_CULL_FACE);
	//light 1
	if (exist[0] == true)
	{
		glPushMatrix();
		glLightfv(GL_LIGHT1, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, key_Poslight[0]);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT1);
	
		glTranslatef(key_Poslight[0][0], key_Poslight[0][1], key_Poslight[0][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	if (exist[1] == true)
	{
		//light 2
		glPushMatrix();
		glLightfv(GL_LIGHT2, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT2, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT2, GL_POSITION, key_Poslight[1]);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT2);
	
		glTranslatef(key_Poslight[1][0], key_Poslight[1][1], key_Poslight[1][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	if (exist[2] == true)
	{
		//light 3
		glPushMatrix();
		glLightfv(GL_LIGHT3, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT3, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT3, GL_POSITION, key_Poslight[2]);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT3);
	
		glTranslatef(key_Poslight[2][0], key_Poslight[2][1], key_Poslight[2][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	if (exist[3] == true)
	{
		//light 4
		glPushMatrix();
		glLightfv(GL_LIGHT4, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT4, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT4, GL_POSITION, key_Poslight[3]);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT4);
	
		glTranslatef(key_Poslight[3][0], key_Poslight[3][1], key_Poslight[3][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	if (exist[4] == true)
	{
		// light 5
		glPushMatrix();
		glLightfv(GL_LIGHT5, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT5, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT5, GL_POSITION, key_Poslight[4]);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT5);
	
		glTranslatef(key_Poslight[4][0], key_Poslight[4][1], key_Poslight[4][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	if (exist[5] == true)
	{
		// light 6
		glPushMatrix();
		glLightfv(GL_LIGHT6, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT6, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT6, GL_POSITION, key_Poslight[5]);
		glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT6);
	
		glTranslatef(key_Poslight[5][0], key_Poslight[5][1], key_Poslight[5][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	if (exist[6] == true)
	{
		//light 7
		glPushMatrix();
		glLightfv(GL_LIGHT7, GL_AMBIENT, key_AmbientLight);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, key_DiffuseLight);
		glLightfv(GL_LIGHT7, GL_SPECULAR, key_SpecularLight);
		glLightfv(GL_LIGHT7, GL_POSITION, key_Poslight[6]);
		glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, direction);
		glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, cutoff);
		glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, exponent);
		glEnable(GL_LIGHT7);
	
		glTranslatef(key_Poslight[6][0], key_Poslight[6][1], key_Poslight[6][2]);
		glColor4fv(key_AmbientLight);
		glRotatef(light_rot, 0.0f, 1.0f, 0.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glutSolidCone(key_light_size, key_light_size, 4, 4);
		glPopMatrix();
	}
	glDisable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
}

void Light::light_off()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);
}

void Light::update()
{
	light_rot = (light_rot + 2) % 360;
	global_rot_cnt++;
	if (global_rot_cnt > 5)
	{
		global_rot = (global_rot + 1) % 360;
		if (global_rot == 180 || global_rot == 0)
		{			
			global_state = !global_state;
		}

		if (!global_state)
		{
			if (g < 0.8f)
			{
				r += 4.0f / 360.0f;
				g += 2.0f / 360.0f;
				b += 1.0f / 360.0f;
				AmbientLight[0] = r;
				AmbientLight[1] = g;
				AmbientLight[2] = b;
			}
		}
		else if (global_state)
		{
			if (r > 0.2f)
			{
				r -= 4.0f / 360.0f;
				g -= 2.0f / 360.0f;
				b -= 1.0f / 360.0f;
				AmbientLight[0] = r;
				AmbientLight[1] = g;
				AmbientLight[2] = b;
			}
		}

		global_rot_cnt = 0;
	}
}
