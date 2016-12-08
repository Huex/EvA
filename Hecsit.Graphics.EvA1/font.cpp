#include "font.h"
#include <OpenGL/glew.h>
#include <OpenGL/glut.h>

FontHelper::~FontHelper()
{
}

void FontHelper::Render(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, 0);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}