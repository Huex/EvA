#pragma once
#include <OpenGL/glew.h>

class Drawable
{
public:
	virtual ~Drawable(){}
	virtual void Draw() = 0;
};

class RedSquare : public Drawable
{
public:
	void Draw() override
	{
		float scale = 1.7;
		float scaleX = -0.4*scale;
		float scaleY = -0.3*scale;
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-scaleX, -scaleY);
		glVertex2f(scaleX, -scaleY);
		glVertex2f(scaleX, scaleY);
		glVertex2f(-scaleX, scaleY);
		glVertex2f(-scaleX, -scaleY);
		glEnd();
		scale = 3.9;
		scaleX = -0.13*scale;
		scaleY = -0.07*scale;
		glBegin(GL_LINE_STRIP);
		glVertex2f(-scaleX, -scaleY-0.1);
		glVertex2f(scaleX, -scaleY-0.1);
		glVertex2f(scaleX, scaleY-0.1);
		glVertex2f(-scaleX, scaleY-0.1);
		glVertex2f(-scaleX, -scaleY-0.1);
		glEnd();
		glColor3f(1, 0, 0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-scaleX, -scaleY - 0.075);
		glVertex2f(scaleX, -scaleY - 0.075);
		glVertex2f(scaleX, scaleY - 0.075);
		glVertex2f(-scaleX, scaleY - 0.075);
		glVertex2f(-scaleX, -scaleY - 0.075);
		glEnd();
		glColor3f(1, 1, 1);
	};
private:
};