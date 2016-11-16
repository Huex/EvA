#include "stdafx.h"
#include "font.h"
#include <ftgl/FTGLBitmapFont.h>

FontHelper::~FontHelper()
{
}

FontHelper::FontHelper(char *ttf, int FSize, int FDepth)
{
	MyFont = new FTGLBitmapFont(ttf);
	// Устанавливаем размер шрифта или выходим с ошибкой
	if (!MyFont->FaceSize(FSize)) {
		MessageBox(NULL, L"Can't set font FaceSize", L"Error", MB_OK);
		exit(1);
	}
	MyFont->Depth(FDepth);
	// И кодировку - юникод
	MyFont->CharMap(ft_encoding_unicode);
}

void FontHelper::Print(float x, float y, const wchar_t *text)
{
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	// Перемещаемся на указанные координаты
	glTranslatef(x, y, -1);
	glRasterPos2f(-1, 0.5);
	MyFont->Render(text);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}