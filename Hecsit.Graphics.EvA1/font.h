#pragma once
#include <ftgl/FTFont.h>
class FontHelper {
public:
	FontHelper(char *ttf, int FSize, int FDepth);
	~FontHelper();
	FTFont * MyFont;
	void Print(float x, float y, const wchar_t *text);
};

