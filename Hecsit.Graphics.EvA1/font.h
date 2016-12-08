#pragma once
#include "texture.h"

class FontHelper 
{
public:
	~FontHelper();
	static void Render(float x, float y, void *font, char *string);
};

