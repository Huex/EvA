#include "stdafx.h"
#include "chiken.h"

void Chiken::Update()
{
	extern float TIME_PER_FRAME;
	x += dx*0.005;
	y += dy*0.005;

	if (dx == 0 && dy == 0)
	{
		coord.s = float(2) / 7;
	}

	if (dy > 0)
	{
		orientation = Up;
		timerY += TIME_PER_FRAME;
		if (timerY > 120)
		{
			coord.s -= scale.s;
			timerX = 0;
			timerY = 0;
			if (coord.s <= float(3) / 7)
			{
				coord.s = float(6) / 7;
			}
		}

	}
	if (dy < 0)
	{
		orientation = Down;
		timerY += TIME_PER_FRAME;
		if (timerY > 120)
		{
			coord.s -= scale.s;
			timerX = 0;
			timerY = 0;
			if (coord.s <= float(3) / 7)
			{
				coord.s = float(6) / 7;
			}
		}
	}
	if (dx < 0)
	{
		orientation = Left;
		timerX += TIME_PER_FRAME;
		if (timerX > 120)
		{
			coord.s -= scale.s;
			timerX = 0;
			timerY = 0;
			if (coord.s <= float(3) / 7)
			{
				coord.s = float(6) / 7;
			}
		}

	}
	if (dx > 0)
	{
		orientation = Right;
		timerX +=  TIME_PER_FRAME;
		if (timerX > 120)
		{
			coord.s -= scale.s;
			timerX = 0;
			timerY = 0;
			if (coord.s <= float(3) / 7)
			{
				coord.s = float(6) / 7;
			}
		}

	}
}


Chiken::Chiken(TextureHelper * gTexture)
{
	_textureHelper = gTexture;
	_textureHelper->Load("textures/chiken.png", &texture);
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	timerX = 0;
	timerY = 0;
	orientation = Left;

	coord.s = float(6) / 7;
	coord.t = float(1) / 3;


	scale.s = float(1) / 7;
	scale.t = float(1) / 3;
}


Chiken::~Chiken()
{
}

void Chiken::Draw()
{
	extern float RATIO;
	Update();
	_textureHelper->Activate(&texture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	if (orientation == Left)
	{
		coord.t = float(1) / 3;
		glTexCoord2f(coord.s, coord.t); glVertex3f(-0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t); glVertex3f(0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t - scale.t); glVertex3f(0.1 + x, (0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s, coord.t - scale.t); glVertex3f(-0.1 + x, (0.1 + y) * RATIO, 0);
	}
	if (orientation == Right)
	{
		coord.t = float(1) / 3;
		glTexCoord2f(coord.s + scale.s, coord.t); glVertex3f(-0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s, coord.t); glVertex3f(0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s, coord.t - scale.t); glVertex3f(0.1 + x, (0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t - scale.t); glVertex3f(-0.1 + x, (0.1 + y) * RATIO, 0);
	}
	if (orientation == Up)
	{
		coord.t = float(3) / 3;
		glTexCoord2f(coord.s, coord.t); glVertex3f(-0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t); glVertex3f(0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t - scale.t); glVertex3f(0.1 + x, (0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s, coord.t - scale.t); glVertex3f(-0.1 + x, (0.1 + y) * RATIO, 0);
	}
	if (orientation == Down)
	{
		coord.t = float(2) / 3;
		glTexCoord2f(coord.s, coord.t); glVertex3f(-0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t); glVertex3f(0.1 + x, (-0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s + scale.s, coord.t - scale.t); glVertex3f(0.1 + x, (0.1 + y) * RATIO, 0);
		glTexCoord2f(coord.s, coord.t - scale.t); glVertex3f(-0.1 + x, (0.1 + y) * RATIO, 0);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	dx = dy = 0;
}